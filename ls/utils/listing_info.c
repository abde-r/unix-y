/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:13:50 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/20 11:32:45 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

char	*print_permissions(mode_t mode, const char *path) {

    char *s = ft_calloc(9999, 1);

    ft_strcat(s, (S_ISDIR(mode)) ? "d" : "-");
    ft_strcat(s, (mode & S_IRUSR) ? "r" : "-");
    ft_strcat(s, (mode & S_IWUSR) ? "w" : "-");
    ft_strcat(s, (mode & S_IXUSR) ? "x" : "-");
    ft_strcat(s, (mode & S_IRGRP) ? "r" : "-");
    ft_strcat(s, (mode & S_IWGRP) ? "w" : "-");
    ft_strcat(s, (mode & S_IXGRP) ? "x" : "-");
    ft_strcat(s, (mode & S_IROTH) ? "r" : "-");
    ft_strcat(s, (mode & S_IWOTH) ? "w" : "-");
    ft_strcat(s, (mode & S_IXOTH) ? "x" : "-");
    
    if (has_acl(path))
		ft_strcat(s, "x");
	else if (has_extended_attributes(path))
		ft_strcat(s, "@");
	else
		ft_strcat(s, " ");

	return s;
}

char	*print_file_info(char *filename, int _hide_owner, int _hide_group_info_, const char *path) {

	struct stat statbuf;
    char *s = ft_calloc(9999, 1);
    char *full_path = ft_calloc(9999, 1);
    
    ft_strcat(full_path, ft_strjoin(path, "/", filename));
    // printf("pathtogo %s\n", full_path);
    
    if (stat(full_path, &statbuf) == -1) {
        perror("stat");
        exit(1);
    }

    // Get file permissions
    ft_strcat(s, print_permissions(statbuf.st_mode, full_path));
    ft_strcat(s, " ");
    // printf("PERMISSIONSS: %s %s\n", fullpath, print_permissions(statbuf.st_mode, fullpath));

    // Print number of hard links
    // printf(" %ld", file_stat->st_nlink);
	char *st_link = ft_calloc(9999, 1);
	snprintf(st_link, 9999, "%lu", statbuf.st_nlink);
    s = ft_strjoin(s, st_link, " ");

    if (_hide_owner == 1) { // Print the owner name (exclude group info)
		struct passwd *pwd = getpwuid(statbuf.st_uid);
		// printf("%s ", pwd->pw_name);
		s = ft_strjoin(s, pwd->pw_name, " ");
	}


    if (_hide_group_info_ == 1) { // Get group information
		struct group *grp = getgrgid(statbuf.st_gid);
        if (grp)
            s = ft_strjoin(s, grp->gr_name, " ");
	}
    

    // Print file size
    // printf(" %ld", file_stat->st_size);
	char *st_size = ft_calloc(9999, 1);
	snprintf(st_size, 9999, "%ld",statbuf.st_size);
    s = ft_strjoin(s, st_size, " ");

    // Print last modification time
    char time_str[999];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&(statbuf.st_mtime)));
    // printf(" %s", time_str);
    s = ft_strjoin(s, time_str, " ");
    

    // Print file name
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
		else
			t = ft_strchrjoin(t, head->content, '\0');
		head = head->next;
	}

	return t;
}

char	*generate_listing_result(t_list *head, char delim, int _hide_owner, int _hide_group_info_, const char *path) {

	struct stat buff;
    char *t = ft_calloc(9999, 1);

	while (head != NULL) {
        
		lstat(head->content, &buff);
        // printf("hattt %s\n", path);
        // char *fullpath = ft_calloc(9999, 1);
        // ft_strcat(fullpath, ft_strjoin(path, "/", head->content));
        // printf("fullpath %s\n", fullpath);
		if (head->next != NULL)
			t = ft_strchrjoin(t, print_file_info(head->content, _hide_owner, _hide_group_info_, path), delim);
		else
			t = ft_strchrjoin(t, print_file_info(head->content, _hide_owner, _hide_group_info_, path), '\0');
		head = head->next;
	}

	return t;
}

