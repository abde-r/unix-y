/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:34:46 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/13 10:43:21 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int	swap_nodes(t_list	*a, t_list	*b)
{
	char	*temp_content;
	t_list	*temp_subdir;

	temp_content = a->content;
	temp_subdir = a->subdirectory;
	a->content = b->content;
	a->subdirectory = b->subdirectory;
	b->content = temp_content;
	b->subdirectory = temp_subdir;
	return (1);
}

int	compare_case_sensitive(char	*a, char	*b)
{
	char	lower_a;
	char	lower_b;

	while (*a && *b)
	{
		lower_a = ft_tolower(*a);
		lower_b = ft_tolower(*b);
		if (lower_a != lower_b)
			return (lower_a - lower_b);
		a++;
		b++;
	}
	return (*a - *b);
}

void	sort_list(t_list	**head)
{
	t_list	*current;
	t_list	*next;
	char	*temp;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *head;
		while (current->next != NULL)
		{
			next = current->next;
			if (compare_case_sensitive(current->content, next->content) > 0)
			{
				temp = current->content;
				current->content = next->content;
				next->content = temp;
				swapped = 1;
			}
			current = current->next;
		}
	}
}

// void	sort_by_time(t_list	**output, char	*path)
// {
// 	int			swapped;
// 	t_list		*ptr1;
// 	t_list		*lptr;
// 	struct stat	buff1;
// 	struct stat	buff2;
// 	char		*full_path;
// 	char		*full_path2;

// 	lptr = NULL;
// 	swapped = 1;
// 	while (swapped)
// 	{
// 		swapped = 0;
// 		ptr1 = *output;
// 		while (ptr1->next != lptr)
// 		{
// 			full_path = ft_strjoin(path, "/", ptr1->content);
// 			lstat(full_path, &buff1);
// 			full_path2 = ft_strjoin(path, "/", ptr1->next->content);
// 			lstat(full_path2, &buff2);
// 			if (buff1.st_mtime < buff2.st_mtime)
// 			{
// 				swap_nodes(ptr1, ptr1->next);
// 				swapped = 1;
// 			}
// 			ptr1 = ptr1->next;
// 			free(full_path);
// 			free(full_path2);
// 		}
// 		lptr = ptr1;
// 	}
// }

// void	sort_by_access_time(t_list	**output, char	*path)
// {
// 	int			swapped;
// 	t_list		*ptr1;
// 	t_list		*lptr;
// 	struct stat	buff1;
// 	struct stat	buff2;

// 	lptr = NULL;
// 	swapped = 1;
// 	while (swapped)
// 	{
// 		swapped = 0;
// 		ptr1 = *output;
// 		while (ptr1->next != lptr)
// 		{
// 			lstat(ft_strjoin(path, "/", ptr1->content), &buff1);
// 			lstat(ft_strjoin(path, "/", ptr1->next->content), &buff2);
// 			if (buff1.st_atime < buff2.st_atime)
// 			{
// 				swap_nodes(ptr1, ptr1->next);
// 				swapped = 1;
// 			}
// 			ptr1 = ptr1->next;
// 		}
// 		lptr = ptr1;
// 	}
// }
