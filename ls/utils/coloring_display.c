/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:53:33 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/20 09:54:05 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

const char* get_file_color(const char* path) {
    struct stat file_stat;

    if (lstat(path, &file_stat) == -1) {
        // printf("path %s\n", path);
        // perror("lstat");
        return COLOR_RESET;  // Return reset color if error
    }

    if (S_ISDIR(file_stat.st_mode)) {
        return COLOR_DIR;  // Directory -> Blue
    } else if (S_ISLNK(file_stat.st_mode)) {
        return COLOR_LINK;  // Symbolic Link -> Cyan
    } else if (file_stat.st_mode & S_IXUSR) {
        return COLOR_EXEC;  // Executable -> Green
    } else {
        return COLOR_RESET;  // No color for regular files
    }
}

char *manage_colors(t_list *head, char *joined_string) {

    int count = 0;
    char *s = malloc(9999);  // Allocate memory for the final string
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
        return "";
    }

    int i = 0;
    char temp[1024];  // Temporary buffer for formatted output

    // Iterate through the linked list and apply color only to the file/dir name
    while (head != NULL && i < count) {
        const char *color = get_file_color(head->content);  // Get the color for the file/dir name

        // Get the length of the file/dir name to separate it from the rest of the string
        // int name_len = strlen(head->content);

        // Format the item: color the file name and leave the rest uncolored
        snprintf(temp, sizeof(temp), "%s%s%s%s", COLOR_RESET, ft_substr(items[i], 0, ft_strlen(items[i]) -ft_strlen(head->content)), color, head->content);

        // Append the formatted item to `s`
        strcat(s, temp);

        // Append a newline at the end of each row
        strcat(s, "\n");

        // Move to the next node in the linked list
        head = head->next;
        i++;
    }

    // Free the allocated memory for `items`
    for (int i = 0; i < count; i++) {
        free(items[i]);
    }
    free(items);

    return s;  // Return the final string
}
