/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:38:08 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/19 22:20:05 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

t_list	*merge_sorted(t_list	*left, t_list	*right, \
char	*path, int (*compare)(struct stat, struct stat))
{
	struct stat	stat_left;
	struct stat	stat_right;
	char		*full_path_left;
	char		*full_path_right;

	if (!left)
		return (right);
	if (!right)
		return (left);
	full_path_left = ft_strjoin(path, "/", left->content);
	full_path_right = ft_strjoin(path, "/", right->content);
	lstat(full_path_left, &stat_left);
	lstat(full_path_right, &stat_right);
	free(full_path_left);
	free(full_path_right);
	if (compare(stat_left, stat_right) <= 0)
	{
		left->next = merge_sorted(left->next, right, path, compare);
		return (left);
	}
	else
	{
		right->next = merge_sorted(left, right->next, path, compare);
		return (right);
	}
}

/*
	Split the list into two halves
	and recursively sort both halves
	then merge the sorted halves
*/
t_list	*merge_sort(t_list	*head, char	*path, \
int (*compare)(struct stat, struct stat))
{
	t_list	*left;
	t_list	*right;
	t_list	*slow;
	t_list	*fast;
	t_list	*mid;

	if (!head || !head->next)
		return (head);
	slow = head;
	fast = head->next;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	mid = slow->next;
	slow->next = NULL;
	left = merge_sort(head, path, compare);
	right = merge_sort(mid, path, compare);
	return (merge_sorted(left, right, path, compare));
}

int	compare_mtime(struct stat a, struct stat b)
{
	if (a.st_mtime < b.st_mtime)
		return (1);
	else
	{
		if (a.st_mtime > b.st_mtime)
			return (-1);
		return (0);
	}
}

int	compare_atime(struct stat a, struct stat b)
{
	if (a.st_atime < b.st_atime)
		return (1);
	else
	{
		if (a.st_atime > b.st_atime)
			return (-1);
		return (0);
	}
}

/*
	Select comparison function and 
	perform merge sort on the current directory
	then recursively sort subdirectories
*/
void	sort_time(t_list	**head, char	*path, int __flag_)
{
	t_list	*current;
	char	*full_path;
	int		(*compare)(struct stat, struct stat);

	if (!*head)
		return ;
	if (__flag_ == 1)
		compare = compare_atime;
	else
		compare = compare_mtime;
	*head = merge_sort(*head, path, compare);
	current = *head;
	while (current != NULL)
	{
		if (is_directory(current->content) && ft_strcmp(current->content, "."))
		{
			full_path = ft_strjoin(path, "/", current->content);
			sort_time(&(current->subdirectory), full_path, __flag_);
			free(full_path);
		}
		current = current->next;
	}
}
