/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:03:41 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/25 22:07:52 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

void	ft_putchr(char	*s)
{
	size_t	i;

	i = 0;
	while (s[i])
		write(2, &s[i++], 1);
}

void	freee(t_list	**head)
{
	t_list	*temp;

	temp = *head;
	*head = (*head)->next;
	free(temp->content);
	if (temp->subdirectory)
	{
		free(temp->subdirectory->content);
		free(temp->subdirectory);
	}
	free(temp);
}

void	ft_free2(t_list	**head, char	**t)
{
	free(*t);
	free(*head);
}
