/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:19:50 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/20 13:52:31 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int	reverse_compare_case_sensitive(const char	*a, const char	*b)
{
	char	lower_a;
	char	lower_b;

	while (*a && *b)
	{
		lower_a = *a;
		lower_b = *b;
		if (lower_a != lower_b)
			return (lower_b - lower_a);
		a++;
		b++;
	}
	return (*b - *a);
}

int	compare_case_sensitive(char	*a, char	*b)
{
	char	lower_a;
	char	lower_b;

	while (*a && *b)
	{
		lower_a = *a;
		lower_b = *b;
		if (lower_a != lower_b)
			return (lower_a - lower_b);
		a++;
		b++;
	}
	return (*a - *b);
}

int	sort_state(t_list	*current, t_list	*next, int __reverse_flag_)
{
	int	_sort_stat;

	_sort_stat = -1;
	if (!__reverse_flag_)
		_sort_stat = compare_case_sensitive(current->content, \
		next->content);
	else if (__reverse_flag_ == 1)
		_sort_stat = reverse_compare_case_sensitive(current->content, \
		next->content);
	return (_sort_stat);
}
