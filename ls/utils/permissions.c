/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:52:38 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/21 18:00:03 by ael-asri         ###   ########.fr       */
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
	if (mode & S_ISUID)
		s[3] = 'S';
	else if (mode & S_IXUSR)
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
	if (mode & S_ISGID)
		s[2] = 'S';
	else if (mode & S_IXGRP)
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
	if (mode & S_ISVTX)
		s[2] = 'T';
	else if (mode & S_IXOTH)
		s[2] = 'x';
	if (has_acl(path))
		s[3] = '+';
	if (has_extended_attributes(path))
		s[3] = '@';
	return (s);
}

char	*print_permissions(struct stat statbuf, char	*path, \
t_owner_group_info info)
{
	char	*s;
	char	*user;
	char	*group;
	char	*other;
	char	*extra_info;

	user = get_user_permissions(statbuf.st_mode);
	group = get_group_permissions(statbuf.st_mode);
	other = get_others_permissions(statbuf.st_mode, path);
	extra_info = get_extra_info(statbuf, info);
	s = ft_strjoin(user, group, other);
	s = ft_custom_strjoin(s, extra_info, "");
	free(user);
	free(group);
	free(other);
	free(extra_info);
	return (s);
}
