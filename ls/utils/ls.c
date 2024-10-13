/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:04:43 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/13 15:55:19 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

DIR	*get_current_dir(const char	*path)
{
	DIR	*dp;

	dp = opendir(path);
	if (dp == NULL)
	{
		perror("opendir");
		exit(1);
	}
	return (dp);
}

void	recursive_subdirs(t_list	*current, DIR *dp, char	*full_path)
{
	t_list	*subdir;

	subdir = NULL;
	ls(&subdir, dp, full_path);
	while (current->next != NULL)
		current = current->next;
	current->subdirectory = subdir;
}

/*
	list content and subdirectories recursively
*/
void	ls(t_list	**head, DIR	*dp, char	*path)
{
	struct dirent	*entry;
	struct stat		statbuf;
	char			*full_path;

	dp = get_current_dir(path);
	while (1)
	{
		entry = readdir(dp);
		if (!entry)
			break ;
		full_path = ft_strjoin(path, "/", entry->d_name);
		if (lstat(full_path, &statbuf) == -1)
		{
			free(full_path);
			continue ;
		}
		insert_node(head, entry->d_name);
		if (!ft_strcmp(entry->d_name, ".") || !ft_strcmp(entry->d_name, ".."))
		{
			free(full_path);
			continue ;
		}
		if (S_ISDIR(statbuf.st_mode))
			recursive_subdirs(*head, dp, full_path);
		free(full_path);
	}
	closedir(dp);
}

/*
	If it's a directory, just print the directory name
	Otherwise if it's not a directory, also print the file name
*/
char	*ls_d(const char	*path)
{
	if (is_directory(path))
		return ((char *)path);
	else
		return ((char *)path);
}
