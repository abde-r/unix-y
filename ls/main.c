/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:32 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/15 22:55:19 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int	char_finder(char	*s)
{
	return (ft_strchr(s, 'l') || \
	ft_strchr(s, 'g') || ft_strchr(s, 'o'));
}

void	free_subdirectory(t_list *subdir)
{
	t_list	*temp;

	while (subdir != NULL)
	{
		temp = subdir;
		subdir = subdir->next;
		free(temp->content);
		if (temp->subdirectory != NULL)
			free_subdirectory(temp->subdirectory);
		free(temp);
	}
}

void	outer_free(t_list	*head, char	**opts, \
char	**final_res)
{
	t_list	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->content);
		if (temp->subdirectory)
			free_subdirectory(temp->subdirectory);
		free(temp);
	}
	free(head);
	free(*opts);
	free(*final_res);
}

int	main(int ac, char	**av)
{
	t_list	*head;
	char	*opts;
	char	*path;
	char	*final_res;
	char	*temp_s;

	head = 0;
	path = ".";
	opts = opts_parser(ac, av, &path);
	final_res = ft_ls(&head, opts, path);
	if (!char_finder(opts))
		temp_s = manage_recursive_columns(final_res);
	else
		temp_s = manage_recursive_colors(ft_split(final_res, '\n'), 0);
	ft_putchar(temp_s);
	free(temp_s);
	outer_free(head, &opts, &final_res);
	return (0);
}
