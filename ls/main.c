/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:32 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/07 14:15:51 by ael-asri         ###   ########.fr       */
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
		closedir(dp);
	}
	return (final_res);
}

int	char_finder(char	*s)
{
	return (ft_strchr(s, 'l') || \
	ft_strchr(s, 'g') || ft_strchr(s, 'o'));
}

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
	if (ft_strchr(opts, 'R'))
	{
		if (!char_finder(opts))
			temp_s = manage_recursive_columns(final_res);
			// printf("%s", );
		else
			temp_s = manage_recursive_colors(ft_split(final_res, '\n'), 0);
			// printf("%s", );
	}
	else
	{
		if (!char_finder(opts))
			temp_s = manage_columns(final_res);
			// printf("%s", );
		else
			temp_s = manage_colors(head, final_res);
	}
	printf("%s", temp_s);
	free(temp_s);

	t_list *temp;
    
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp->content);
        free(temp);
    }
	free(head);
	free(opts);
	free(path);
	free(final_res);
	return (0);
}
