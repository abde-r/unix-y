/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:36:20 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/26 19:01:37 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

void	sort_final_list(t_list **head)
{
	t_list	*current;
	t_list	*next;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *head;
		while (current != NULL && current->next != NULL)
		{
			next = current->next;
			if (is_directory(current->content) \
			&& custom_compare(current->content, next->content) > 0)
				swap_list_nodes(current, next, &swapped);
			current = current->next;
		}
	}
}

char	*get_files_result(t_list	**head, char	*delim)
{
	t_list	*current;
	char	*t;

	current = *head;
	t = ft_strdup("");
	while (current != NULL)
	{
		if (!is_directory(current->content))
		{
			if (current->next)
				t = ft_custom_strjoin(t, current->subdirectory->content, delim);
			else
				t = ft_custom_strjoin(t, current->subdirectory->content, "");
			free(current->content);
			current->content = NULL;
			free(current->subdirectory->content);
			free(current->subdirectory);
			current->subdirectory = NULL;
		}
		current = current->next;
	}
	return (t);
}

void	_some_magic(t_list	**head, char	*options)
{
	char	*t;
	char	*delim;
	t_list	*front_node;

	delim = " ";
	sort_final_list(head);
	if (ft_strchr(options, 'l'))
		delim = "\n";
	t = get_files_result(head, delim);
	if (ft_strlen(t))
	{
		front_node = create_node(t);
		lstadd_front(head, front_node);
	}
	free(t);
	delete_null_nodes(head);
}

void	print_final_list(t_list	*head, char	*options)
{
	char	*t;

	t = ft_strdup("");
	_some_magic(&head, options);
	while (head)
	{
		if (head->content)
		{
			if (!is_directory(head->content))
				t = ft_custom_strjoin(t, head->content, "\n");
			else
			{
				t = ft_custom_strjoin(t, head->content, ":\n");
				if (head->subdirectory)
					t = ft_custom_strjoin(t, head->subdirectory->content, "\n");
			}
			if (head->next)
				t = ft_custom_strjoin(t, "\n", "");
			freee(&head);
		}
		else
			head = head->next;
	}
	ft_putchr(t);
	ft_free2(&head, &t);
}

t_list	*get_final_list(t_list	*head, char	**paths, char	*options)
{
	t_list	*list;
	char	*final_res;
	char	*temp_s;
	int		i;

	i = 0;
	list = 0;
	while (paths[i])
	{
		head = 0;
		final_res = ft_ls(&head, options, paths[i]);
		if (!char_finder(options) && !ft_strchr(options, 'd'))
			temp_s = manage_recursive_columns(final_res);
		else if (!ft_strchr(options, 'd'))
			temp_s = manage_recursive_colors(\
ft_split(final_res, '\n'), paths[i], 0);
		else
			temp_s = ft_strdup(final_res);
		insert_nnode(&list, paths[i], temp_s);
		outer_free(head, temp_s);
		i++;
		free(final_res);
	}
	return (list);
}
