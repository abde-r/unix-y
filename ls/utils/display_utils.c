/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:58:25 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/20 19:26:04 by ael-asri         ###   ########.fr       */
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

char	*pad_string(char *str, int max_len)
{
	char	*result;
	size_t	len;
	int		padding_len;
	int		i;

	len = ft_strlen(str);
	padding_len = max_len - len;
	if (padding_len < 0)
		padding_len = 0;
	result = ft_calloc(max_len + 1, 1);
	ft_strcat(result, str);
	i = len;
	while (i < max_len)
		result[i++] = ' ';
	result[i] = '\0';
	return (result);
}

char	*get_content_color(char	*s, int max_len, int index, int count)
{
	char	*t;
	char	*temp_pad;

	if (index < count)
	{
		temp_pad = pad_string(s, max_len + 2);
		t = ft_strjoin(get_file_color(s), temp_pad, COLOR_RESET);
		free(temp_pad);
		return (t);
	}
	return (ft_strdup(""));
}
