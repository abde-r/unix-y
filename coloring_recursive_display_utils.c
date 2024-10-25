/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_recursive_display_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:21:20 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/20 21:19:29 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int	return_error(char	*err)
{
	perror(err);
	return (-1);
}

int	condition_norm(char	*name, char	*path, struct stat *file_stat)
{
	char	*full_path;

	full_path = ft_strjoin(path, "/", name);
	if (!ft_strcmp(name, ".") || \
	!ft_strcmp(name, "..") || \
	stat(full_path, file_stat) == -1)
	{
		free(full_path);
		return (1);
	}
	free(full_path);
	return (0);
}

/*
	total number of 512-byte blocks allocated for all the files 
	and directories listed. Each block is 512 bytes, 
	so print the total blocks
*/
int	get_dir_total(char	*path)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		file_stat;
	int				total_blocks;

	total_blocks = 0;
	dir = opendir(path);
	if (!dir)
		return (-1);
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (condition_norm(entry->d_name, path, &file_stat))
			continue ;
		total_blocks += file_stat.st_blocks;
	}
	closedir(dir);
	return (total_blocks);
}

char	*add_color(char	*s)
{
	char	**t;
	char	*data;
	char	*temp;

	t = ft_split(s, ' ');
	temp = ft_substr(s, 0, ft_strlen(s) - \
	ft_strlen(t[ft_arrlen(t) - 1]));
	data = ft_strjoin(COLOR_RESET, temp, get_file_color(t[ft_arrlen(t) - 1]));
	data = ft_custom_strjoin(data, t[ft_arrlen(t) - 1], COLOR_RESET);
	data = ft_custom_strjoin(data, "\n", "");
	free(temp);
	ft_free(t);
	return (data);
}
