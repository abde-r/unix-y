/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl_xattr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:15:00 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/20 12:24:37 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

// Get the size of the xattr list
/* Return 1 if xattr exists, otherwise 0 */
int	has_extended_attributes(const char *path)
{
	ssize_t	len;

	len = listxattr(path, NULL, 0);
	if (len > 0)
		return (1);
	return (0);
}

int	has_acl(const char *path)
{
	ssize_t	len;
	char	*acl_attr_name;
	char	*list;
	char	*attr;

	acl_attr_name = ft_strdup("system.posix_acl_access");
	/* Get the size of the extended attributes list */
	len = listxattr(path, NULL, 0);
	list = ft_calloc(len, 1);
	if (len == -1)
	{
		perror("listxattr");
		return (-1);
	}
	if (len > 0)
	{
		if (listxattr(path, list, len) == -1)
		{
			perror("listxattr");
			free(list);
			return (-1);
		}
		/* Iterate over the list of extended attributes
		and check for the ACL attribute */
		attr = list;
		while (attr < list + len)
		{
			if (strcmp(attr, acl_attr_name) == 0)
			{
				free(list);
				return (1);/* File has ACL (system.posix_acl_access) */
			}
			/* Move to the next attribute in the list */
			attr += strlen(attr) + 1;
		}
		free(list);
	}
	/* File does not have an ACL */
	return (0);
}
