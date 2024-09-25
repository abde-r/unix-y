/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_recursive_display.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:13:51 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/24 12:19:56 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int	is_directory_header(const char	*line)
{
	size_t	len;

	len = strlen(line);
	return (len > 0 && line[len - 1] == ':');
}

// Helper function to skip '.' and '..' entries
int	is_current_or_parent_directory(const char	*name)
{
	return (strcmp(name, "./.:") == 0 || strcmp(name, "./..:") == 0);
}

/*
	If the content is a directory header (ends with a colon)
	we print the directory name, skipping '.' and '..' directories 
	inside subdirectories, Otherwise if it's a file entry we 
	print it but skip '.' and '..'
*/
char	*manage_recursive_columns(const char	*joined_string)
{
	char	*s;
	int		in_directory;
	char	**items;
	int		i;

	s = ft_calloc(9999, 1);
	in_directory = 0;
	items = ft_split(joined_string, '\n');
	i = 0;
	while (items[i] != NULL)
	{
		if (is_directory_header(items[i]))
		{
			if (in_directory)
				ft_strcat(s, "\n");
			if (!is_current_or_parent_directory(items[i]))
				ft_strcat(s, ft_strjoin(items[i], "\n", ""));
			in_directory = 1;
		}
		else
			if (!is_current_or_parent_directory(items[i]))
				ft_strcat(s, ft_strjoin(manage_columns(items[i]), "\n", ""));
		i++;
	}
	return (s);
}
