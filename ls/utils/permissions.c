/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:52:38 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/13 15:43:02 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

char	*get_user_permissions(mode_t mode)
{
	char	*s;

	s = ft_strdup("----");
	if (S_ISDIR(mode))
		s[0] = 'd';
	if (mode & S_IRUSR)
		s[1] = 'r';
	if (mode & S_IWUSR)
		s[2] = 'w';
	if (mode & S_IXUSR)
		s[3] = 'x';
	return (s);
}

char	*get_group_permissions(mode_t mode)
{
	char	*s;

	s = ft_strdup("---");
	if (mode & S_IRGRP)
		s[0] = 'r';
	if (mode & S_IWGRP)
		s[1] = 'w';
	if (mode & S_IXGRP)
		s[2] = 'x';
	return (s);
}

char	*get_others_permissions(mode_t mode, char	*path)
{
	char	*s;

	s = ft_strdup("--- ");
	if (mode & S_IROTH)
		s[0] = 'r';
	if (mode & S_IWOTH)
		s[1] = 'w';
	if (mode & S_IXOTH)
		s[2] = 'x';
	if (has_acl(path))
		s[3] = 'x';
	else if (has_extended_attributes(path))
		s[3] = '@';
	return (s);
}

char	*print_permissions(mode_t mode, char	*path)
{
	char	*s;
	char	*user;
	char	*group;
	char	*other;

	user = get_user_permissions(mode);
	group = get_group_permissions(mode);
	other = get_others_permissions(mode, path);
	s = ft_strjoin(user, group, other);
	free(user);
	free(group);
	free(other);
	return (s);
}
