/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:48:07 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/26 19:01:20 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

void	delete_null_nodes(t_list	**head)
{
	t_list	*current;
	t_list	*prev;
	t_list	*temp;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (current->content == NULL)
		{
			temp = current;
			current = current->next;
			if (prev == NULL)
				*head = current;
			else
				prev->next = current;
			free(temp);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

int	custom_compare(char	*a, char	*b)
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

t_list	*create_nnode(char	*path, char	*content)
{
	t_list	*new_node;

	new_node = ft_calloc(1, sizeof(t_list));
	if (!new_node)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	new_node->content = ft_strdup(path);
	new_node->next = NULL;
	new_node->subdirectory = create_node(content);
	return (new_node);
}

void	insert_nnode(t_list	**head, char	*path, char	*content)
{
	t_list	*new_node;
	t_list	*current;
	char	*temp;

	temp = ft_substr(content, 0, ft_strlen(content));
	if (temp[ft_strlen(temp) - 1] == '\n')
		temp = ft_substr(content, 0, ft_strlen(content) - 1);
	new_node = create_nnode(path, temp);
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	free(temp);
}
