/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:32 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/20 12:07:55 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int	main(int ac, char	**av)
{
	t_list	*head;
	char	*opts;
	char	*path;
	char	*final_res;

	head = 0;
	path = ft_calloc(999, 1);
	final_res = ft_calloc(9999, 1);
	opts = opts_parser(ac, av, &path);
	if (ft_strchr(opts, 'd'))
		final_res = ft_strjoin(ls_d(path), "\0", "");
	else
	{
		if (ft_strchr(opts, 'R'))
			ls_R(&head, path);
		else if (!ft_strchr(opts, 'R'))
			ls(&head, path);
		final_res = opts_executer(&head, opts, path);
	}
	if (ft_strchr(opts, 'R'))
	{
		if (!ft_strchr(opts, 'l'))
			printf("%s", manage_recursive_columns(final_res));
		else
			printf("%s", manage_recursive_colors(final_res));
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
