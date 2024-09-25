/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:04:43 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/25 17:12:30 by ael-asri         ###   ########.fr       */
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

/*
	list content and subdirectories recursively
*/
void	ls_recursive(t_list	**head, DIR	*dp, const char	*path)
{
	struct dirent	*entry;
	struct stat		statbuf;
	t_list			*current;
	t_list			*subdir;

	dp = get_current_dir(path);
	while (1)
	{
		entry = readdir(dp);
		if (!entry)
			break ;
		if (lstat(ft_strjoin(path, "/", entry->d_name), &statbuf) == -1)
			continue ;
		insert_node(head, entry->d_name);
		if (!ft_strcmp(entry->d_name, ".") || !ft_strcmp(entry->d_name, ".."))
			continue ;
		if (S_ISDIR(statbuf.st_mode))
		{
			subdir = NULL;
			ls_recursive(&subdir, dp, ft_strjoin(path, "/", entry->d_name));
			current = *head;
			while (current->next != NULL)
				current = current->next;
			current->subdirectory = subdir;
		}
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

void	ls(t_list	**head, const char	*path)
{
	struct dirent	*entry;
	DIR				*dp;

	dp = opendir(path);
	if (dp == NULL)
	{
		perror("opendir");
		exit(1);
	}
	while (1)
	{
		entry = readdir(dp);
		if (!entry)
			break ;
		insert_node(head, entry->d_name);
	}
	closedir(dp);
}