char	*generate_recursive_result(t_list *head, char delim) {
    if (head == NULL) return NULL;

    // Allocate memory for the result string
    char *result = ft_calloc(9999, 1);  
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
        if (is_directory(current->content)) {
            if (current->subdirectory != NULL) {  // If it's a directory with subdirectories
                // Generate content for the subdirectory
                char *subdir_res = generate_recursive_result(current->subdirectory, delim);

                // Append the directory name and its content
                temp = ft_strjoin("\n./", current->content, ":\n");
                // printf("TEMPPPPPP %s\n", temp);
                result = ft_strchrjoin(result, temp, '\0');
                free(temp);
                result = ft_strchrjoin(result, subdir_res, '\0');
                free(subdir_res);
            }
            else {
                // char *subdir_res = generate_recursive_result(current->subdirectory, delim);

                // Append the directory name and its content
                temp = ft_strjoin("\n./", current->content, ":\n");
                // printf("TEMPPPPPP %s\n", temp);
                result = ft_strchrjoin(result, temp, '\0');
                free(temp);
                // result = ft_strchrjoin(result, "", '\0');
                // free(subdir_res);
            }
        }
        current = current->next;
    }

    return result;
}

char *generate_recursive_listing_result(t_list *head, char delim, int _hide_owner, int _hide_group_info, const char *path) {

	struct stat buff;
    
    if (head == NULL) return NULL;

    // Allocate memory for the result string
    char *result = ft_calloc(9999, 1);  
    char *full_path = ft_calloc(1, 1);
    char *temp;

    // List all files and directories in the current directory
    t_list *current = head;
    // char *t = current->content;
    while (current != NULL) {
        // if (current->subdirectory == NULL || ft_strcmp(t, current->content)) {  // If it's a file or a simple directory without subdirectories
            // if (ft_strcmp(path, "."))
            //     snprintf(full_path, 4096, "%s/%s", path, current->content);
            // else
            // snprintf(full_path, 9999, "%s", path);
            full_path = ft_strdup(ft_strjoin(path, "/", current->content));

            // printf("pathtogo %s\n", full_path);
            lstat(full_path, &buff);
            temp = ft_strchrjoin(result, print_file_info(current->content, _hide_owner, _hide_group_info, path), delim);
            free(result);  // Free the old result before reassigning
            result = temp;
        // }
        current = current->next;
    }

    // Now process each subdirectory
    current = head;

    while (current != NULL) {
        if (is_directory(current->content)) {
		    
            char *full_path = ft_calloc(9999, 1);
            snprintf(full_path, 9999, "%s/%s", path, current->content);
            lstat(full_path, &buff);
            if (current->subdirectory != NULL) {  // If it's a directory with subdirectories
                // Generate content for the subdirectory
                // printf("NEW PATH: %s\n", path);
                char *subdir_res = generate_recursive_listing_result(current->subdirectory, delim, _hide_owner, _hide_group_info, current->content);

                // Append the directory name and its content
                // printf("v - %s: %s\n", current->content, print_file_info(current->content, &buff, _hide_owner, _hide_group_info, full_path));
                // printf("fullpath %s | %s\n", full_path, path);
                temp = ft_strjoin("\n", print_file_info(current->content, _hide_owner, _hide_group_info, path), "");
                // printf("TEMPPPPPP %s\n", temp);
                result = ft_strjoin(result, temp, ":\n");
                free(temp);
                result = ft_strchrjoin(result, subdir_res, '\0');
                free(subdir_res);
            }
            else {
                // char *full_path = ft_calloc(9999, 1);
                // snprintf(full_path, 9999, "%s/%s", path, current->content);
                temp = ft_strjoin("\n", print_file_info(current->content, _hide_owner, _hide_group_info, path), "");
                // printf("TEMPPPPPP %s\n", temp);
                result = ft_strjoin(result, temp, ":\n");
                result = ft_strchrjoin(result, "\n", '\0');
            }
        }
        current = current->next;
    }

    // printf("result:\n%s\n", result);
    return result;
    
}
