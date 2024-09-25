/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:55 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/24 11:08:30 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

static int	set_count(char const	*s, char c)
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
