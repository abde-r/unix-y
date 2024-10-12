/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:28:59 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/12 12:42:09 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

char	*ft_custom_strjoin(char *s1, char *s2, char *s3)
{
	int		i;
	int		j;
	char	*tab;

	tab = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1), 1);
	if (!tab)
		return (0);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		tab[i] = s2[j];
		i++;
		j++;
	}
	j = 0;
	while (s3[j])
		tab[i++] = s3[j++];
	tab[i] = '\0';
	free(s1);
	return (tab);
}

char	*ft_strjoin(char *s1, char *s2, char *s3)
{
	int		i;
	int		j;
	char	*tab;

	tab = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1), 1);
	if (!tab)
		return (0);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		tab[i] = s2[j];
		i++;
		j++;
	}
	j = 0;
	while (s3[j])
		tab[i++] = s3[j++];
	tab[i] = '\0';
	return (tab);
}

char	*ft_str2join(char *s1)
{
	int		i;
	char	*tab;

	tab = ft_calloc((ft_strlen(s1) + 2), 1);
	if (!tab)
		return (0);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	tab[i] = ' ';
	i++;
	tab[i] = '\0';
	return (tab);
}

char	*ft_strchrjoin(char *s1, char *s2, char delim)
{
	int		i;
	int		j;
	char	*tab;

	tab = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!tab)
		return (0);
	i = 0;
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		tab[i] = s2[j];
		i++;
		j++;
	}
	tab[i] = delim;
	i++;
	tab[i] = '\0';
	free(s1);
	return (tab);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned int	i;
	char			*t;

	i = 0;
	t = malloc(count * size);
	if (t == NULL)
		return (0);
	while (i < (size * count))
	{
		t[i] = '\0';
		i++;
	}
	return (t);
}

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

size_t	ft_strncpy(char *dst, char *src, size_t	dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
