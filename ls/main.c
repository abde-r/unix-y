/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:32 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/05 12:15:31 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

// void print_list(t_list *node, int depth) {
//     while (node) {
//         for (int i = 0; i < depth; ++i) {
//             printf(" ");
//         }
//         printf("%s\n", node->content);

//         if (node->subdirectory) {
//             print_list(node->subdirectory, depth + 1);
//         }

//         node = node->next;
//     }
// }

// void print_list(t_list *node, int depth) {
//     while (node) {
//         // Print the directory name or current path indication (for root)
//         if (depth == 0) {
//             printf(".:\n");  // Root directory represented by '.'
//         } else {
//             printf("%s:\n", node->content);
//         }

//         // Print all files and directories in the current directory
//         t_list *content = node->subdirectory;
//         while (content) {
//             printf("%s\n", content->content);
//             content = content->next;
//         }

//         // Separate directories with a newline for clarity
//         if (node->subdirectory && node->subdirectory->subdirectory) {
//             printf("\n");
//         }

//         // Recursively print subdirectories
//         content = node->subdirectory;
//         while (content) {
//             if (content->subdirectory) {
//                 print_list(content, depth + 1);
//             }
//             content = content->next;
//         }

//         node = node->next;
//         if (node) {
//             printf("\n");
//         }
//     }
// }

// void print_list(t_list* node) {

//     while (node) {
//     printf("hola\n");
//         printf("%s:\n", node->content);

//         // Print all files and directories in the current directory
//         t_list* content = node->subdirectory;
//         while (content) {
//             printf("%s\n", content->content);
//             content = content->next;
//         }

//         // Print a newline for separation
//         printf("\n");

//         // Recursively print subdirectories
//         content = node->subdirectory;
//         while (content) {
//             if (content->subdirectory) {
//                 print_list(content);
//             }
//             content = content->next;
//         }

//         node = node->next;
//     }
// }

int main(int ac, char **av) {

    t_list	*head = 0;
    char	*opts;
    (void)ac;
	
    // parse & error checking
    opts = opts_parser(av);

    if (ft_strchr(opts, 'R')) // if -R exists, execute ls with -R flag
        ls_R(&head, ".");
    else if (!ft_strchr(opts, 'R')) // else if -R doesn't exist, execute default ls
   {     ls(&head, ".");
   } 
    // while (head) {
    //     if (head->subdirectory)
    //         printf("DIR-%s\n", head->content);
    //     else
    //         printf("%s\n", head->content);
    //     head = head->next;
    // }
    // exit(1);
	// execute other options
    
    char *final_res = opts_executer(&head, opts);

    // // Print the final result
    printf("%s", final_res);
    // (void)opts;
    // (void)final_res;
	// print_list(head);
    
    return (0);
}