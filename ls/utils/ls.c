/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:04:43 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/16 12:38:16 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

DIR *get_current_dir(char *path)
{
	DIR	*dp;

	dp = opendir(path);
	if (!dp)
	{
	    // Print an error message but continue execution.
	    // perror(path);
	    return NULL;
	}
	return (dp);
}

void recursive_subdirs(t_list *current, char *full_path) {
    t_list *subdir = NULL;
    ls_recursive(&subdir, full_path);  // Use the corrected recursive call
    while (current->next) {
        current = current->next;
    }
    current->subdirectory = subdir;
}

void ls_recursive(t_list **head, char *path) {
    struct dirent *entry;
    struct stat statbuf;
    DIR *dp = get_current_dir(path);  // Get the directory pointer

    // If directory can't be opened, just insert the node and return.
	
    if (!dp) {
		char	*unauthorized_message_error = ft_strjoin("ls:_cannot_open_directory'", path,"':_Permission_denied");
	    insert_node(head, unauthorized_message_error);  // Include the directory name anyway
        free(unauthorized_message_error);
		return;
    }

    // Traverse the directory entries
    while ((entry = readdir(dp))) {
        // Skip "." and ".." to avoid infinite recursion.
        if (!ft_strcmp(entry->d_name, ".") || !ft_strcmp(entry->d_name, ".."))
            continue;

        char *full_path = ft_strjoin(path, "/", entry->d_name);

        if (lstat(full_path, &statbuf) == -1) {
            perror(full_path);  // Handle stat errors
            free(full_path);
            continue;
        }

        insert_node(head, entry->d_name);  // Insert the file/dir name

        // Recursively explore subdirectories
        if (S_ISDIR(statbuf.st_mode)) {
            recursive_subdirs(*head, full_path);
        }

        free(full_path);  // Free the constructed path
    }
    closedir(dp);  // Close the directory
}


/*
	If it's a directory, just print the directory name
	Otherwise if it's not a directory, also print the file name
*/
char	*ls_d(char	*path)
{
	if (is_directory(path))
		return ((char *)path);
	else
		return ((char *)path);
}

void ls(t_list **head, char *path) {
    struct dirent *entry;
    DIR *dp;
    struct stat statbuf;

    // Check if the given path is a file or directory
    if (lstat(path, &statbuf) == -1)
	{
        perror("lstat");
        exit(1);
    }
	if (S_ISREG(statbuf.st_mode))
	{
        insert_node(head, path); // Insert the file into the linked list
        return ;
    }
	dp = opendir(path);
    if (dp == NULL)
	{
        perror("opendir");
        exit(1);
    }

    while ((entry = readdir(dp)) != NULL) {
        char *full_path = malloc(strlen(path) + strlen(entry->d_name) + 2);
        sprintf(full_path, "%s/%s", path, entry->d_name);

        if (lstat(full_path, &statbuf) == -1) {
            perror("lstat");
            free(full_path);
            continue;
        }
        insert_node(head, entry->d_name);
        free(full_path);
    }

    closedir(dp);
}

char	*ft_ls(t_list	**head, char	*opts, char	*path)
{
	char		*final_res;

	if (ft_strchr(opts, 'd'))
		final_res = ls_d(path);
	else
	{
		if (ft_strchr(opts, 'R'))
			ls_recursive(head, path);
		else if (!ft_strchr(opts, 'R'))
			ls(head, path);
		final_res = executer(head, opts, path);
	}
	return (final_res);
}
