/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:34:46 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/19 16:33:08 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int	swap_nodes(t_list	*a, t_list	*b)
{
	char	*temp_content;
	t_list	*temp_subdir;

	temp_content = a->content;
	temp_subdir = a->subdirectory;
	a->content = b->content;
	a->subdirectory = b->subdirectory;
	b->content = temp_content;
	b->subdirectory = temp_subdir;
	return (1);
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

void	sort_list(t_list	**head)
{
	t_list	*current;
	t_list	*next;
	char	*temp;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *head;
		while (current->next != NULL)
		{
			next = current->next;
			if (compare_case_sensitive(current->content, next->content) > 0)
			{
				temp = current->content;
				current->content = next->content;
				next->content = temp;
				swapped = 1;
			}
			current = current->next;
		}
	}
}

/*
	Sorting the list using bubble sort
*/
void	sort(t_list	**head, int __reverse_flag_)
{
	t_list	*current;
	t_list	*next;
	int		swapped;

	if (!*head)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *head;
		while (current->next != NULL)
		{
			next = current->next;
			if (sort_state(current, next, __reverse_flag_) > 0)
				swapped = swap_nodes(current, next);
			current = current->next;
		}
	}
	current = *head;
	while (current != NULL)
	{
		if (current->subdirectory != NULL)
			sort(&current->subdirectory, __reverse_flag_);
		current = current->next;
	}
}
