/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:34:46 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/20 13:52:25 by ael-asri         ###   ########.fr       */
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
void	bubble_sort(t_list	**head, int reverse_flag)
{
	int		swapped;
	t_list	*current;
	t_list	*next;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *head;
		while (current->next)
		{
			next = current->next;
			if (sort_state(current, next, reverse_flag) > 0)
				swapped = swap_nodes(current, next);
			current = current->next;
		}
	}
}

void	sort_subdirectories(t_list	*head, int reverse_flag)
{
	while (head)
	{
		if (head->subdirectory)
			sort(&head->subdirectory, reverse_flag);
		head = head->next;
	}
}

void	sort(t_list	**head, int reverse_flag)
{
	if (!head || !*head)
		return ;
	bubble_sort(head, reverse_flag);
	sort_subdirectories(*head, reverse_flag);
}
