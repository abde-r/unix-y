/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:04:43 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/06 15:31:31 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

void ls_R(t_list** head, char* path) {
    DIR* dp = opendir(path);
    if (dp == NULL) {
        perror("opendir");
        return;
    }

    struct dirent* entry;
    struct stat statbuf;

    // Create the root directory node with name "."
    t_list* root = create_node(path);
    insert_node(head, ".");

    // Read the contents of the directory
    while ((entry = readdir(dp)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct the full path
        char full_path[999];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        // Insert the entry (file or directory) into the root's subdirectory list
        insert_node(&(root->subdirectory), entry->d_name);

        // Check if it's a directory
        if (stat(full_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
            t_list* subdir = NULL;
            ls_R(&subdir, full_path); // Recursively list the subdirectory

            // Find the node we just inserted and attach the subdirectory list
            t_list* current = root->subdirectory;
            while (current->next) {
                current = current->next;
            }
            current->subdirectory = subdir;
        }
    }

    // Insert the root directory node into the list
    *head = root;

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
	// sort_list(head);
}