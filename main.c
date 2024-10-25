/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:32 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/25 21:10:08 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int	main(int ac, char	**av)
{
	t_list	*head;
	t_list	*list;
	char	*options;
	char	**paths;

	head = 0;
	paths = ft_calloc(ac, PATH_SIZE);
	options = opts_parser(av, paths);
	list = get_final_list(head, paths, options);
	print_final_list(list, options);
	outer_free2(paths);
	free(options);
	return (0);
}
