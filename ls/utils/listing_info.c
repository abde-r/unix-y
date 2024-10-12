/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:13:50 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/12 12:07:13 by ael-asri         ###   ########.fr       */
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
		// free(t);
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

	t = ft_strdup("");
	while (head != NULL)
	{
		lstat(head->content, &buff);
		char *gg = print_file_info(head->content, \
			info, path);
		if (head->next != NULL)
			temp = ft_strchrjoin(t, gg, delim);
		else
			temp = ft_strchrjoin(t, gg, '\0');
		// free(t);
		free(gg);
		t = temp;
		head = head->next;
	}
	// free(temp);
	return (t);
}
