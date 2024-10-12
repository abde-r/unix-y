/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:53:33 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/10 20:25:36 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

/*
	Assigning each data type with spesific color
		-Blue for Directory
		-Cyan for Symbolic Link
		-Green Executable
		-regular files stay with no color 
*/
char	*get_file_color(const	char	*path)
{
	struct stat	file_stat;

	if (lstat(path, &file_stat) == -1)
		return (COLOR_RESET);
	if (S_ISDIR(file_stat.st_mode))
		return (COLOR_DIR);
	else if (S_ISLNK(file_stat.st_mode))
		return (COLOR_LINK);
	else if (file_stat.st_mode & S_IXUSR)
		return (COLOR_EXEC);
	else
		return (COLOR_RESET);
}

void	ft_free(char	**items)
{
	int	i;

	i = 0;
	while (items[i])
		free(items[i++]);
	free(items);
}

char	*manage_colors(t_list	*head, char	*joined_string)
{
	char		**items;
	char		*s;
	size_t		i;
	char		*temp;
	char		*temp2;
	char		*tt;

	i = 0;
	s = ft_calloc(ft_strlen(joined_string), 1);
	items = ft_split(joined_string, '\n');
	while (head != NULL && i < ft_arrlen(items))
	{
		tt = ft_substr(items[i], 0, \
		ft_strlen(items[i]) - ft_strlen(head->content));
		temp = ft_strjoin(COLOR_RESET, tt, "");
		temp2 = ft_strjoin(get_file_color(head->content), head->content, "\n");
		s = ft_custom_strjoin(s, temp, temp2);
		head = head->next;
		i++;
		free(temp);
		free(temp2);
		free(tt);
	}
	ft_free(items);
	return (s);
}
