/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:32 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/22 16:24:34 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

int	custom_compare(char	*a, char	*b)
{
	char	lower_a;
	char	lower_b;

	while (*a && *b)
	{
		lower_a = *a;
		lower_b = *b;
		if (lower_a != lower_b)
			return (lower_a - lower_b);
		a++;
		b++;
	}
	return (*a - *b);
}

char	*sort_final_list(t_list **head) {
    t_list	*current;
    t_list	*next;
    char	*temp;
    char	*result;
    int		swapped;

    swapped = 1;
    result = ft_strdup("");

    // Bubble sort to rearrange the linked list content
    while (swapped) {
        swapped = 0;
        current = *head;

        while (current != NULL && current->next != NULL) {
            next = current->next;
            if (is_directory(current->content)) {
                if (custom_compare(current->content, next->content) > 0) {
                    // Swap the contents
                    temp = current->content;
                    current->content = next->content;
                    next->content = temp;
                    swapped = 1;
                }
            }
            current = current->next;
        }
    }

    // Traverse the sorted list to generate the result string
    current = *head;
    while (current != NULL) {
        if (!is_directory(current->content)) {
			printf("content -%s-\n", current->subdirectory->content);
            result = ft_custom_strjoin(result, current->subdirectory->content, " ");
        	current->content = NULL;
			current->subdirectory = NULL;
		}
        current = current->next;
    }

    return result;
}

// char	*sort_final_list(t_list	**head)
// {
// 	t_list	*current;
// 	t_list	*next;
// 	char	*temp;
// 	char	*t;
// 	int		swapped;

// 	swapped = 1;
// 	t = ft_strdup("");
// 	while (swapped)
// 	{
// 		swapped = 0;
// 		current = *head;
// 		while (current->next != NULL)
// 		{
// 			next = current->next;
// 			if (is_directory(current->content))
// 			{
// 				printf("whattt %s\n", current->content);
// 				if (custom_compare(current->content, next->content) > 0)
// 				{
// 					temp = current->content;
// 					current->content = next->content;
// 					next->content = temp;
// 					swapped = 1;
// 				}
// 			}
// 			else
// 			{
// 				printf("yooooo %s\n", current->content);
// 				t = ft_custom_strjoin(t, current->content, " ");
// 				current->content = NULL;
// 				current->subdirectory = NULL;
// 			}
				
// 			current = current->next;
// 		}
// 	}
// 	return (t);
// }

void	final_list(t_list	*head)
{
	char *t = sort_final_list(&head);
	char c;
	t_list	*front_node = create_node(t);
	free(t);
	lstadd_front(&head, front_node);
	while (head)
	{
		if (head->content)
		{
			c = '\0';
			if (head->next)
				c = '\n';
			if (!head->subdirectory)
				printf("%s", head->content);
			else
			{
				printf("%s:\n", head->content);
				printf("%s", head->subdirectory->content);
			}
			printf("%c", c);
		}
		head = head->next;
	}
}

t_list	*create_nnode(char	*path, char	*content)
{
	t_list	*new_node;

	new_node = ft_calloc(1, sizeof(t_list));
	if (!new_node)
	{
		perror("Failed to allocate memory");
		exit(EXIT_FAILURE);
	}
	new_node->content = ft_strdup(path);
	new_node->next = NULL;
	new_node->subdirectory = create_node(content);
	return (new_node);
}

void	insert_nnode(t_list	**head, char	*path, char	*content)
{
	t_list	*new_node;
	t_list	*current;

	char *temp = ft_substr(content, 0, ft_strlen(content) - 1);
	new_node = create_nnode(path, temp);
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	free(temp);
}

int	main(int ac, char	**av)
{
	t_list	*head;
	t_list	*list;
	char	*options;
	char	**paths;
	char	*final_res;
	char	*temp_s;
	int		i;

	paths = ft_calloc(ac, PATH_SIZE);
	options = opts_parser(av, paths);
	i = 0;
	list = 0;
	while (paths[i])
	{
		head = 0;
		final_res = ft_ls(&head, options, paths[i]);
		if (!char_finder(options) && !ft_strchr(options, 'd'))
			temp_s = manage_recursive_columns(final_res);
		else if (!ft_strchr(options, 'd'))
			temp_s = manage_recursive_colors(ft_split(final_res, '\n'), paths[i], 0);
		else
			temp_s = ft_strdup(final_res);
		insert_nnode(&list, paths[i], temp_s);
		// list->subdirectory->content = temp_s;
		// ft_putchar(paths, temp_s, i);
		outer_free(head, temp_s);
		i++;
	}
	outer_free2(paths, &options, &final_res);
	final_list(list);
	return (0);
}
