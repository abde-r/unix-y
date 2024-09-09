/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl_xattr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:15:00 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/09 12:18:29 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int has_extended_attributes(const char *path) {
    ssize_t len = listxattr(path, NULL, 0);  // Get the size of the xattr list
    return len > 0 ? 1 : 0;                  // Return 1 if xattr exists, otherwise 0
}

int has_acl(const char *path) {
    char acl_attr_name[] = "system.posix_acl_access";
    ssize_t len = listxattr(path, NULL, 0);  // Get the size of the extended attributes list

    if (len == -1) {
        perror("listxattr");
        return -1;  // Error occurred while fetching extended attributes
    }

    if (len > 0) {
        char *list = (char *)malloc(len);
        if (listxattr(path, list, len) == -1) {
            perror("listxattr");
            free(list);
            return -1;  // Error while fetching attribute names
        }

        // Iterate over the list of extended attributes and check for the ACL attribute
        char *attr = list;
        while (attr < list + len) {
            if (strcmp(attr, acl_attr_name) == 0) {
                free(list);
                return 1;  // File has ACL (system.posix_acl_access)
            }
            attr += strlen(attr) + 1;  // Move to the next attribute in the list
        }

        free(list);
    }

    return 0;  // File does not have an ACL
}
