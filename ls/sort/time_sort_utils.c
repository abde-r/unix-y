/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_sort_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:30:06 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/26 17:44:58 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int	_compare_mtime(char	*path, char	*content1, char	*content2)
{
	char		*temp;
	char		*temp2;
	struct stat	buff1;
	struct stat	buff2;

	temp = ft_strjoin(path, "/", content1);
	lstat(temp, &buff1);
	temp2 = ft_strjoin(path, "/", content2);
	lstat(temp2, &buff2);
	free(temp);
	free(temp2);
	if (buff1.st_mtime < buff2.st_mtime)
		return (1);
	return (0);
}

void	sort_by_time(t_list	**output, char	*path)
{
	int			swapped;
	t_list		*ptr1;
	t_list		*lptr;

	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = *output;
		while (ptr1->next != lptr)
		{
			if (_compare_mtime(path, ptr1->content, ptr1->next->content))
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

int	_compare_atime(char	*path, char	*content1, char	*content2, \
struct stat *buff1)
{
	char		*temp;
	char		*temp2;
	time_t		sec1;
	time_t		sec2;
	struct stat	buff2;

	temp = ft_strjoin(path, "/", content1);
	lstat(temp, buff1);
	temp2 = ft_strjoin(path, "/", content2);
	lstat(temp2, &buff2);
	sec1 = buff1->st_atimespec.tv_sec;
	sec2 = buff2.st_atimespec.tv_sec;
	free(temp);
	free(temp2);
	if (localtime(&sec1) < localtime(&sec2))
		return (1);
	return (0);
}

void	sort_by_access_time(t_list	**output, char	*path)
{
	int			swapped;
	t_list		*ptr1;
	t_list		*lptr;
	struct stat	buff1;

	lptr = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = *output;
		while (ptr1->next != lptr)
		{
			if (_compare_atime(path, ptr1->content, \
			ptr1->next->content, &buff1))
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}
