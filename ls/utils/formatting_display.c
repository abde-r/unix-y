/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_display.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:49:56 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/27 16:52:09 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

/*
	Get the Max length + 2 for padding and 
	if num of rows is 0 ensure at least one column
*/
int	*get_num_col_rows(int max_len, int count)
{
	int		*_num_col_rows;

	_num_col_rows = ft_calloc(2, 0);
	_num_col_rows[1] = get_terminal_width() / (max_len + 2);
	_num_col_rows[0] = (count + _num_col_rows[1] - 1) / _num_col_rows[1];
	if (_num_col_rows[1] == 0)
		_num_col_rows[1] = 1;
	return (_num_col_rows);
}

/*
	Printing each item in its column after 
	getting a Rough estimate of total size (including color codes)
*/
char	*print_in_columns(char **items, int count, int max_len)
{
	char	*s;
	int		*_num_col_rows;
	int		row;
	int		col;
	int		estimated_size;

	_num_col_rows = get_num_col_rows(max_len, count);
	estimated_size = (max_len + 2 + 10) * count + _num_col_rows[0];
	s = ft_calloc(estimated_size, 1);
	row = 0;
	while (row < _num_col_rows[0])
	{
		col = 0;
		while (col < _num_col_rows[1])
		{
			ft_strcat(s, get_content_color(items[row + col * _num_col_rows[0]], \
			max_len, row + col * _num_col_rows[0], count));
			col++;
		}
		ft_strcat(s, "\n");
		row++;
	}
	return (s);
}

char	*manage_columns(char	*joined_string)
{
	int		count;
	char	**items;
	int		max_len;
	char	*s;
	int		i;

	count = 0;
	items = ft_split(joined_string, ' ');
	while (items[count])
		count++;
	if (count == 0)
		return ("");
	max_len = calculate_max_len(items, count);
	s = print_in_columns(items, count, max_len);
	i = 0;
	while (i < count)
		free(items[i++]);
	free(items);
	return (s);
}
