/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 21:06:39 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/19 22:42:34 by ael-asri         ###   ########.fr       */
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
	s = ft_strjoin(" ", st_link, " ");
	if (info.owner_info == 0)
	{
		pwd = getpwuid(statbuf.st_uid);
		s = ft_custom_strjoin(s, pwd->pw_name, "  ");
	}
	if (info.group_info == 0)
	{
		grp = getgrgid(statbuf.st_gid);
		if (grp)
			s = ft_custom_strjoin(s, grp->gr_name, " ");
	}
	s = ft_custom_strjoin(s, " ", st_size);
	free(st_size);
	free(st_link);
	return (s);
}

char	*get_month_name(int month)
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
	return (months[month]);
}

char	*format_time_string(time_t mtime)
{
	struct tm	*time_info;
	char		*formated_time;
	char		*hour;
	char		*day;
	char		*min;

	time_info = localtime(&mtime);
	day = ft_itoa(time_info->tm_mday);
	hour = ft_itoa(time_info->tm_hour);
	min = ft_itoa(time_info->tm_min);
	formated_time = ft_strjoin(" ", get_month_name(time_info->tm_mon), " ");
	formated_time = ft_custom_strjoin(formated_time, day, " ");
	formated_time = ft_custom_strjoin(formated_time, hour, ":");
	formated_time = ft_custom_strjoin(formated_time, min, " ");
	free(day);
	free(hour);
	free(min);
	return (formated_time);
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

	if (!ft_strcmp(path, file))
		full_path = ft_strdup(path);
	else
		full_path = ft_strjoin(path, "/", file);
	if (lstat(full_path, &statbuf) == -1)
		return ("");
	s = print_permissions(statbuf, full_path, info);
	time_str = format_time_string(statbuf.st_mtime);
	s = ft_custom_strjoin(s, time_str, file);
	free(full_path);
	free(time_str);
	return (s);
}
