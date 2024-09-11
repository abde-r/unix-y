/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:13:50 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/11 11:50:52 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

char	*print_permissions(mode_t mode, const char *path) {

    char *s = ft_calloc(999, 1);

    s = ft_strjoin(s, (S_ISDIR(mode)) ? "d" : "-", "");
    s = ft_strjoin(s, (mode & S_IRUSR) ? "r" : "-", "");
    s = ft_strjoin(s, (mode & S_IWUSR) ? "w" : "-", "");
    s = ft_strjoin(s, (mode & S_IXUSR) ? "x" : "-", "");
    s = ft_strjoin(s, (mode & S_IRGRP) ? "r" : "-", "");
    s = ft_strjoin(s, (mode & S_IWGRP) ? "w" : "-", "");
    s = ft_strjoin(s, (mode & S_IXGRP) ? "x" : "-", "");
    s = ft_strjoin(s, (mode & S_IROTH) ? "r" : "-", "");
    s = ft_strjoin(s, (mode & S_IWOTH) ? "w" : "-", "");
    s = ft_strjoin(s, (mode & S_IXOTH) ? "x" : "-", "");
    
    if (has_acl(path))
		s = ft_strjoin(s, "x", "");
	else if (has_extended_attributes(path))
		s = ft_strjoin(s, "@", "");
	else
		s = ft_strjoin(s, " ", "");

	return s;
}

char	*print_file_info(char *filename, const struct stat *file_stat, int _hide_owner, int _hide_group_info_, const char *path) {
    
	struct stat statbuf;
    char fullpath[1024];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", ".", filename);
    
    if (stat(fullpath, &statbuf) == -1) {
        perror("stat");
        exit(1);
    }
    char *s = ft_calloc(999, 1);

    // Get file permissions
    s = ft_strjoin(s, print_permissions(file_stat->st_mode, path), " ");

    // Print number of hard links
    // printf(" %ld", file_stat->st_nlink);
	char *st_link = malloc(999);
	snprintf(st_link, 999, "%lu", file_stat->st_nlink);
    s = ft_strjoin(s, st_link, " ");

    if (_hide_owner == 1) { // Print the owner name (exclude group info)
		struct passwd *pwd = getpwuid(statbuf.st_uid);
		// printf("%s ", pwd->pw_name);
		s = ft_strjoin(s, pwd->pw_name, " ");
	}


    if (_hide_group_info_ == 1) { // Get group information
		struct group *grp = getgrgid(file_stat->st_gid);
		// printf(" %s", grp->gr_name);
		s = ft_strjoin(s, grp->gr_name, " ");
	}


    // Print file size
    // printf(" %ld", file_stat->st_size);
	char *st_size = malloc(999);
	snprintf(st_size, 999, "%ld",file_stat->st_size);
    s = ft_strjoin(s, st_size, " ");

    // Print last modification time
    char time_str[80];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&(file_stat->st_mtime)));
    // printf(" %s", time_str);
    s = ft_strjoin(s, time_str, " ");
    

    // Print file name
    // printf(" %s\n", filename);
    s = ft_strjoin(s, filename, "\0");

	return s;
}

char	*generate_result(t_list *head, char delim) {

    char *t = ft_calloc(ft_lstcontentsize(head), 1);

	while (head != NULL) {
        struct stat file_stat;
        lstat(head->content, &file_stat);
        
		if (head->next != NULL)
			t = ft_strchrjoin(t, head->content, delim);
			// t = print_file_info(head->content, lstat(head->content));
		else
			t = ft_strchrjoin(t, head->content, '\0');
		head = head->next;
	}

	return t;
}

char	*generate_listing_result(t_list *head, char delim, int _hide_owner, int _hide_group_info_, const char *path) {

	struct stat buff;
    char *t = ft_calloc(999, 1);

	while (head != NULL) {
        
		lstat(head->content, &buff);
		if (head->next != NULL)
			t = ft_strchrjoin(t, print_file_info(head->content, &buff, _hide_owner, _hide_group_info_, path), delim);
		else
			t = ft_strchrjoin(t, print_file_info(head->content, &buff, _hide_owner, _hide_group_info_, path), '\0');
		head = head->next;
	}

	return t;
}

char	*generate_recursive_result(t_list *head, char delim) {
    if (head == NULL) return NULL;

    // Allocate memory for the result string
    char *result = ft_calloc(999, 1);  
    char *temp;

    // List all files and directories in the current directory
    t_list *current = head;
    char *t = current->content;
    while (current != NULL) {
        if (current->subdirectory == NULL || ft_strcmp(t, current->content)) {  // If it's a file or a simple directory without subdirectories
            temp = ft_strchrjoin(result, current->content, delim);
            free(result);  // Free the old result before reassigning
            result = temp;
        }
        current = current->next;
    }

    // Now process each subdirectory
    current = head;

    while (current != NULL) {
        if (current->subdirectory != NULL) {  // If it's a directory with subdirectories
            // Generate content for the subdirectory
            char *subdir_res = generate_recursive_result(current->subdirectory, delim);

            // Append the directory name and its content
            temp = ft_strjoin(current->content, ":\n", "");
            // printf("TEMPPPPPP %s\n", temp);
            result = ft_strchrjoin(result, temp, '\0');
            free(temp);
            result = ft_strchrjoin(result, subdir_res, '\0');
            free(subdir_res);
        }
        current = current->next;
    }

    return result;
}
