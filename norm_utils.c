/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:48:42 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/20 22:05:03 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

void	lstat_norm(char	*path, char	*content, struct stat *buff)
{
	char	*full_path;

	full_path = ft_strjoin(path, "/", content);
	lstat(full_path, buff);
	free(full_path);
}

int	lstat_condition_norm(char	*name, char	*path, struct stat *statbuf)
{
	char	*full_path;

	full_path = ft_strjoin(path, "/", name);
	if (lstat(full_path, statbuf) == -1)
	{
		free(full_path);
		return (1);
	}
	free(full_path);
	return (0);
}
