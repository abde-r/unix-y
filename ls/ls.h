/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:23 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/04 11:25:45 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>


typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	struct s_list	*subdirectory;
}				t_list;

//---	parse
char	*opts_parser(char **av);

//--- sort
void	sort_list(t_list **head);
void	sort_by_time(t_list **output);
void	reverse_order(t_list **output);

//--- helper
void	ls(t_list   **head, const char *path);
void	ls_R(t_list **head, char *path);
char	*opts_executer(t_list **head, const char *opts);

//--- list utils
t_list	*create_node(const char *content);
void	insert_node(t_list **head, const char   *content);

//--- utils
size_t	ft_strlen(const char *s);
int		ft_strcmp();
int		ft_strchr(const char *s, const char c);
int		is_directory(char *path);
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


// NOT WORKING CASES
// ./ft_ls -laRrt accures a segfault