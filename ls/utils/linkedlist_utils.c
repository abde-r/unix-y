/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linkedlist_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 12:26:48 by ael-asri          #+#    #+#             */
/*   Updated: 2024/08/29 15:02:45 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*ptr;

	ptr = malloc(sizeof(t_list));
	if (ptr == NULL)
		return (0);
	if (content == 0)
		ptr->content = NULL;
	else
		ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}

void	ft_lstadd(t_list **lst, char   *content)
{
	t_list	*list;
    t_list  *new = ft_lstnew(content);

	list = *lst;
	if (*lst == 0)
	{
		*lst = new;
		return ;
	}
	while (list->next != NULL)
	{
		list = list->next;
	}
	list->next = new;
}

void swap_nodes(t_list* a, t_list* b) {
	
    char* temp = a->content;
    a->content = b->content;
    b->content = temp;
}
