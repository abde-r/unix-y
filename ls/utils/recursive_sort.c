/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:38:08 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/23 19:20:18 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int	reverse_compare_case_sensitive(const char	*a, const char	*b)
{
	char	lower_a;
	char	lower_b;

	while (*a && *b)
	{
		lower_a = ft_tolower(*a);
		lower_b = ft_tolower(*b);
		if (lower_a != lower_b)
			return (lower_b - lower_a);
		a++;
		b++;
	}
	return (*b - *a);
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

// Sorting the list using bubble sort
void	sort_recursive_list(t_list	**head, int __reverse_flag_)
{
	t_list	*current;
	t_list	*next;
	int		swapped;

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
			sort_recursive_list(&current->subdirectory, __reverse_flag_);
		current = current->next;
	}
}

// Recursive function to sort directories
// and their contents by modification time
void	sort_recursive_by_time(t_list	**head, const char	*path, int __flag_)
{
	t_list	*current;
	char	*full_path;

	current = *head;
	if (!__flag_)
		sort_by_time(head, path);
	else if (__flag_ == 1)
		sort_by_access_time(head, path);
	while (current != NULL)
	{
		if (is_directory(current->content))
		{
			full_path = ft_strjoin(path, "/", current->content);
			sort_recursive_by_time(&(current->subdirectory), \
			full_path, __flag_);
		}
		current = current->next;
	}
}
