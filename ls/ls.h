/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:23 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/26 22:38:03 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <sys/acl.h>
#include <errno.h>
#include <sys/ioctl.h>

#define COLOR_DIR     "\033[1;34m"  // Blue
#define COLOR_EXEC    "\033[1;32m"  // Green
#define COLOR_RESET   "\033[0m"
#define COLOR_LINK    "\033[1;36m"  // Cyan for symlinks

#define TIME_SIZE	1024
#define PATH_SIZE	1024

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	struct s_list	*subdirectory;
}				t_list;

typedef struct s_owner_group_info
{
	int	owner_info;
	int	group_info;
}				t_owner_group_info;

//---	Parse
char	*opts_parser(char **av, char **path);

//---	Sort
void	sort_list(t_list **head);
int		compare_case_sensitive(char *a, char *b);
void	reverse_order(t_list **output);
void	sort(t_list **head, int __reverse_flag_);
void	sort_time(t_list **output, char *path, int __flag_);
char	*get_recursive_listing_result(t_list *head, char delim, \
t_owner_group_info	info, char *path);
int		swap_nodes(t_list	*a, t_list	*b);
int		reverse_compare_case_sensitive(const char	*a, const char	*b);
int		sort_state(t_list	*current, t_list	*next, int __reverse_flag_);
void	sort_by_access_time(t_list	**output, char	*path);
void	sort_by_time(t_list	**output, char	*path);

//---	Helpers
void	ls(t_list	**head, char	*path);
void	ls_recursive(t_list	**head, char	*path);
char	*executer(t_list	**head, char	*opts, char	*path);
char	*ft_ls(t_list	**head, char	*opts, char	*path);

//---	listing info
char	*generate_result(t_list	*head, char delim);
char	*generate_listing_result(t_list	*head, char delim, \
t_owner_group_info	info, char	*path);
char	*generate_recursive_result(t_list *head, char delim);
char	*print_file_info(char	*filename, \
t_owner_group_info	info, char *path);
void	print_recursive_list(t_list *head, int depth);

//---	libft utils
size_t	ft_strlen(char *s);
size_t	ft_arrlen(char **s);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strchr(const char *s, const char c);
int		is_directory(const char *path);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2, char *s3);
char	*ft_custom_strjoin(char *s1, char *s2, char *s3);
char	*ft_strchrjoin(char *s1, char *s2, char delim);
char	*ft_substr(char *s, unsigned int start, size_t	len);
char	*ft_strdup(char *s1);
size_t	ft_strncpy(char *dst, char *src, size_t	dstsize);
void	*ft_calloc(size_t count, size_t size);
int		ft_tolower(int c);
int		ft_strcat(char *dst, char *src);
int		ft_lstcontentsize(t_list *lst);
char	*ft_itoa(int n);
void	ft_free(char	**items);
void	ft_putchar(char	**paths, char	*s, size_t index);
t_list	*create_node(char	*content);
void	insert_node(t_list	**head, char	*content);
DIR		*get_current_dir(const char	*path);
int		char_finder(char	*s);
void	unauth_message(t_list	**head, char	*path);
void	lstat_norm(char	*path, char	*content, struct stat *buff);
int		lstat_condition_norm(char	*name, char	*path, \
struct stat *statbuf);
int		is_content_valid(char	*s);
void	lstadd_front(t_list **lst, t_list *new);
void	delete_null_nodes(t_list	**head);
int		custom_compare(char	*a, char	*b);
t_list	*create_nnode(char	*path, char	*content);
void	insert_nnode(t_list	**head, char	*path, char	*content);
t_list	*get_final_list(t_list	*head, char	**paths, char	*options);
void	print_final_list(t_list	*head, char	*options);
void	swap_list_nodes(t_list	*current, t_list	*next, int	*swapped);
void	handle_failure(t_list	**head, char	*path, DIR	*dp, \
struct stat statbuf);
void	ft_putchr(char	*s);

//---	Memory Free
void	free_subdirectory(t_list *subdir);
void	outer_free(t_list	*head, char	*temp_s);
void	outer_free2(char	**paths);
void	freee(t_list	**head);
void	ft_free2(t_list	**head, char	**t);

//---	Bonus
int		has_extended_attributes(char	*path);
int		has_acl(char	*path);
char	*manage_columns(char *joined_string);
char	*get_file_color(const char	*path);
char	*manage_recursive_columns(char *joined_string);
char	*print_in_columns(char **items, int count, int max_len);
size_t	calculate_max_len(char **items, int count);
char	*print_permissions(struct stat statbuf, char	*path, \
t_owner_group_info info);
char	*manage_recursive_colors(char **items, char	*path, int in_directory);
int		get_terminal_width(void);
size_t	calculate_max_len(char	**items, int count);
char	*get_content_color(char	*s, int max_len, int index, int count);
char	*add_color(char	*s);
int		get_dir_total(char	*path);
int		return_error(char	*err);
char	*get_extra_info(struct stat statbuf, t_owner_group_info	info);
char	*get_file_info_temp(t_list	*current, t_owner_group_info \
info, char	*path);
char	*get_temp(t_list	*current, char delim);
