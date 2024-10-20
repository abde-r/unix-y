/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:13:50 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/20 17:23:56 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

char	*generate_result(t_list	*head, char delim)
{
	struct stat	file_stat;
	char		*t;
	char		*temp;

	t = ft_strdup("");
	while (head != NULL)
	{
		lstat(head->content, &file_stat);
		if (head->next != NULL)
			temp = ft_strchrjoin(t, head->content, delim);
		else
			temp = ft_strchrjoin(t, head->content, '\0');
		t = temp;
		head = head->next;
	}
	return (t);
}

char	*generate_listing_result(t_list	*head, char delim, \
t_owner_group_info	info, char	*path)
{
	struct stat	buff;
	char		*t;
	char		*temp;
	char		*temp2;

	t = ft_strdup("");
	while (head != NULL)
	{
		if (lstat(ft_strjoin(path, "/", head->content), &buff) != -1)
			temp2 = print_file_info(head->content, info, path);
		else
			temp2 = ft_strdup(head->content);
		if (ft_strlen(temp2))
		{
			if (head->next != NULL)
				temp = ft_strchrjoin(t, temp2, delim);
			else
				temp = ft_strchrjoin(t, temp2, '\0');
			free(temp2);
			t = temp;
		}
		head = head->next;
	}
	return (t);
}
