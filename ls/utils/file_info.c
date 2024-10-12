/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:06:39 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/12 11:49:49 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

/*
	file extra informations such as the file size, the link, 
	owner name (exclude group info) and the group information
*/
char	*get_extra_info(struct stat statbuf, t_owner_group_info	info)
{
	struct passwd	*pwd;
	struct group	*grp;
	char			*s;
	// char			*temp;
	// char			*temp2;
	// char			*temp3;
	char			*st_size;
	char			*st_link;

	st_size = ft_calloc(10, 1);
	st_link = ft_calloc(10, 1);
	snprintf(st_size, 10, "%ld", statbuf.st_size);
	s = ft_strjoin(st_size, "", "");
	snprintf(st_link, 10, "%lu", statbuf.st_nlink);
	s = ft_custom_strjoin(s, st_link, "");
	if (info.owner_info == 1)
	{
		pwd = getpwuid(statbuf.st_uid);
		s = ft_custom_strjoin(s, pwd->pw_name, " ");
	}
	if (info.group_info == 1)
	{
		grp = getgrgid(statbuf.st_gid);
		if (grp)
			s = ft_custom_strjoin(s, grp->gr_name, " ");
	}
	free(st_size);
	free(st_link);
	return (s);
}

/*
	file info such as permissions and last modification time
	using the C library strftime() function to format the date 
	and time as a string.
*/
char	*print_file_info(char	*file, t_owner_group_info	info, char	*path)
{
	struct stat		statbuf;
	char			*s;
	char			*full_path;
	char			*time_str;

	time_str = ft_calloc(TIME_SIZE, 1);
	full_path = ft_strjoin(path, "/", file);
	if (stat(full_path, &statbuf) == -1)
	{
		perror("stat");
		exit(1);
	}
	char *extra_info = get_extra_info(statbuf, info);
	char *permissions= print_permissions(statbuf.st_mode, full_path);
	char *temp = ft_strjoin(permissions, " ", extra_info);
	// ft_strcat(s, );
	strftime(time_str, TIME_SIZE, "%b %d %H:%M", \
	localtime(&(statbuf.st_mtime)));
	char *temp2 = ft_strjoin(time_str, " ", file);
	s = ft_strjoin(temp, temp2, "");
	free(full_path);
	free(time_str);
	free(extra_info);
	free(permissions);
	free(temp);
	free(temp2);
	return (s);
}
// char	*print_file_info(char	*file, t_owner_group_info	info, char	*path)
// {
// 	struct stat		statbuf;
// 	char			*s;
// 	char			*full_path;
// 	char			*time_str;
// 	char			*_permissions;

// 	time_str = ft_calloc(TIME_SIZE, 1);
// 	// printf("path -%s- file -%s-\n", path, file);
// 	full_path = ft_strjoin(path, "/", file);
// 	if (stat(full_path, &statbuf) == -1)
// 	{
// 		perror("stat");
// 		exit(1);
// 	}
// 	_permissions = print_permissions(statbuf.st_mode, full_path);
// 	s = ft_strjoin(_permissions, get_extra_info(statbuf, info), " ");
// 	// s = ft_strjoin(s, , "");
// 	strftime(time_str, TIME_SIZE, "%b %d %H:%M", \
// 	localtime(&(statbuf.st_mtime)));
// 	s = ft_strjoin(time_str, file, "");
// 	// s = ft_strjoin(s, , "\0");
// 	free(full_path);
// 	free(time_str);
// 	free(_permissions);
// 	return (s);
// }
