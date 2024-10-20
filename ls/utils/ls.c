/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 10:04:43 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/19 22:02:17 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

DIR	*get_current_dir(const char	*path)
{
	DIR	*dp;

	dp = opendir(path);
	if (dp == NULL)
		return (NULL);
	return (dp);
}

void	recursive_subdirs(t_list	*current, char	*full_path)
{
	t_list	*subdir;

	subdir = NULL;
	ls_recursive(&subdir, full_path);
	while (current->next != NULL)
		current = current->next;
	current->subdirectory = subdir;
}

/*
	list content and subdirectories recursively
*/
void	ls_recursive(t_list	**head, char	*path)
{
	DIR				*dp;
	struct dirent	*entry;
	struct stat		statbuf;

	dp = get_current_dir(path);
	if (!dp)
	{
		unauth_message(head, path);
		return ;
	}
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
			recursive_subdirs(*head, ft_strjoin(path, "/", entry->d_name));
	}
	closedir(dp);
}

void	ls(t_list	**head, char	*path)
{
	struct dirent	*entry;
	DIR				*dp;
	struct stat		statbuf;

	lstat(path, &statbuf);
	if (S_ISREG(statbuf.st_mode))
	{
		insert_node(head, path);
		return ;
	}
	dp = opendir(path);
	if (!dp)
	{
		unauth_message(head, path);
		return ;
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

char	*ft_ls(t_list	**head, char	*opts, char	*path)
{
	char	*final_res;

	if (ft_strchr(opts, 'd'))
		final_res = ft_strdup((char *)path);
	else
	{
		if (ft_strchr(opts, 'R'))
			ls_recursive(head, path);
		else
			ls(head, path);
		final_res = executer(head, opts, path);
	}
	return (final_res);
}
