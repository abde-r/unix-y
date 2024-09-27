/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_listing_info.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:58:24 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/26 12:53:01 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

/*
	list simple content like a file or simple 
	directory without subdirectories.
*/
char	*list_simple_data(t_list	*current, const char	*t, char delim)
{
	char	*result;

	result = ft_strdup("");
	while (current != NULL)
	{
		if (current->subdirectory == NULL || ft_strcmp(t, current->content))
			result = ft_strchrjoin(result, current->content, delim);
		current = current->next;
	}
	return (result);
}

char	*generate_recursive_result(t_list	*head, char delim)
{
	char	*result;
	t_list	*current;

	current = head;
	result = list_simple_data(current, current->content, delim);
	current = head;
	while (current != NULL)
	{
		if (is_directory(current->content))
		{
			if (current->subdirectory != NULL)
			{
				result = ft_strchrjoin(result, \
				ft_strjoin("\n./", current->content, ":\n"), '\0');
				result = ft_strchrjoin(result, \
				generate_recursive_result(current->subdirectory, delim), '\0');
			}
			else
				result = ft_strchrjoin(result, ft_strjoin("\n./", \
				current->content, ":\n"), '\0');
		}
		current = current->next;
	}
	return (result);
}

char	*get_result(t_list	*current, const char	*path, \
int	*owner_grp_info_, char delim)
{
	char	*result;

	result = ft_strjoin("", ft_strjoin("\n", print_file_info(\
	current->content, owner_grp_info_, path), ""), ":\n");
	result = ft_strchrjoin(result, get_recursive_listing_result(\
	current->subdirectory, delim, owner_grp_info_, current->content), '\0');
	return (result);
}

char	*get_content_data(t_list	*current, const char	*path, \
int	*owner_grp_info_, char delim)
{
	struct stat	buff;
	char		*result;

	result = ft_strdup("");
	while (current != NULL)
	{
		lstat(ft_strjoin(path, "/", current->content), &buff);
		result = ft_strchrjoin(result, print_file_info(current->content, \
		owner_grp_info_, path), delim);
		current = current->next;
	}
	return (result);
}

char	*get_recursive_listing_result(t_list	*head, char delim, \
int	*owner_grp_info_, const char	*path)
{
	struct stat	buff;
	char		*result;
	t_list		*current;

	current = head;
	result = get_content_data(current, path, owner_grp_info_, delim);
	current = head;
	while (current != NULL)
	{
		if (is_directory(current->content))
		{
			lstat(ft_strjoin(path, "/", current->content), &buff);
			if (current->subdirectory != NULL)
				result = ft_strjoin(result, get_result(current, path, \
owner_grp_info_, delim), "");
			else
			{
				result = ft_strjoin(result, ft_strjoin("\n", print_file_info(\
				current->content, owner_grp_info_, path), ""), ":\n");
				result = ft_strchrjoin(result, "\n", '\0');
			}
		}
		current = current->next;
	}
	return (result);
}
