/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:33:40 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/20 12:08:54 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

char	*opts_parser(int ac, char **av, char **path) {
    
    (void)ac;
    int i=0;
    int count = 0;
    int j=0;
    int index = 0;
    
    while (av[i])
		count+=(ft_strlen(av[i++])-1);

	char *s = ft_calloc(count+1, 1);
	i = 1;
	while (av[i] != NULL) {
        if (av[i][0] == '-') {
            if (ft_strlen(av[i]) < 2) {
                perror("invalid format");
                exit(1);
            }

            j = 0;
            while (av[i][j] != '\0') {
                if (!ft_strchr(s, av[i][j]))
                    s[index++] = av[i][j];
                j++;
            }
            
        }
        else {
            *path = av[i];
        }
        i++;
    }

    if (!ft_strlen(*path))
        *path = ".";
    return s;
}