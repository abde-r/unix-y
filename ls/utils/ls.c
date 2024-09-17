/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:04:43 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/16 22:50:19 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

void ls_R(t_list **head, const char *path) {
    DIR *dp = opendir(path);
    struct dirent *entry;
    struct stat statbuf;

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    // Add current directory to the list
    while ((entry = readdir(dp)) != NULL) {
        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (lstat(full_path, &statbuf) == -1) {
            perror("lstat");
            continue;
        }

        // Insert all files and directories, including `.` and `..`
        insert_node(head, entry->d_name);

        // Skip recursion for special directories "." and ".." to avoid infinite loop
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // If it's a directory, recursively handle subdirectories
        if (S_ISDIR(statbuf.st_mode)) {
            t_list *subdir_head = NULL;
            ls_R(&subdir_head, full_path);
            
            // Find the last node of the current directory and attach subdirectories
            t_list *current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->subdirectory = subdir_head;
        }
    }

    closedir(dp);
}

char	*ls_d(const char *path) {
    if (is_directory(path)) {
        // If it's a directory, just print the directory name
        // printf("%s\n", path);
        // insert_node(head, (char*)path);

        return (char*)path;
    } else {
        // If it's not a directory, also print the file name
        // printf("%s\n", path);
        // insert_node(head, (char*)path);

        return (char*)path;
    }
}

void	ls(t_list	**head, const char *path) {
    
	struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp))) {
        insert_node(head, entry->d_name);
    }

    closedir(dp);
}
