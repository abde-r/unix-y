/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:23 by ael-asri          #+#    #+#             */
/*   Updated: 2024/08/29 16:41:48 by ael-asri         ###   ########.fr       */
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
}				t_list;

//---	parse
char	*opts_parser(char **av);

//--- sort
void	sort_list(t_list **head);
void	sort_by_time(t_list **output);
void	reverse_order(t_list **output);

//--- helper
void	ls(t_list   **output, char *path);
void	ls_R(t_list **output, char *path, int depth);
char	*opts_executer(t_list *output, char *opts);

//--- utils
size_t	ft_strlen();
int		ft_strcmp();
int		ft_strchr(const char *s, const char c);
int		is_directory(char *path);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2, char *s3);
char	*ft_strchrjoin(char *s1, char *s2, char delim);
char	*ft_substr(char *s, unsigned int start, size_t	len);
void	ft_lstadd(t_list **lst, char *content);
void	swap_nodes(t_list* a, t_list* b);
void	*ft_calloc(size_t count, size_t size);
int		ft_tolower(int c);
int		ft_strcat(char *dst, char *src);
