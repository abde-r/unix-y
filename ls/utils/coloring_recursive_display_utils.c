/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_recursive_display_tils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:21:20 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/25 15:21:49 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int	return_error(char	*err)
{
	perror(err);
	return (0);
}

/*
	Each block is 512 bytes, so print the total blocks
*/
int	get_dir_total(const char	*path)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		file_stat;
	int				total_blocks;

	total_blocks = 0;
	dir = opendir(path);
	if (dir == NULL)
		return_error("opendir");
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (!ft_strcmp(entry->d_name, ".") || !ft_strcmp(entry->d_name, ".."))
			continue ;
		if (stat(ft_strjoin(path, "/", entry->d_name), &file_stat) == -1)
		{
			perror("stat");
			continue ;
		}
		total_blocks += file_stat.st_blocks;
	}
	closedir(dir);
	return (total_blocks / 2);
}

char	*add_color(char	*s)
{
	char		**t;
	char		*data;

	t = ft_split(s, ' ');
	data = ft_strjoin(COLOR_RESET, ft_substr(s, 0, ft_strlen(s) - \
	ft_strlen(t[ft_arrlen(t) - 1])), get_file_color(t[ft_arrlen(t) - 1]));
	data = ft_strjoin(data, t[ft_arrlen(t) - 1], COLOR_RESET);
	data = ft_strjoin(data, "\n", "");
	return (data);
}
