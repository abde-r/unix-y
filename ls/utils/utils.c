/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:55 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/16 19:52:48 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

size_t ft_strlen(const char *s) {
    size_t  i=0;

    while (s[i] != '\0')
        i++;
    return i;
}

size_t ft_arrlen(char **s) {
    size_t  i=0;

    while (s[i] != NULL)
        i++;
    return i;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t			i=0;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (str1[i] && str2[i])
	{
		if (str1[i] > str2[i])
			return (1);
		else if (str1[i] < str2[i])
			return (-1);
		i++;
	}
	return 0;
}

int	ft_strchr(const char *s, const char c)
{
	size_t	i=0;
	
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return 1;
		i++;
	}
	return 0;
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*p;

	p = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

int is_directory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}

static int	set_count(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] == c)
		i++;
	count++;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
		{
			count++;
		}
		i++;
	}
	return (count);
}

static char	**ft_del(char **t, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(t[i]);
		i++;
	}
	free(t);
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t	len)
{
	char			*tab;
	unsigned int	i;
	unsigned int	j;

	tab = NULL;
	if (s == 0)
		return (0);
	if (len >= ft_strlen(s))
		tab = malloc(sizeof(char) * (ft_strlen(s) + 1));
	else if (len < ft_strlen(s))
		tab = malloc(sizeof(char) * (len + 1));
	if (tab == NULL)
		return (0);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
			tab[j++] = s[i];
		i++;
	}
	tab[j] = '\0';
	return (tab);
}

static char	**chek_and_fill(char **t, const char *s, char c)
{
	int	i;
	int	count;
	int	temp;

	i = 0;
	count = 0;
	while (s[i])
	{
		temp = i;
		if (s[i] == c)
		{
			i++;
			continue ;
		}
		while (s[i] != c && s[i])
			i++;
		t[count] = ft_substr(s, temp, i - temp);
		if (t[count] == NULL)
			return (ft_del(t, count));
		count++;
	}
	t[count] = 0;
	return (t);
}

char	**ft_split(const char *s, char c)
{
	char	**t;
	int		count;

	if (s == 0)
		return (0);
	count = set_count(s, c);
	t = (char **)malloc(sizeof(char *) * (count + 1));
	if (t == NULL)
		return (0);
	return (chek_and_fill(t, s, c));
}

char	*ft_strjoin(char *s1, char *s2, char *s3)
{
	int		i;
	int		j;
	char	*tab;

	// if (s1 == 0 || s2 == 0)
	// 	return (0);
	tab = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1));
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
	{
		tab[i] = s3[j];
		i++;
		j++;
	}
	tab[i] = '\0';
	return (tab);
}

char	*ft_strchrjoin(char *s1, char *s2, char delim)
{
	int		i;
	int		j;
	char	*tab;

	// if (s1 == 0 || s2 == 0)
	// 	return (0);
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

int	ft_strcat(char *dst, const char *src)
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

static void	ft_rev(char	*s)
{
	int		i;
	int		len;
	char	temp;

	i = 0;
	len = ft_strlen(s) - 1;
	while (s[i] && len > i)
	{
		temp = s[i];
		s[i] = s[len];
		s[len] = temp;
		i++;
		len--;
	}
}

static char	*ft_convert(char *s, int n, int count)
{
	int		i;
	int		nb;

	i = 0;
	nb = n;
	if (nb < 0)
		nb *= -1;
	while (i < count && nb > 0)
	{
		s[i] = nb % 10 + '0';
		nb /= 10;
		i++;
	}
	if (n < 0)
	{
		s[i] = '-';
		i++;
	}
	s[i] = '\0';
	ft_rev(s);
	return (s);
}

static char	*fill_tab(char *s)
{
	char	*nb;
	int		i;

	i = 0;
	nb = "-2147483648";
	while (i < 12)
	{
		s[i] = nb[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

static char	*allocate(long n)
{
	char	*s;
	int		i;

	s = NULL;
	i = 0;
	if (n == 0)
	{
		s = malloc(sizeof(char) * 2);
		s[0] = '0';
		s[1] = '\0';
	}
	else if (n == -2147483648)
	{
		s = malloc(sizeof(char) * 12);
		if (s == NULL)
			return (0);
		s = fill_tab(s);
	}
	return (s);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*s;
	int		nb;

	count = 0;
	nb = n;
	if (n == 0 || n == -2147483648)
	{
		return (allocate(n));
	}
	if (n < 0)
	{
		count = 1;
		nb *= -1;
	}
	while (nb > 0)
	{
		nb /= 10;
		count++;
	}
	s = malloc(sizeof(char) * (count + 1));
	if (s == NULL)
		return (0);
	return (ft_convert(s, n, count));
}
