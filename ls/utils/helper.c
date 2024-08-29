/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:38:25 by ael-asri          #+#    #+#             */
/*   Updated: 2024/08/29 16:42:57 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"



char	*generate_final_res(t_list *output, char delim) {
	char *t = ft_calloc(999, 1);
	
	while (output != NULL) {
		if (output->next != NULL)
			t = ft_strchrjoin(t, output->content, delim);
		else
			t = ft_strchrjoin(t, output->content, '\0');
		output = output->next;
	}

	return t;
}

void	remove_hiddens(t_list **output) {
	t_list* current = *output;
    t_list* prev = NULL;

    // Iterate over the linked list
    while (current != NULL) {
        if (current->content[0] == '.') {
            if (prev == NULL) {
                // This node is the head of the list
                *output = current->next;
                // free(current->content);
                free(current);
                current = *output;
            } else {
                // This node is not the head, remove it from the list
                prev->next = current->next;
                free(current->content);
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void ls_R(t_list **output, char *path, int depth) {
    struct dirent *entry;
    struct stat statbuf;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    // Print the directory name
    if (depth > 0) {
        printf("\n");
    }
    printf("%s:\n", path);

    while ((entry = readdir(dp)) != NULL) {
        // Skip "." and ".."
        if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path to the file or directory
        char full_path[1024];
        full_path[0] = '\0'; // Initialize the full_path to an empty string
        ft_strcat(full_path, path);
        ft_strcat(full_path, "/");
        ft_strcat(full_path, entry->d_name);

        // Get file status
        if (stat(full_path, &statbuf) == -1) {
            perror("stat");
            continue;
        }

        // Print file or directory name
        if (S_ISDIR(statbuf.st_mode)) {
            printf("%s/\n", entry->d_name);
            // Recursively list subdirectories
            ls_R(output, full_path, depth + 1);
        } else {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dp);
}

void    ls(t_list   **output, char *path) {
    
	struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        ft_lstadd(output, entry->d_name);

        // Exclude the current and parent directory entries ('.' and '..')
        // if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
        //     printf("%s\n", entry->d_name);
        // }
    }

    closedir(dp);
	sort_list(output);
    // DIR *dir = opendir(path);
    // struct dirent *file;
    // // dir = ;
    // if (dir) {
    //     while ((file = readdir(dir)))
    //         // if (file->d_name[0] == '.')
    //         //     flag && printf("%s ", file->d_name);
    //         // else
    //         // t_list *node = ft_lstnew(file->d_name);
    //         ft_lstadd(output, file->d_name);
    //         // output[0] = strdup(file->d_name);
    //             // printf("%s ", file->d_name);
    //     // closedir(dir);
    // free(file);
    // }
    // free(dir);
}

char	*opts_executer(t_list *output, char *opts) {
    
	char *t = malloc(999);
    // 1- a
    // 2- t
    // 3- r
    // 4- l
    
    if (!ft_strchr(opts, 'a')) // remove hidden files and dirs => anything start with a dot
		remove_hiddens(&output);
    if (ft_strchr(opts, 't')) // sort by time
		sort_by_time(&output);
    if (ft_strchr(opts, 'r')) // reverse the order
		reverse_order(&output);
	
	if (ft_strchr(opts, 'l')) // generate a string joined by new line
		t = generate_final_res(output, '\n');
	else if (!ft_strchr(opts, 'l')) // generate a string joined by space
		t = generate_final_res(output, ' ');

	return t;
    
}