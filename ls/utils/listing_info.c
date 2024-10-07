/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:13:50 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/07 13:09:48 by ael-asri         ###   ########.fr       */
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
		free(t);
		t = temp;
		head = head->next;
	}
	return (t);
}

char	*generate_listing_result(t_list	*head, char delim, \
int	*owner_grp_info_, const char	*path)
{
	struct stat	buff;
	char		*t;
	char		*temp;

	t = ft_strdup("");
	while (head != NULL)
	{
		lstat(head->content, &buff);
		if (head->next != NULL)
			temp = ft_strchrjoin(t, print_file_info(head->content, \
			owner_grp_info_, path), delim);
		else
			temp = ft_strchrjoin(t, print_file_info(head->content, \
			owner_grp_info_, path), '\0');
		free(t);
		t = temp;
		head = head->next;
	}
	return (t);
}
