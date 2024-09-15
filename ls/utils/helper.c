/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:38:25 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/15 14:02:22 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

void	remove_hiddens(t_list **head) {
	t_list* current = *head;
    t_list* prev = NULL;

    // Iterate over the linked list
    while (current != NULL) {
        if (current->content[0] == '.') {
            if (prev == NULL) {
                // This node is the head of the list
                *head = current->next;
                // free(current->content);
                free(current);
                current = *head;
            } else {
                // This node is not the head, remove it from the list
                prev->next = current->next;
                free(current->content);
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void remove_recursive_hiddens(t_list **head) {
    t_list *current = *head;
    t_list *prev = NULL;

    while (current != NULL) {
        // First, handle the subdirectory recursively
        if (current->subdirectory != NULL) {
            remove_recursive_hiddens(&(current->subdirectory));
        }

        // Then, check if the current node should be removed
        if (current->content[0] == '.') {
            if (prev == NULL) {
                // This node is the head of the list
                *head = current->next;
                free(current->content);
                free(current);
                current = *head;
            } else {
                // This node is not the head, remove it from the list
                prev->next = current->next;
                free(current->content);
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

char	*opts_executer(t_list **head, const char *opts, const char *path) {
    
	char *t = ft_calloc(999, 1);
    // 1- d
    // 2- R
    // 3- a
    // 4- t
    // 5- r
    // 6- l
    
	
    if (ft_strchr(opts, 'R')) { // if -R exists

        if (!ft_strchr(opts, 'a') && !ft_strchr(opts, 'f')) // remove hidden files and dirs => anything start with a dot
			remove_recursive_hiddens(head);

        if (!ft_strchr(opts, 'f')) // No sorting and includes hidden files
			sort_recursive_list(head);

        if (ft_strchr(opts, 't')) // sort by time
			sort_recursive_by_time(head, path);
        // print_recursive_list(*head, 0);
        // exit(1);
        if (ft_strchr(opts, 'r')) // reverse the order
			reverse_sort_recursive_list(head);
        if (ft_strchr(opts, 'u')) // Sort by last access time
			sort_recursive_by_access_time(head, path);
		
        if (ft_strchr(opts, 'l') || ft_strchr(opts, 'g') || ft_strchr(opts, 'o')) { // generate a string joined by new line
			int _hide_owner;
			int	_hide_group_info_;

			_hide_owner = ft_strchr(opts, 'g') ? 0 : 1; // Hide the owner of the file
			_hide_group_info_ = ft_strchr(opts, 'o') ?  0 : 1; // Hide the group name
	        
			t = generate_recursive_listing_result(*head, '\n', _hide_owner, _hide_group_info_, path);
            // printf("y %s\n", t);
            // t = generate_recursive_result(*head, '\n');
            // printf("o\n");

		}
        else if (!ft_strchr(opts, 'l') && !ft_strchr(opts, 'g') && !ft_strchr(opts, 'o')) // generate a string joined by space
            // t = generate_result(*head, ' ');
            t = generate_recursive_result(*head, ' ');


        // if (ft_strchr(opts, 't')) // sort by time
        //     sort_by_time(head);
        // if (ft_strchr(opts, 'r')) // reverse the order
        //     reverse_order(head);
        
        // printf("res gen %s\n", generate_final_res(output, '\n'));
        
        // if (ft_strchr(opts, 'l')) // generate a string joined by new line
        //     t = generate_recursive_result(*head, '\n');
        // else if (!ft_strchr(opts, 'l')) // generate a string joined by space
        
        // printf("why not sorted\n");
        // printf("%s", t);
        // exit(1);
    }
    else if (!ft_strchr(opts, 'R')) { // else if -R doesn't exist
        if (!ft_strchr(opts, 'a') && !ft_strchr(opts, 'f')) // remove hidden files and dirs => anything start with a dot
            remove_hiddens(head);
        
        if (!ft_strchr(opts, 'f')) // No sorting and includes hidden files
			sort_list(head);

        if (ft_strchr(opts, 't')) // sort by time
			sort_by_time(head);
        if (ft_strchr(opts, 'r')) // reverse the order
			reverse_order(head);
        if (ft_strchr(opts, 'u')) // Sort by last access time
			sort_by_access_time(head);

        if (ft_strchr(opts, 'l') || ft_strchr(opts, 'g') || ft_strchr(opts, 'o')) { // generate a string joined by new line
			int _hide_owner;
			int	_hide_group_info_;

			_hide_owner = ft_strchr(opts, 'g') ? 0 : 1; // Hide the owner of the file
			_hide_group_info_ = ft_strchr(opts, 'o') ?  0 : 1; // Hide the group name
	        
			t = generate_listing_result(*head, '\n', _hide_owner, _hide_group_info_, path);
		}
        else if (!ft_strchr(opts, 'l') && !ft_strchr(opts, 'g') && !ft_strchr(opts, 'o')) // generate a string joined by space
            t = generate_result(*head, ' ');
    }

	return t;
    
}
