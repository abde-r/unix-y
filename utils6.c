/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:16:56 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/24 09:32:38 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}

int	ft_strcat(char *dst, char *src)
{
	unsigned int	src_len;
	unsigned int	dest_len;
	unsigned int	i;

	dest_len = 0;
	src_len = 0;
	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	while (src[i])
	{
		dst[dest_len + i] = src[i];
		i++;
	}
	dst[dest_len + i] = '\0';
	return (src_len + dest_len);
}

int	is_content_valid(char	*s)
{
	char	*t;
	int		i;

	i = 0;
	t = ft_strdup("Error	ft_ls:");
	while (s[i] && t[i])
	{
		if (s[i] != t[i])
		{
			free(t);
			return (0);
		}
		i++;
	}
	return (1);
}

void	swap_list_nodes(t_list	*current, t_list	*next, int	*swapped)
{
	char	*temp_content;
	t_list	*temp_subdirectory;

	temp_content = current->content;
	current->content = next->content;
	next->content = temp_content;
	temp_subdirectory = current->subdirectory;
	current->subdirectory = next->subdirectory;
	next->subdirectory = temp_subdirectory;
	*swapped = 1;
}

void	handle_failure(t_list	**head, char	*path, \
DIR	*dp, struct stat statbuf)
{
	if (S_ISREG(statbuf.st_mode))
		insert_node(head, path);
	else if (!dp)
		unauth_message(head, path);
}
