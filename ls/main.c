/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:32 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/16 20:01:25 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void print_recursive_list(t_list *head, int depth) {
    t_list *current = head;

    // First, print all files and directories at the current level
    while (current != NULL) {
        // Print the file or directory name with appropriate indentation
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }
		printf("%s\n", current->content);

        current = current->next;
    }

    // // Second, print the contents of any subdirectories
    current = head;  // Reset current pointer to head
    while (current != NULL) {
        // if (current->subdirectory != NULL) {
        if (is_directory(current->content)) {
            // Print the subdirectory name, followed by its contents
            for (int i = 0; i < depth; i++) {
                printf("  ");
            }
            printf("%s:\n", current->content);
            print_recursive_list(current->subdirectory, depth + 1);  // Recursively print subdirectory contents
        }
        current = current->next;
    }
}


int main(int ac, char **av) {

    t_list	*head = 0;
    char	*opts;
    char	*path = ft_calloc(999, 1);
	char *final_res = ft_calloc(999, 1);
    // char *cl = ft_calloc(999, 1);
    // char *clr = ft_calloc(999, 1);
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

		


		// while (head != NULL) {
		// 	printf("%s\n", head->content);

		// 	t_list *subnode = head->subdirectory;
		// 	while (subnode != NULL) {
		// 		printf("  %s\n", subnode->content);
		// 		subnode = subnode->next;
		// 	}
			
		// 	head = head->next;
		// }
		// exit(1);

		final_res = opts_executer(&head, opts, path);
		// printf(".:\n");
	    // print_recursive_list(head, 0);
		// exit(1);
	}

    if (ft_strchr(opts, 'R')) {
        if (!ft_strchr(opts, 'l')) { // -l doesn't exist

            // char *sf = ft_calloc(999, 1);
            // // char **items = split_string(final_res, ":");
            // char **items = ft_split(final_res, ':');
            // // char **data = ft_calloc(9999, 1);
            
            // // for (size_t i=0;i<ft_arrlen(items);i++) {
            // //     char **item = split_string(items[i], "\n");
            // //     // printf("1 %s 2 %s\n", item[0], item[1]);
                
            // //     if (item[1])
            // //         data[i] =  ft_strdup(item[1]);
            // //     else
            // //         data[i] =  ft_strdup("");
            // //     // printf("hgana %s\n", data[i]);
                    
            // // }
            // // data[i] =  ft_strdup("\n");

            
            // sf = ft_strjoin(".:\n", sf, manage_recursive_columns(items[0], path));
            // sf = ft_strjoin(sf, "\n", "");
            // // int x=0;
            // for (size_t i=1;i<ft_arrlen(items);i++) {
            //     // printf("          %s\n", items[i]); 
            //     if ((i%2)) {
            //         if (ft_strlen(items[i]) > 0)
            //             sf = ft_strjoin(sf, manage_recursive_columns(items[i], path), "");
            //         else
            //             sf = ft_strjoin(sf, "\n", "");
            //     }
            //     else {
            //         // printf("yoooooooo %s\n", data[i]);
            //         // sf = ft_strjoin(sf, data[i], "\n");
            //         sf = ft_strjoin(sf, manage_recursive_columns(items[i], path), "");

            //         // printf("--- %s\n", items[i]);
            //     }
            // }
            printf("%s", manage_recursive_columns(final_res));
        }
        else { // -l exists
			// printf("we weew%s\n", final_res);
			printf("%s", manage_recursive_colors(final_res));
		}

	    // print_recursive_list(head, 0);
		// exit(1);

    }
    else {
        if (!ft_strchr(opts, 'l')) // -l doesn't exist
            printf("%s", manage_columns(final_res));
        else
            printf("%s", manage_colors(head, final_res));
    }

	return (0);
}
