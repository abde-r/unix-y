/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:33:40 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/01 12:16:34 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

char	*opts_parser(char **av) {
    
    
    int i=0;
    int count = 0;
    int j=0;
    int index = 0;
    
    while (av[i])
		count+=(ft_strlen(av[i++])-1);

	char *s = ft_calloc(count+1, 1);
	i = 1;
	while (av[i] != NULL) {
        j = 0;
		if (ft_strlen(av[i]) < 2) {
            perror("invalid format");
			exit(1);
		}

        while (av[i][j] != '\0') {
            if (!ft_strchr(s, av[i][j]))
                s[index++] = av[i][j];
            j++;
        }
        i++;
    }

    return s;
}