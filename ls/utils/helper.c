/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:38:25 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/29 20:47:56 by ael-asri         ###   ########.fr       */
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
char	*recursive_executer(t_list	**head, const char	*opts, \
const char	*path)
{
	int		*ownrgrp_info;

	ownrgrp_info = ft_calloc(2, 0);
	if (!ft_strchr(opts, 'a') && !ft_strchr(opts, 'f'))
		remove_recursive_hiddens(head);
	if (!ft_strchr(opts, 'f'))
		sort_recursive_list(head, 0);
	if (ft_strchr(opts, 't'))
		sort_recursive_by_time(head, path, 0);
	if (ft_strchr(opts, 'r'))
		sort_recursive_list(head, 1);
	if (ft_strchr(opts, 'u'))
		sort_recursive_by_time(head, path, 1);
	if (ft_strchr(opts, 'l') || ft_strchr(opts, 'g') || ft_strchr(opts, 'o'))
	{
		ownrgrp_info[0] = ft_strchr(opts, 'g');
		ownrgrp_info[1] = ft_strchr(opts, 'o');
		return (get_recursive_listing_result(*head, '\n', ownrgrp_info, path));
	}
	else if (!ft_strchr(opts, 'l') && !ft_strchr(opts, 'g') && \
	!ft_strchr(opts, 'o'))
		return (generate_recursive_result(*head, ' '));
	return ("");
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
char	*executer(t_list	**head, const char	*opts, const char	*path)
{
	int		*owner_grp_info_;

	owner_grp_info_ = ft_calloc(2, 0);
	if (!ft_strchr(opts, 'a') && !ft_strchr(opts, 'f'))
		remove_hiddens(head);
	if (!ft_strchr(opts, 'f'))
		sort_list(head);
	if (ft_strchr(opts, 't'))
		sort_by_time(head, path);
	if (ft_strchr(opts, 'r'))
		reverse_order(head);
	if (ft_strchr(opts, 'u'))
		sort_by_access_time(head, path);
	if (ft_strchr(opts, 'l') || ft_strchr(opts, 'g') || ft_strchr(opts, 'o'))
	{
		owner_grp_info_[0] = ft_strchr(opts, 'g');
		owner_grp_info_[1] = ft_strchr(opts, 'o');
		return (generate_listing_result(*head, '\n', owner_grp_info_, path));
	}
	else if (!ft_strchr(opts, 'l') && !ft_strchr(opts, 'g') && \
	!ft_strchr(opts, 'o'))
		return (generate_result(*head, ' '));
	return ("");
}

char	*opts_executer(t_list	**head, const char	*opts, const char	*path)
{
	// char	*t;

	// t = ft_strdup("");
	if (ft_strchr(opts, 'R'))
		return(recursive_executer(head, opts, path));
	else if (!ft_strchr(opts, 'R'))
		return(executer(head, opts, path));
	return ("");
}
