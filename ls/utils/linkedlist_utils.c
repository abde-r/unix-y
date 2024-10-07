/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:26:48 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/07 14:04:51 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

t_list	*create_node(char const *content)
{
	t_list	*new_node;

	new_node = ft_calloc(1, sizeof(t_list));
	if (!new_node)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	new_node->subdirectory = NULL;
	return (new_node);
}

void	insert_node(t_list	**head, char	const *content)
{
	t_list	*new_node;
	t_list	*current;

	new_node = create_node(content);
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	reverse_order(t_list	**output)
{
	t_list	*prev;
	t_list	*current;
	t_list	*next;

	prev = NULL;
	current = *output;
	next = NULL;
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*output = prev;
}

int	ft_lstcontentsize(t_list	*lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count += (ft_strlen(lst->content) + 1);
		lst = lst->next;
	}
	return (count);
}
