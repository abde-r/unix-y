/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:53:33 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/24 14:31:22 by ael-asri         ###   ########.fr       */
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
	char		*temp;
	int			count;
	int			i;

	i = 0;
	count = 0;
	s = ft_calloc(9999, 1);
	items = ft_split(joined_string, '\n');
	while (items[count])
		count++;
	while (head != NULL && i < count)
	{
		temp = ft_calloc(1024, 1);
		snprintf(temp, 1024, "%s%s%s%s", COLOR_RESET, ft_substr(items[i], 0 \
		, ft_strlen(items[i]) - ft_strlen(head->content)) \
		, get_file_color(head->content), head->content);
		ft_strcat(s, ft_strjoin(temp, "\n", ""));
		head = head->next;
		i++;
	}
	ft_free(items);
	return (s);
}
