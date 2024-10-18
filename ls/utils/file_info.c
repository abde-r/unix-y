/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:06:39 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/16 13:19:53 by ael-asri         ###   ########.fr       */
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
	char			*st_size;
	char			*st_link;

	st_size = ft_itoa(statbuf.st_size);
	st_link = ft_itoa(statbuf.st_nlink);
	s = ft_strdup(st_link);
	if (info.owner_info == 0)
	{
		pwd = getpwuid(statbuf.st_uid);
		s = ft_custom_strjoin(s, " ", pwd->pw_name);
	}
	if (info.group_info == 0)
	{
		grp = getgrgid(statbuf.st_gid);
		if (grp)
			s = ft_custom_strjoin(s, " ", grp->gr_name);
	}
	s = ft_custom_strjoin(s, " ", st_size);
	free(st_size);
	free(st_link);
	return (s);
}

char	*get_months(int n)
{
	char	*months[12];

	months[0] = "Jan";
	months[1] = "Feb";
	months[2] = "Mar";
	months[3] = "Apr";
	months[4] = "May";
	months[5] = "Jun";
	months[6] = "Jul";
	months[7] = "Aug";
	months[8] = "Sep";
	months[9] = "Oct";
	months[10] = "Nov";
	months[11] = "Dec";
	return (months[n]);
}

char	*format_time_string(time_t mtime)
{
	struct tm	*tm_info;
	char		*t;
	char		*day;
	char		*hour;
	char		*min;

	tm_info = localtime(&mtime);
	day = ft_itoa(tm_info->tm_mday);
	hour = ft_itoa(tm_info->tm_hour);
	min = ft_itoa(tm_info->tm_min);
	t = ft_strjoin(" ", get_months(tm_info->tm_mon), "");
	t = ft_custom_strjoin(t, " ", day);
	t = ft_custom_strjoin(t, " ", hour);
	t = ft_custom_strjoin(t, ":", min);
	t = ft_custom_strjoin(t, " ", "");
	free(day);
	free(hour);
	free(min);
	return (t);
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
	char			*extra_info;
	char			*permissions;

	if (!ft_strcmp(path, file))
		full_path = ft_strdup(path);
	else
		full_path = ft_strjoin(path, "/", file);

	// if (stat(full_path, &statbuf) == -1)
	// {
	// 	perror("stat");
	// 	exit(1);
	// }
	if (lstat(full_path, &statbuf) != -1)
	{
	// printf("FULLPATH -%s-\n", full_path);
	extra_info = get_extra_info(statbuf, info);
	permissions = print_permissions(statbuf.st_mode, full_path);
	s = ft_strjoin(permissions, " ", extra_info);
	time_str = format_time_string(statbuf.st_mtime);
	s = ft_custom_strjoin(s, time_str, file);
	free(full_path);
	free(time_str);
	free(extra_info);
	free(permissions);
	return (s);
	}
	return ft_strdup("la yomkin asat");
}
