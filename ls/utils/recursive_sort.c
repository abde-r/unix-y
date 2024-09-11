/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:38:08 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/11 20:09:21 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int reverse_compare_case_sensitive(const char *a, const char *b) {
    while (*a && *b) {
        // Convert to lowercase for case-insensitive comparison
        char lower_a = ft_tolower(*a);
        char lower_b = ft_tolower(*b);

        if (lower_a != lower_b) {
            return lower_b - lower_a;
        }

        // If current characters are equal in case-insensitive comparison
        // but different in case-sensitive manner, use case-sensitive order
        // if (*a != *b) {
        //     return *a - *b;
        // }

        a++;
        b++;
    }
    return *b - *a;
}

void sort_recursive_list(t_list **head) {
    if (*head == NULL) return;  // If the list is empty, do nothing

    t_list *current, *next;
    int swapped;

    // First, sort the current list using bubble sort
    do {
        swapped = 0;
        current = *head;

        while (current->next != NULL) {
            next = current->next;

            // Use the custom comparison function
            if (compare_case_sensitive(current->content, next->content) > 0) {
                // Swap the entire node (content and subdirectory)
                char *temp_content = current->content;
                t_list *temp_subdir = current->subdirectory;

                current->content = next->content;
                current->subdirectory = next->subdirectory;

                next->content = temp_content;
                next->subdirectory = temp_subdir;

                swapped = 1;
            }

            current = current->next;
        }
    } while (swapped);

    // Then, recursively sort each subdirectory's linked list
    current = *head;
    while (current != NULL) {
        if (current->subdirectory != NULL) {
            sort_recursive_list(&current->subdirectory);  // Recursively sort the subdirectory list
        }
        current = current->next;
    }
}


void reverse_sort_recursive_list(t_list **head) {
    if (*head == NULL) return;  // If the list is empty, do nothing

    t_list *current, *next;
    int swapped;

    // First, sort the current list using bubble sort
    do {
        swapped = 0;
        current = *head;

        while (current->next != NULL) {
            next = current->next;

            // Use the custom comparison function
            if (reverse_compare_case_sensitive(current->content, next->content) > 0) {
                // Swap the entire node (content and subdirectory)
                char *temp_content = current->content;
                t_list *temp_subdir = current->subdirectory;

                current->content = next->content;
                current->subdirectory = next->subdirectory;

                next->content = temp_content;
                next->subdirectory = temp_subdir;

                swapped = 1;
            }

            current = current->next;
        }
    } while (swapped);

    // Then, recursively sort each subdirectory's linked list
    current = *head;
    while (current != NULL) {
        if (current->subdirectory != NULL) {
            reverse_sort_recursive_list(&current->subdirectory);  // Recursively sort the subdirectory list
        }
        current = current->next;
    }
}















// int w333(const char *a, const char *b) {
    
//     struct stat buff1, buff2;
//     lstat(a, &buff1);
//     lstat(b, &buff2);

//     if (buff1.st_mtime < buff2.st_mtime) {
//         return 1;
//     }
//     return 0;
// }

// void sort_recursive_by_time(t_list **head) {
//     if (*head == NULL) return;  // If the list is empty, do nothing

//     t_list *current, *next;
//     int swapped;

//     // First, sort the current list using bubble sort
//     do {
//         swapped = 0;
//         current = *head;

//         while (current->next != NULL) {
//             next = current->next;

//             // Use the custom comparison function
//             if (w333(current->content, next->content) > 0) {
//                 // Swap the entire node (content and subdirectory)
//                 char *temp_content = current->content;
//                 t_list *temp_subdir = current->subdirectory;

//                 current->content = next->content;
//                 current->subdirectory = next->subdirectory;

//                 next->content = temp_content;
//                 next->subdirectory = temp_subdir;

//                 swapped = 1;
//             }

//             current = current->next;
//         }
//     } while (swapped);

//     // Then, recursively sort each subdirectory's linked list
//     current = *head;
//     while (current != NULL) {
//         if (current->subdirectory != NULL) {
//         // if (is_directory(current->content)) {
//             sort_recursive_by_time(&current->subdirectory);  // Recursively sort the subdirectory list
//         }
//         current = current->next;
//     }
// }



void _swap_nodes(t_list *a, t_list *b) {
    char *temp_content = a->content;
    t_list *temp_subdir = a->subdirectory;

    // Swap content and subdirectory pointers
    a->content = b->content;
    a->subdirectory = b->subdirectory;
    b->content = temp_content;
    b->subdirectory = temp_subdir;
}

void construct_full_path(char *full_path, const char *parent_path, const char *filename) {
    snprintf(full_path, 4096, "%s/%s", parent_path, filename);
}

// Function to sort the files and directories by modification time in a linked list
void sort_list_by_time(t_list **head, const char *parent_path) {
    int swapped;
    t_list *ptr1;
    t_list *lptr = NULL;

    if (*head == NULL) return;

    char full_path1[4096];
    char full_path2[4096];

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            struct stat buff1, buff2;

            // Construct full paths for the two files/directories
            construct_full_path(full_path1, parent_path, ptr1->content);
            construct_full_path(full_path2, parent_path, ptr1->next->content);

            // Get the file stats using lstat
            if (lstat(full_path1, &buff1) == -1 || lstat(full_path2, &buff2) == -1) {
                perror("lstat");
                return;
            }

            // Compare the modification times and swap if necessary
            if (buff1.st_mtime < buff2.st_mtime) {
                _swap_nodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void sort_list_by_access_time(t_list **head, const char *parent_path) {
    int swapped;
    t_list *ptr1;
    t_list *lptr = NULL;

    if (*head == NULL) return;

    char full_path1[4096];
    char full_path2[4096];

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            struct stat buff1, buff2;

            // Construct full paths for the two files/directories
            construct_full_path(full_path1, parent_path, ptr1->content);
            construct_full_path(full_path2, parent_path, ptr1->next->content);

            // Get the file stats using lstat
            if (lstat(full_path1, &buff1) == -1 || lstat(full_path2, &buff2) == -1) {
                perror("lstat");
                return;
            }

            // Compare the modification times and swap if necessary
            // printf("%ld %ld\n", buff1.st_mtime, buff2.st_mtime);
            if (buff1.st_atime < buff2.st_atime) {
                _swap_nodes(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

// Recursive function to sort directories and their contents by modification time
void sort_recursive_by_time(t_list **head, const char *parent_path) {
    t_list *current = *head;
    
    // First, sort the current directory's list (files and subdirectories)
    sort_list_by_time(head, parent_path);

    // Recursively sort each subdirectory
    while (current != NULL) {
        if (is_directory(current->content)) {
            // Construct the new path for the subdirectory
            char new_path[4096];
            construct_full_path(new_path, parent_path, current->content);

            // Sort the subdirectory's contents recursively
            sort_recursive_by_time(&(current->subdirectory), new_path);
        }
        current = current->next;
    }
}

void sort_recursive_by_access_time(t_list **head, const char *parent_path) {
    t_list *current = *head;
    
    // First, sort the current directory's list (files and subdirectories)
    sort_list_by_access_time(head, parent_path);

    // Recursively sort each subdirectory
    while (current != NULL) {
        if (is_directory(current->content)) {
            // Construct the new path for the subdirectory
            char new_path[4096];
            construct_full_path(new_path, parent_path, current->content);

            // Sort the subdirectory's contents recursively
            sort_recursive_by_time(&(current->subdirectory), new_path);
        }
        current = current->next;
    }
}

