/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_recursive_display_utils.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 15:21:20 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/13 15:46:43 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int	return_error(char	*err)
{
	perror(err);
	return (-1);
}

/*
	Each block is 512 bytes, so print the total blocks
*/
int	get_dir_total(char	*path)
{
	DIR				*dir;
	struct dirent	*entry;
	struct stat		file_stat;
	int				total_blocks;
	char			*full_path;

	total_blocks = 0;
	dir = opendir(path);
	if (dir == NULL)
		return_error("opendir");
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		full_path = ft_strjoin(path, "/", entry->d_name);
		if (!ft_strcmp(entry->d_name, ".") || !ft_strcmp(entry->d_name, ".."))
		{
			free(full_path);
			continue ;
		}
		if (stat(full_path, &file_stat) == -1)
		{
			perror("stat");
			free(full_path);
			continue ;
		}
		free(full_path);
		total_blocks += file_stat.st_blocks;
	}
	closedir(dir);
	return (total_blocks / 2);
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
