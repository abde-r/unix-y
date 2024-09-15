/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_recursive_display.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:40:43 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/15 14:30:32 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

char *manage_recursive_colors(t_list *head, char *joined_string, char *current_path) {
    int count = 0;
    char *s = malloc(4096);  // Allocate memory for the final string
    if (s == NULL) {
        perror("malloc");
        return NULL;
    }
    s[0] = '\0';  // Initialize the string as empty

    // Split the joined_string by newlines into `items`
    char **items = ft_split(joined_string, '\n');
    while (items[count]) {
        count++;
    }

    if (count == 0) {
        free(items);  // Free allocated memory for empty split result
        return s;
    }

    int i = 0;
    char temp[1024];  // Temporary buffer for formatted output

    // Iterate through the linked list and apply color only to the file/dir name
    while (head != NULL && i < count) {
        const char *color = get_file_color(head->content);  // Get the color for the file/dir name

        // Combine the current path with the file/dir name
        char *full_path = ft_strjoin(current_path, head->content, "");

        // Check if the item is a directory
        if (is_directory(full_path)) {
            // Format the directory with color
            snprintf(temp, sizeof(temp), "%s%s%s%s\n", COLOR_RESET, ft_substr(items[i], 0, ft_strlen(items[i]) - ft_strlen(head->content)), color, head->content);

            // Append the formatted directory to `s`
            strcat(s, temp);

            // Recursively list and color the contents of the subdirectory
            char *subdir_items = list_directory(full_path);  // List subdirectory contents
            if (is_directory(head->content)) {
                printf("we weeeee");
                // Process subdirectory contents recursively
                char *subdir_output = manage_recursive_colors(head, subdir_items, ft_strjoin(full_path, "/", ""));

                // Append subdirectory results to `s`
                s = realloc(s, strlen(s) + strlen(subdir_output) + 1);  // Reallocate to fit new output
                strcat(s, subdir_output);

                // Clean up subdir items and output
                free(subdir_items);
                free(subdir_output);
            }
        } else {
            // Format the file with color
            snprintf(temp, sizeof(temp), "%s%s%s%s\n", COLOR_RESET, ft_substr(items[i], 0, ft_strlen(items[i]) - ft_strlen(head->content)), color, head->content);
            strcat(s, temp);  // Append formatted file to `s`
        }

        // printf("sss %s\n", s);
        // Move to the next node in the linked list
        head = head->next;
        i++;
        free(full_path);  // Free the full path memory after use
    }

    // Free the allocated memory for `items`
    for (int i = 0; i < count; i++) {
        free(items[i]);
    }
    free(items);

    // printf("s %s\n", s);
    // exit(1);
    return s;  // Return the final string
}
