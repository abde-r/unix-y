/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:46:51 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/18 10:47:30 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

void	free_subdirectory(t_list *subdir)
{
	t_list	*temp;

	while (subdir != NULL)
	{
		temp = subdir;
		subdir = subdir->next;
		free(temp->content);
		if (temp->subdirectory != NULL)
			free_subdirectory(temp->subdirectory);
		free(temp);
	}
}

void	outer_free(t_list	*head, char	**opts, \
char	**path, char	**final_res)
{
	t_list	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->content);
		if (temp->subdirectory)
			free_subdirectory(temp->subdirectory);
		free(temp);
	}
	free(head);
	free(*opts);
	free(*path);
	free(*final_res);
}
