/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl_xattr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:15:00 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/21 18:53:13 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

/*
	Return 1 if xattr exists, otherwise 0
*/
int	has_extended_attributes(char	*path)
{
	ssize_t	len;

	len = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (len > 0)
		return (len);
	return (0);
}

/*
	Get the size of the extended attributes and iterating 
	over the list to check for the ACL attribute
	it returns 1 if the file has ACL (system.posix_acl_access)
*/
int	has_acl(char	*path)
{
	acl_t	acl;

	acl = acl_get_file(path, ACL_TYPE_EXTENDED);
	if (!acl && errno == ENOENT)
		return (0);
	acl_free(acl);
	return (1);
}
