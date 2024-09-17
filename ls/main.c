/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:32 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/16 22:48:28 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

// void print_recursive_list(t_list *head, int depth) {
//     t_list *current = head;

//     // First, print all files and directories at the current level
//     while (current != NULL) {
//         // Print the file or directory name with appropriate indentation
//         for (int i = 0; i < depth; i++) {
//             printf("  ");
//         }
// 		printf("%s\n", current->content);

//         current = current->next;
//     }

//     // // Second, print the contents of any subdirectories
//     current = head;  // Reset current pointer to head
//     while (current != NULL) {
//         // if (current->subdirectory != NULL) {
//         if (is_directory(current->content)) {
//             // Print the subdirectory name, followed by its contents
//             for (int i = 0; i < depth; i++) {
//                 printf("  ");
//             }
//             printf("%s:\n", current->content);
//             print_recursive_list(current->subdirectory, depth + 1);  // Recursively print subdirectory contents
//         }
//         current = current->next;
//     }
// }


int main(int ac, char **av) {

    t_list	*head = 0;
    char	*opts;
    char	*path = ft_calloc(999, 1);
	char *final_res = ft_calloc(999, 1);
    
    (void)ac;
	
    // parse & error checking
    opts = opts_parser(av, &path);

	if (ft_strchr(opts, 'd')) // Print directories themselves, not their contents
        final_res = ft_strjoin(ls_d(path), "\0", "");
    else {
		if (ft_strchr(opts, 'R')) // if -R exists, execute ls with -R flag
			ls_R(&head, path);
		else if (!ft_strchr(opts, 'R')) { // else if -R doesn't exist, execute default ls
			ls(&head, path);
		}

		final_res = opts_executer(&head, opts, path);
	}

    if (ft_strchr(opts, 'R')) {
        if (!ft_strchr(opts, 'l')) // -l doesn't exist
            printf("%s", manage_recursive_columns(final_res));
        else // -l exists
			printf("%s", manage_recursive_colors(final_res));
    }
    else {
        if (!ft_strchr(opts, 'l')) // -l doesn't exist
            printf("%s", manage_columns(final_res));
        else // -l exists
            printf("%s", manage_colors(head, final_res));
    }

	return (0);
}
