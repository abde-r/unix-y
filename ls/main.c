/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:32 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/21 17:31:54 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int	main(int ac, char	**av)
{
	t_list	*head;
	char	*options;
	char	**paths;
	char	*final_res;
	char	*temp_s;
	int		i;

	paths = ft_calloc(ac, PATH_SIZE);
	options = opts_parser(av, paths);
	i = 0;
	while (paths[i])
	{
		head = 0;
		final_res = ft_ls(&head, options, paths[i]);
		if (!char_finder(options) && !ft_strchr(options, 'd'))
			temp_s = manage_recursive_columns(final_res);
		else if (!ft_strchr(options, 'd'))
			temp_s = manage_recursive_colors(ft_split(final_res, '\n'), paths[i], 0);
		else
			temp_s = ft_strdup(final_res);
		ft_putchar(paths, temp_s, i);
		outer_free(head, temp_s);
		i++;
	}
	outer_free2(paths, &options, &final_res);
	return (0);
}
