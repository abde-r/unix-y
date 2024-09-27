/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:06:39 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/26 11:32:21 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

/*
	file extra informations such as the file size, the link, 
	owner name (exclude group info) and the group information
*/
char	*get_extra_info(struct stat statbuf, int	*ownrgrp_info)
{
	struct passwd	*pwd;
	struct group	*grp;
	char			*s;
	char			*st_size;
	char			*st_link;

	st_size = ft_calloc(10, 1);
	st_link = ft_calloc(10, 1);
	snprintf(st_size, 10, "%ld", statbuf.st_size);
	s = ft_strjoin(st_size, " ", "");
	snprintf(st_link, 10, "%lu", statbuf.st_nlink);
	s = ft_strjoin(s, st_link, " ");
	if (ownrgrp_info[0] == 1)
	{
		pwd = getpwuid(statbuf.st_uid);
		s = ft_strjoin(s, pwd->pw_name, " ");
	}
	if (ownrgrp_info[1] == 1)
	{
		grp = getgrgid(statbuf.st_gid);
		if (grp)
			s = ft_strjoin(s, grp->gr_name, " ");
	}
	return (s);
}

/*
	file info such as permissions and last modification time
*/
char	*print_file_info(char	*file, int	*ownrgrp_info, const char	*path)
{
	struct stat		statbuf;
	char			*s;
	char			*full_path;
	char			*time_str;

	// full_path = ft_calloc(9999, 1);
	time_str = ft_calloc(999, 0);
	full_path = ft_strjoin(path, "/", file);
	if (stat(full_path, &statbuf) == -1)
	{
		perror("stat");
		exit(1);
	}
	s = ft_strjoin(print_permissions(statbuf.st_mode, full_path), " ", "");
	ft_strcat(s, get_extra_info(statbuf, ownrgrp_info));
	strftime(time_str, 999, "%b %d %H:%M", localtime(&(statbuf.st_mtime)));
	s = ft_strjoin(s, time_str, " ");
	s = ft_strjoin(s, file, "\0");
	return (s);
}
