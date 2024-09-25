/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:58:25 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/25 17:07:12 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

/*
	The default value of terminal size is set to 80
	columns if it cannot be determined
*/
int	get_terminal_width(void)
{
	struct winsize	w;
	int				st;

	st = ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (st == -1)
	{
		perror("ioctl");
		return (80);
	}
	return (w.ws_col);
}

/*
	calculating the maximum item length for formatting columns
*/
size_t	calculate_max_len(char	**items, int count)
{
	size_t	max_len;
	size_t	len;
	int		i;

	i = 0;
	max_len = 0;
	while (i < count)
	{
		len = ft_strlen(items[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

char	*get_content_color(char	*s, int max_len, int index, int count)
{
	char	*t;
	char	*temp;

	t = ft_calloc(9999, 1);
	temp = ft_calloc(9999, 1);
	if (index < count)
	{
		snprintf(temp, 9999, "%s%-*s%s", get_file_color(s), max_len + 2, s, COLOR_RESET);
		ft_strcat(t, temp);
	}
	return (t);
}
