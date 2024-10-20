/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_display.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:49:56 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/20 19:01:23 by ael-asri         ###   ########.fr       */
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

	_num_col_rows = ft_calloc(2, sizeof(int));
	_num_col_rows[1] = get_terminal_width() / (max_len + 2);
	_num_col_rows[0] = (count + _num_col_rows[1] - 1) / _num_col_rows[1];
	if (_num_col_rows[1] == 0)
		_num_col_rows[1] = 1;
	return (_num_col_rows);
}

void	get__num_col_rows(int	*_num_col_rows, int max_len, int count)
{
	_num_col_rows[1] = get_terminal_width() / (max_len + 2);
	_num_col_rows[0] = (count + _num_col_rows[1] - 1) / _num_col_rows[1];
	if (_num_col_rows[1] == 0)
		_num_col_rows[1] = 1;
}

/*
	just get_content_color func splitted due to the shitty norminette
*/
char	*_color(char	**items, int *col_row, \
int	*_num_col_rows, int max_len)
{
	return (get_content_color(items[col_row[0] + col_row[1] * \
	_num_col_rows[0]], max_len, col_row[0] + col_row[1] * \
	_num_col_rows[0], ft_arrlen(items)));
}

/*
	Printing each item in its column after 
	getting a Rough estimate of total size (including color codes)
*/
char	*print_in_columns(char	**items, int count, int max_len)
{
	char	*s;
	char	*color;
	int		_num_col_rows[2];
	int		col_row[2];

	get__num_col_rows(_num_col_rows, max_len, count);
	s = ft_calloc((max_len + 2 + 10) * count + _num_col_rows[0], 1);
	col_row[0] = 0;
	while (col_row[0] < _num_col_rows[0])
	{
		col_row[1] = 0;
		while (col_row[1] < _num_col_rows[1])
		{
			if ((col_row[0] + col_row[1] * _num_col_rows[0]) < count)
			{
				color = _color(items, col_row, _num_col_rows, max_len);
				s = ft_custom_strjoin(s, color, "");
				free(color);
			}
			col_row[1]++;
		}
		s = ft_custom_strjoin(s, "\n", "");
		col_row[0]++;
	}
	return (s);
}

char	*manage_columns(char	*joined_string)
{
	char	**items;
	int		max_len;
	char	*s;
	size_t	i;

	items = ft_split(joined_string, ' ');
	max_len = calculate_max_len(items, ft_arrlen(items));
	s = print_in_columns(items, ft_arrlen(items), max_len);
	i = 0;
	while (i < ft_arrlen(items))
		free(items[i++]);
	free(items);
	return (s);
}
