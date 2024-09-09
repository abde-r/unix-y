/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:32 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/09 13:28:17 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int main(int ac, char **av) {

    t_list	*head = 0;
    char	*opts;
    char	*path = ft_calloc(999, 1);
	char *final_res = ft_calloc(999, 1);
    (void)ac;
	
    // parse & error checking
    opts = opts_parser(av, &path);

	if (ft_strchr(opts, 'd')) // Print directories themselves, not their contents
        final_res = ft_strjoin(ls_d(path), "\0", "");
    else {
		if (ft_strchr(opts, 'R')) // if -R exists, execute ls with -R flag
			ls_R(&head, path);
		else if (!ft_strchr(opts, 'R')) { // else if -R doesn't exist, execute default ls
			ls(&head, path);
		}

		final_res = opts_executer(&head, opts, path);
	}

	// printf("-%s-\n", final_res);
	if (!ft_strchr(opts, 'l'))
		printf("%s", manage_columns(final_res));
	else
		printf("%s", manage_colors(head, final_res));

	return (0);
}
