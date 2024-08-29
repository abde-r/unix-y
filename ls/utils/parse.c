/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:33:40 by ael-asri          #+#    #+#             */
/*   Updated: 2024/08/29 16:34:19 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

char	*opts_parser(char **av) {
    char *s = malloc(999);
    int i=1;
    int j=0;
    int index = 0;
    
    while (av[i] != NULL) {
        j = 0;
        while (av[i][j] != '\0')
        {
            if (!ft_strchr(s, av[i][j]))
                s[index++] = av[i][j];
            j++;
        }
        i++;
    }

    return s;
}