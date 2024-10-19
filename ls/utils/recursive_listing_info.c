/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_listing_info.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:58:24 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/19 20:09:47 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

/*
	list simple content like a file or simple 
	directory without subdirectories.
*/
char	*list_simple_data(t_list	*current, char	*t, char delim)
{
	char	*result;

	result = ft_calloc(ft_strlen(t), 1);
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
	char	*temp1;
	char	*temp2;
	char	*temp3;
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
				temp1 = ft_strjoin("\n./", current->content, ":\n");
				temp2 = generate_recursive_result(current->subdirectory, delim);
				result = ft_strchrjoin(result, \
				temp1, '\0');
				result = ft_strchrjoin(result, \
				temp2, '\0');
				free(temp1);
				free(temp2);
			}
			else
			{
				temp3 = ft_strjoin("\n./", \
				current->content, ":\n");
				result = ft_strchrjoin(result, temp3, '\0');
				free(temp3);
			}
		}
		current = current->next;
	}
	return (result);
}

char	*get_result(t_list	*current, char	*path, \
t_owner_group_info	info, char delim)
{
	char	*result;
	char	*file_info;
	char	*temp;
	char	*temp2;

	file_info = print_file_info(\
	current->content, info, path);
	temp = ft_strjoin("\n", file_info, "");
	result = ft_strjoin("", temp, ":\n");
	temp2 = get_recursive_listing_result(\
	current->subdirectory, delim, info, current->content);
	result = ft_strchrjoin(result, temp2, '\0');
	free(temp);
	free(temp2);
	free(file_info);
	return (result);
}

char	*get_content_data(t_list	*current, char	*path, \
t_owner_group_info	info, char delim)
{
	struct stat	buff;
	char		*result;
	char		*full_path;
	char		*file_info;

	result = ft_strdup("");
	while (current != NULL)
	{
		full_path = ft_strjoin(path, "/", current->content);
		lstat(full_path, &buff);
		file_info = print_file_info(current->content, \
		info, path);
		if (ft_strlen(file_info) && ft_strlen(file_info))
		{
			result = ft_strchrjoin(result, file_info, delim);
			free(full_path);
			free(file_info);
		}
		// else
		// 	result = ft_custom_strjoin(result, current->content, "");
		current = current->next;
	}
	return (result);
}

char	*get_recursive_listing_result(t_list	*head, char delim, \
t_owner_group_info	info, char	*path)
{
	struct stat	buff;
	char		*result;
	char		*full_path;
	char		*file_infos;
	char		*temp;
	t_list		*current;

	current = head;
	result = get_content_data(current, path, info, delim);
	current = head;
	full_path = ft_strjoin(path, "/", current->content);
	while (current != NULL)
	{
		if (is_directory(current->content))
		{
			lstat(full_path, &buff);
			if (current->subdirectory != NULL)
			{
				temp = get_result(current, path, \
	info, delim);
				result = ft_custom_strjoin(result, temp, "");
				free(temp);
			}
			else
			{
				file_infos = print_file_info(\
				current->content, info, path);
				temp = ft_strjoin("\n", file_infos, "");
				result = ft_custom_strjoin(result, temp, ":\n\n");
				free(file_infos);
				free(temp);
			}
		}
		current = current->next;
	}
	free(full_path);
	return (result);
}
