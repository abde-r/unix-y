/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:26:48 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/01 12:40:36 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

t_list	*create_node(const char *content)
{
	// t_list	*ptr;

	// ptr = malloc(sizeof(t_list));
	// if (ptr == NULL)
	// 	return (0);
	// if (content == 0)
	// 	ptr->content = NULL;
	// else
	// 	ptr->content = content;
	// ptr->next = NULL;
	// return (ptr);

	t_list *new_node = (t_list*)malloc(sizeof(t_list));
    if (!new_node) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }
	// ft_strcat(new_node->content, content);
	new_node->content = ft_strdup(content);
    new_node->next = NULL;
    new_node->subdirectory = NULL;
    return new_node;
}

void	insert_node(t_list **head, const char   *content)
{
	// t_list	*list;
    // t_list  *new = ft_lstnew(content);

	// list = *lst;
	// if (*lst == 0)
	// {
	// 	*lst = new;
	// 	return ;
	// }
	// while (list->next != NULL)
	// {
	// 	list = list->next;
	// }
	// list->next = new;

	t_list *new_node = create_node(content);
	t_list *current;
	
    if (*head == NULL) {
        *head = new_node;
    } else {
        current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void swap_nodes(t_list* a, t_list* b) {
	
    char* temp = a->content;
    a->content = b->content;
    b->content = temp;
}

int	ft_lstcontentsize(t_list *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		count+=(ft_strlen(lst->content)+1);
		lst = lst->next;
	}
	return (count);
}
