/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:33:40 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/21 18:53:57 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

void	print_error(char	*s)
{
	perror(s);
	exit(0);
}

void	syntax_checker(char c)
{
	if (c != 'l' && c != 'R' && c != 'a' && c != 'r' && c != 't'\
	&& c != 'u' && c != 'f' && c != 'g' && c != 'd' && c != 'o')
		print_error("invalid option format");
}

void	len_checker(char	*s)
{
	if (ft_strlen(s) < 2)
		print_error("invalid option");
}

char	*parser(char	**av, char	*s, char	**path)
{
	int		i;
	int		j;
	int		index;

	i = 1;
	index = 0;
	while (av[i] != NULL)
	{
		if (av[i][0] == '-')
		{
			len_checker(av[i]);
			j = 1;
			while (av[i][j] != '\0')
			{
				syntax_checker(av[i][j]);
				if (!ft_strchr(s, av[i][j]))
					ft_strcat(s, &av[i][j]);
				j++;
			}
		}
		else
			path[index++] = ft_strdup(av[i]);
		i++;
	}
	return (s);
}

char	*opts_parser(char	**av, char	**paths)
{
	char	*s;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (av[i])
		count += (ft_strlen(av[i++]) - 1);
	s = ft_calloc(count + 1, 1);
	s = parser(av, s, paths);
	if (!ft_arrlen(paths))
		paths[0] = ft_strdup(".");
	return (s);
}
