/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 22:16:56 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/21 18:28:02 by ael-asri         ###   ########.fr       */
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
