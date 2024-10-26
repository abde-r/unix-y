/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:38:25 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/26 18:45:51 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

void	remove_hiddens(t_list	**head)
{
	t_list	*current;
	t_list	*prev;
	t_list	*to_free;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (current->content[0] == '.')
		{
			to_free = current;
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			current = current->next;
			free(to_free->content);
			free(to_free);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void	remove_recursive_hiddens(t_list	**head)
{
	t_list	*current;
	t_list	*prev;

	current = *head;
	prev = NULL;
	while (current != NULL)
	{
		if (current->subdirectory != NULL)
			remove_recursive_hiddens(&(current->subdirectory));
		current = current->next;
	}
	remove_hiddens(head);
}

char	*listing_executer(t_list	**head, char	*opts, char	*path)
{
	t_owner_group_info	info;

	info.owner_info = ft_strchr(opts, 'g');
	info.group_info = ft_strchr(opts, 'o');
	if (ft_strchr(opts, 'R'))
		return (get_recursive_listing_result(*head, '\n', info, path));
	else
		return (generate_listing_result(*head, '\n', info, path));
}

/*
	-a & -f doesn't exist: remove hidden files and dirs.
	-f: No sorting and includes hidden files.
	-t: sort by time.
	-r: reverse the order.
	-u: Sort by last access time.
	-g: Hide the owner of the file.
	-o: Hide the group name.
	-l, -g & -o doesn't exist: generate a string joined by space
*/
char	*executer(t_list	**head, char	*opts, char	*path)
{
	if (!ft_strchr(opts, 'a') && !ft_strchr(opts, 'f'))
		remove_recursive_hiddens(head);
	if (!ft_strchr(opts, 'f'))
		sort(head, 0);
	if (ft_strchr(opts, 't'))
		sort_time(head, path, 0);
	if (ft_strchr(opts, 'r'))
		sort(head, 1);
	if (ft_strchr(opts, 'u'))
		sort_by_access_time(head, path);
	if (ft_strchr(opts, 'l') || ft_strchr(opts, 'g') || ft_strchr(opts, 'o'))
		return (listing_executer(head, opts, path));
	else if (!ft_strchr(opts, 'l') && !ft_strchr(opts, 'g') && \
	!ft_strchr(opts, 'o'))
	{
		if (ft_strchr(opts, 'R'))
			return (generate_recursive_result(*head, ' '));
		else
			return (generate_result(*head, ' '));
	}
	return ("");
}
