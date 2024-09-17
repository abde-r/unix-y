/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:34:46 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/16 22:52:38 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int compare_case_sensitive(const char *a, const char *b) {
    while (*a && *b) {
        char lower_a = ft_tolower(*a);
        char lower_b = ft_tolower(*b);

        if (lower_a != lower_b) {
            return lower_a - lower_b;
        }

        a++;
        b++;
    }
    return *a - *b;
}

void sort_list(t_list **head) {
    if (*head == NULL) return; // If the list is empty, do nothing

    t_list *current, *next;
    char *temp;
    int swapped;

    do {
        swapped = 0;
        current = *head;

        while (current->next != NULL) {
            next = current->next;
            // Use the custom comparison function
            if (compare_case_sensitive(current->content, next->content) > 0) {
                // Swap contents if they are out of order
                temp = current->content;
                current->content = next->content;
                next->content = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

void	sort_by_time(t_list **output) {

    int swapped;
    t_list* ptr1;
    t_list* lptr = NULL;

	swapped = 1;
    while (swapped) {
        swapped = 0;
        ptr1 = *output;

        while (ptr1->next != lptr) {
            struct stat buff1, buff2;
            lstat(ptr1->content, &buff1);
            lstat(ptr1->next->content, &buff2);

            if (buff1.st_mtime < buff2.st_mtime) {
                swap_nodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
}

void	sort_by_access_time(t_list **output) {

    int swapped;
    t_list* ptr1;
    t_list* lptr = NULL;

	swapped = 1;
    while (swapped) {
        swapped = 0;
        ptr1 = *output;

        while (ptr1->next != lptr) {
            struct stat buff1, buff2;
            lstat(ptr1->content, &buff1);
            lstat(ptr1->next->content, &buff2);

            if (buff1.st_atime < buff2.st_atime) {
                swap_nodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
}

void	reverse_order(t_list **output) {
	t_list* prev = NULL;
    t_list* current = *output;
    t_list* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *output = prev;
}