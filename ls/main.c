/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:32 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/25 14:44:26 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char	*ft_ls(t_list	**head, char	*opts, char	*path)
{
	DIR		*dp;
	char	*final_res;

	if (ft_strchr(opts, 'd'))
		final_res = ft_strjoin(ls_d(path), "\0", "");
	else
	{
		dp = get_current_dir(path);
		if (ft_strchr(opts, 'R'))
			ls_recursive(head, dp, path);
		else if (!ft_strchr(opts, 'R'))
			ls(head, path);
		final_res = opts_executer(head, opts, path);
	}
	return (final_res);
}

int	main(int ac, char	**av)
{
	t_list	*head;
	char	*opts;
	char	*path;
	char	*final_res;

	head = 0;
	path = ft_calloc(9999, 1);
	opts = opts_parser(ac, av, &path);
	final_res = ft_ls(&head, opts, path);
	if (ft_strchr(opts, 'R'))
	{
		if (!ft_strchr(opts, 'l'))
			printf("%s", manage_recursive_columns(final_res));
		else
			printf("%s", manage_recursive_colors(ft_split(final_res, '\n'), 0));
	}
	else
	{
		if (!ft_strchr(opts, 'l'))
			printf("%s", manage_columns(final_res));
		else
			printf("%s", manage_colors(head, final_res));
	}
	return (0);
}
