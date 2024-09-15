/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:23 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/15 12:42:47 by ael-asri         ###   ########.fr       */
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

#include <sys/ioctl.h>

#define COLOR_DIR     "\033[1;34m"  // Blue
#define COLOR_EXEC    "\033[1;32m"  // Green
#define COLOR_RESET   "\033[0m"
#define COLOR_LINK    "\033[1;36m"  // Cyan for symlinks

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	struct s_list	*subdirectory;
}				t_list;

//---	parse
char	*opts_parser(char **av, char **path);


//--- sort
void	sort_list(t_list **head);
int		compare_case_sensitive(const char *a, const char *b);
void	sort_by_time(t_list **output);
void	reverse_order(t_list **output);
void	sort_by_access_time(t_list **output);
void	sort_recursive_list(t_list **head);
void	reverse_sort_recursive_list(t_list **head);
void	sort_recursive_by_time(t_list **output, const char *path);
void	sort_recursive_by_access_time(t_list **head, const char *parent_path);
char	*generate_recursive_listing_result(t_list *head, char delim, int _hide_owner, int _hide_group_info, const char *path);

//--- helper
void	ls(t_list   **head, const char *path);
void	ls_R(t_list **head, const char *path);
char	*ls_d(const char *path);
char	*opts_executer(t_list **head, const char *opts, const char *path);


//--- list utils
t_list	*create_node(const char *content);
void	insert_node(t_list **head, const char   *content);


//--- listing info
char	*generate_result(t_list *head, char delim);
char	*generate_listing_result(t_list *head, char delim, int _hide_owner, int _hide_group_info_, const char *path);
char	*generate_recursive_result(t_list *head, char delim);
char	*print_file_info(char *filename, const struct stat *file_stat, int _hide_owner, int _hide_group_info_, const char *path);
void	print_recursive_list(t_list *head, int depth);

//--- utils
size_t	ft_strlen(const char *s);
int		ft_strcmp();
int		ft_strchr(const char *s, const char c);
int		is_directory(const char *path);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2, char *s3);
char	*ft_strchrjoin(char *s1, char *s2, char delim);
char	*ft_substr(char *s, unsigned int start, size_t	len);
char	*ft_strdup(const char *s1);
// void	ft_lstadd(t_list **lst, char *content);
void	swap_nodes(t_list* a, t_list* b);
void	*ft_calloc(size_t count, size_t size);
int		ft_tolower(int c);
int		ft_strcat(char *dst, const char *src);
int		ft_lstcontentsize(t_list *lst);


//--- Bonus
int		has_extended_attributes(const char *path);
int		has_acl(const char *path);
char	*manage_columns(char *joined_string);
char	*manage_colors(t_list *head, char *joined_string);
const	char*	get_file_color(const char* path);
char	*manage_recursive_columns(char *joined_string, char *path);
char	*print_in_columns(char **items, int count, int max_len);
size_t	calculate_max_len(char **items, int count);
char	*list_directory(const char *dir_path);
char	*manage_recursive_colors(t_list *head, char *joined_string, char *current_path);
// NOT WORKING CASES
// ./ft_ls -laRrt accures a segfault