/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listing_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:13:50 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/21 18:28:48 by ael-asri         ###   ########.fr       */
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

char	*file_info_norm(t_list	*head, char	*path, \
t_owner_group_info info)
{
	char	*full_path;
	char	*s;

	full_path = ft_strjoin(path, "/", head->content);
	if (!is_content_valid(head->content))
		s = print_file_info(head->content, info, path);
	else
		s = ft_strdup(head->content);
	free(full_path);
	return (s);
}

char	*generate_listing_result(t_list	*head, char delim, \
t_owner_group_info	info, char	*path)
{
	char		*t;
	char		*temp;
	char		*temp2;

	t = ft_strdup("");
	while (head != NULL)
	{
		temp2 = file_info_norm(head, path, info);
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
