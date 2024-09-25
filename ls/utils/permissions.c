/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:52:38 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/24 14:53:07 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

char	*get_user_permissions(mode_t mode)
{
	char	*s;

	s = ft_calloc(3, 1);
	if (S_ISDIR(mode))
		ft_strcat(s, "d");
	else
		ft_strcat(s, "-");
	if (mode & S_IRUSR)
		ft_strcat(s, "r");
	else
		ft_strcat(s, "-");
	if (mode & S_IWUSR)
		ft_strcat(s, "w");
	else
		ft_strcat(s, "-");
	if (mode & S_IXUSR)
		ft_strcat(s, "x");
	else
		ft_strcat(s, "-");
	return (s);
}

char	*get_group_permissions(mode_t mode)
{
	char	*s;

	s = ft_calloc(3, 1);
	if (mode & S_IRGRP)
		ft_strcat(s, "r");
	else
		ft_strcat(s, "-");
	if (mode & S_IWGRP)
		ft_strcat(s, "w");
	else
		ft_strcat(s, "-");
	if (mode & S_IXGRP)
		ft_strcat(s, "x");
	else
		ft_strcat(s, "-");
	return (s);
}

char	*get_others_permissions(mode_t mode)
{
	char	*s;

	s = ft_calloc(3, 1);
	if (mode & S_IROTH)
		ft_strcat(s, "r");
	else
		ft_strcat(s, "-");
	if (mode & S_IWOTH)
		ft_strcat(s, "w");
	else
		ft_strcat(s, "-");
	if (mode & S_IXOTH)
		ft_strcat(s, "x");
	else
		ft_strcat(s, "-");
	return (s);
}

char	*print_permissions(mode_t mode, const char	*path)
{
	char	*s;

	s = ft_strdup("");
	ft_strcat(s, ft_strjoin(get_user_permissions(mode), \
	get_group_permissions(mode), get_others_permissions(mode)));
	if (has_acl(path))
		ft_strcat(s, "x");
	else if (has_extended_attributes(path))
		ft_strcat(s, "@");
	else
		ft_strcat(s, " ");
	return (s);
}
