/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:37:09 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/25 22:04:07 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

size_t	ft_strlen(char	*s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	ft_putchar(char	**paths, char	*s, size_t index)
{
	size_t	i;

	i = 0;
	if (is_directory(paths[index]) && ft_arrlen(paths) > 1)
	{
		while (paths[index][i])
			write(2, &paths[index][i++], 1);
		write(2, &":\n", 2);
		i = 0;
	}
	while (s[i])
		write(2, &s[i++], 1);
	if (index < ft_arrlen(paths) - 1)
		write(2, &"\n", 1);
}

int	char_finder(char	*s)
{
	return (ft_strchr(s, 'l') || \
	ft_strchr(s, 'g') || ft_strchr(s, 'o'));
}

void	unauth_message(t_list	**head, char	*path)
{
	char	*err_message;

	err_message = ft_strjoin("Error	ft_ls:'", path, "'\
	cant-operate!");
	insert_node(head, err_message);
	free(err_message);
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
