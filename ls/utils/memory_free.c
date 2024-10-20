/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 10:46:51 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/20 19:56:20 by ael-asri         ###   ########.fr       */
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
char	**final_res)
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
	free(*final_res);
}

char	*get_file_info_temp(t_list	*current, t_owner_group_info \
info, char	*path)
{
	char	*s;
	char	*file_infos;
	char	*temp;

	file_infos = print_file_info(current->content, info, path);
	temp = ft_strjoin("\n", file_infos, "");
	s = ft_strjoin(file_infos, temp, ":\n\n");
	free(temp);
	free(file_infos);
	return (s);
}

char	*get_temp(t_list	*current, char delim)
{
	char	*temp1;
	char	*temp2;
	char	*s;

	temp1 = ft_strjoin("\n./", current->content, ":\n");
	temp2 = generate_recursive_result(current->subdirectory, delim);
	s = ft_strjoin(temp1, temp2, "");
	free(temp1);
	free(temp2);
	return (s);
}
