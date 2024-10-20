/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_recursive_display.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:40:43 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/20 19:43:34 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

/*
	getting the dir line by Update current directory 
	and print header then removing the colon
*/
char	**get_dir(char	*s)
{
	char	**temps;
	char	*current_dir;

	current_dir = ft_substr(s, 0, ft_strlen(s) - 1);
	temps = ft_split(current_dir, ' ');
	free(current_dir);
	return (temps);
}

char	*get_total_dir(char	*s)
{
	char	*t;
	char	*temp;
	char	*temp_itoa;
	int		total_dir;

	t = ft_strjoin("\n./", s, ":\n");
	total_dir = get_dir_total(s);
	if (total_dir != -1)
	{
		temp_itoa = ft_itoa(total_dir);
		temp = ft_strjoin("total ", temp_itoa, "\n");
		t = ft_custom_strjoin(t, temp, "");
		free(temp_itoa);
		free(temp);
	}
	return (t);
}

char	*total_dir(char	*item, int	*in_directory)
{
	char	**dirs;
	char	*dir;
	char	*t;

	dirs = get_dir(item);
	dir = dirs[ft_arrlen(dirs) - 1];
	if (ft_strcmp(dir, ".") && ft_strcmp(dir, ".."))
		t = get_total_dir(dir);
	else
		t = ft_strdup("");
	*in_directory = 1;
	ft_free(dirs);
	return (t);
}

char	*total_dir_norm(char	*path)
{
	char	*itoa_dir_total;
	char	*_dir_total;

	if (is_directory(path) && get_dir_total(path) >= 0)
	{
		_dir_total = ft_itoa(get_dir_total(path));
		itoa_dir_total = ft_strjoin("total ", _dir_total, "\n");
		free(_dir_total);
		return (itoa_dir_total);
	}
	else
		return (ft_strdup(""));
}

char	*manage_recursive_colors(char	**items, char	*path, int in_directory)
{
	char	*s;
	char	*total_dirs;
	char	*color;
	size_t	i;

	i = 0;
	s = total_dir_norm(path);
	while (i < ft_arrlen(items))
	{
		if (items[i][strlen(items[i]) - 1] == ':')
		{
			total_dirs = total_dir(items[i], &in_directory);
			s = ft_custom_strjoin(s, total_dirs, "");
			i++;
			free(total_dirs);
			continue ;
		}
		color = add_color(items[i]);
		s = ft_custom_strjoin(s, color, "");
		free(color);
		i++;
	}
	i = 0;
	ft_free(items);
	return (s);
}
