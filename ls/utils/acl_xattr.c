/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl_xattr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:15:00 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/25 19:29:58 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

/*
	Return 1 if xattr exists, otherwise 0
*/
int	has_extended_attributes(const char *path)
{
	ssize_t	len;

	len = listxattr(path, NULL, 0);
	if (len > 0)
		return (len);
	return (0);
}

int	listxattr_err(char	**list)
{
	perror("listxattr");
	free(*list);
	return (-1);
}

/*
	Get the size of the extended attributes and iterating 
	over the list to check for the ACL attribute
	it returns 1 if the file has ACL (system.posix_acl_access)
*/
int	has_acl(const char *path)
{
	ssize_t	len;
	char	*acl_attr_name;
	char	*list;
	char	*attr;

	acl_attr_name = ft_strdup("system.posix_acl_access");
	len = has_extended_attributes(path);
	list = ft_calloc(len, 1);
	if (len > 0)
	{
		if (listxattr(path, list, len) == -1)
			return (listxattr_err(&list));
		attr = list;
		while (attr < list + len)
		{
			if (ft_strcmp(attr, acl_attr_name) == 0)
			{
				free(list);
				return (1);
			}
			attr += strlen(attr) + 1;
		}
		free(list);
	}
	return (0);
}
