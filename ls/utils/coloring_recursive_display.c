/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_recursive_display.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:40:43 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/16 13:05:53 by ael-asri         ###   ########.fr       */
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

char	*total_dir(char	*dir)
{
	if (ft_strcmp(dir, ".") && ft_strcmp(dir, ".."))
		return (get_total_dir(dir));
	return ("");
}

char	*manage_recursive_colors(char	**items, int in_directory)
{
	char	**dir;
	char	*s;
	char	*total_dirs;
	char	*color;
	size_t	i;

	s = ft_strdup("");
	i = 0;
	while (i < ft_arrlen(items))
	{
		if (items[i][strlen(items[i]) - 1] == ':')
		{
			if (in_directory)
				s = ft_custom_strjoin(s, "\n", "");
			dir = get_dir(items[i]);
			total_dirs = total_dir(dir[ft_arrlen(dir) - 1]);
			if (ft_strlen(total_dirs))
				s = ft_custom_strjoin(s, total_dirs, "");
			ft_free(dir);
			in_directory = 1;
			i++;
			if (ft_strlen(total_dirs))
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
