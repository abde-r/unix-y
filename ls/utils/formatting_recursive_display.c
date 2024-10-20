/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_recursive_display.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:13:51 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/20 18:36:50 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int	is_directory_header(char	*line)
{
	size_t	len;

	len = strlen(line);
	return (len > 0 && line[len - 1] == ':');
}

int	is_current_or_parent_directory(char	*name)
{
	return (!ft_strcmp(name, "./.:") || \
	!ft_strcmp(name, "./..:"));
}

char	*get_temp_normm(char	*item, int	*in_directory)
{
	char	*temp;

	temp = ft_strjoin("\n", item, "\n");
	*in_directory = 1;
	return (temp);
}

/*
	If the content is a directory header (ends with a colon)
	we print the directory name, skipping '.' and '..' directories 
	inside subdirectories, Otherwise if it's a file entry we 
	print it but skip '.' and '..'
*/
char	*manage_recursive_columns(char	*joined_string)
{
	char	**items;
	char	*s;
	char	*temp;
	int		in_directory;
	int		i;

	s = ft_strdup("");
	in_directory = 0;
	items = ft_split(joined_string, '\n');
	i = 0;
	while (items[i] != NULL)
	{
		if (!is_current_or_parent_directory(items[i]))
		{
			if (is_directory_header(items[i]))
				temp = get_temp_normm(items[i], &in_directory);
			else
				temp = manage_columns(items[i]);
			s = ft_custom_strjoin(s, temp, "");
			free(temp);
		}
		i++;
	}
	ft_free(items);
	return (s);
}
