/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:32 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/18 23:32:47 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int	main(int ac, char	**av)
{
	t_list	*head;
	char	*opts;
	char	*path;
	char	*final_res;
	char	*temp_s;

	head = 0;
	path = ft_strdup(".");
	opts = opts_parser(ac, av, &path);
	final_res = ft_ls(&head, opts, path);
	temp_s = ft_strdup(final_res);
	if (!char_finder(opts) && !ft_strchr(opts, 'd'))
		temp_s = manage_recursive_columns(final_res);
	else if (!ft_strchr(opts, 'd'))
		temp_s = manage_recursive_colors(ft_split(final_res, '\n'), 0);
	// printf("final res -%s- -%s-\n", final_res, temp_s);
	ft_putchar(temp_s);
	free(temp_s);
	outer_free(head, &opts, &path, &final_res);
	return (0);
}
