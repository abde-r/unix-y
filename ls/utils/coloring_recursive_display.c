/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_recursive_display.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:40:43 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/27 16:51:46 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

/*
	getting the dir line by Update current directory 
	and print header then removing the colon
*/
char	**get_dir(char	*s)
{
	char		*current_dir;

	current_dir = ft_calloc(ft_strlen(s), 1);
	strncpy(current_dir, s, strlen(s) - 1);
	current_dir[ft_strlen(s) - 1] = '\0';
	return (ft_split(current_dir, ' '));
}

char	*get_total_dir(char	*s)
{
	char	*t;

	t = ft_calloc(ft_strlen(s), 1);
	t = ft_strjoin("\n./", s, ":\n");
	ft_strcat(t, ft_strjoin("total ", ft_itoa(get_dir_total(s)), "\n"));
	return (t);
}

char	*total_dir(char	*dir)
{
	char	*s;

	s = ft_strdup("");
	if (ft_strcmp(dir, ".") && ft_strcmp(dir, ".."))
		s = get_total_dir(dir);
	return (s);
}

char	*manage_recursive_colors(char	**items, int in_directory)
{
	char		**dir;
	char		*s;
	size_t		i;

	s = ft_strdup("");
	i = 0;
	while (i < ft_arrlen(items))
	{
		if (items[i][strlen(items[i]) - 1] == ':')
		{
			if (in_directory)
				ft_strcat(s, "\n");
			dir = get_dir(items[i]);
			s = ft_strjoin(s, total_dir(dir[ft_arrlen(dir) - 1]), "");
			in_directory = 1;
			i++;
			continue ;
		}
		s = ft_strjoin(s, add_color(items[i]), "");
		i++;
	}
	i = 0;
	ft_free(items);
	return (s);
}
