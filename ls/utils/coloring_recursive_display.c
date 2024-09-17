/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring_recursive_display.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 12:40:43 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/16 20:24:25 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int get_dir_total(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    int total_blocks = 0;
    char filepath[1024];  // Buffer to hold the full file path

    // Open the directory
    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return 0;
    }

    // Read each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." directories
        if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Build the full path to the file
        snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);

        // Get the file stats
        if (stat(filepath, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // Add the number of blocks to the total
        total_blocks += file_stat.st_blocks;
    }

    // Each block is 512 bytes, so print the total blocks
    // printf("total %d\n", total_blocks / 2);  // Divide by 2 to get 1KB blocks (as per ls behavior)

    // Close the directory
    closedir(dir);
    return total_blocks/2;
}

char *manage_recursive_colors(char *joined_string) {

    int count = 0;
    char *s = ft_calloc(9999, 1);  // Allocate memory for the final string
    // if (s == NULL) {
    //     perror("malloc");
    //     return NULL;
    // }
    // s[0] = '\0';  // Initialize the string as empty

    // Split the joined_string by newlines into `items`
    char **items = ft_split(joined_string, '\n');
    while (items[count]) {
        count++;
    }

    if (count == 0) {
        free(items);  // Free allocated memory for empty split result
        return s;
    }

    int in_directory=0;
    char *current_dir = ft_strdup(".");
    char temp[999];
    for (int i = 0; i < count; i++) {
        char *line = items[i];
        
        // Check if it's a directory header (ends with a colon)
        if (line[strlen(line) - 1] == ':') {
            // Print directory name (skip the first directory)
            if (in_directory) {
                // printf("\n");
                ft_strcat(s, "\n");
            }
            
            // Update current directory and print header
            strncpy(current_dir, line, strlen(line) - 1);
            current_dir[strlen(line) - 1] = '\0';  // Remove the colon
            // printf("\n%s:\n", current_dir);
            char **dir = ft_split(current_dir, ' ');
            if (ft_strcmp(dir[ft_arrlen(dir)-1], ".") && ft_strcmp(dir[ft_arrlen(dir)-1], "..")) {
                ft_strcat(s, "\n./");
                ft_strcat(s, dir[ft_arrlen(dir)-1]);
                ft_strcat(s, ":\n");
                ft_strcat(s, ft_strjoin("total ", ft_itoa(get_dir_total(dir[ft_arrlen(dir)-1])), "\n"));
            }
            // ft_strcat(s, "\n");
            // printf("TOTAL --> %d\n", get_dir_total(dir[ft_arrlen(dir)-1]));

            // s = ft_strjoin("\n", current_dir, ":\n");
            
            // Reset the flag to indicate we're inside a directory
            in_directory = 1;
            continue;
        }
        
        // If it's a file, print the file information
        // if (!ft_strcmp(current_dir, ".")) {
            // printf("line %s\n", line);
            char **t = ft_split(line, ' ');
            // int j=0;
            // while (t[j] != NULL) {
            //     j++;
            // }
            const char *color = get_file_color(t[ft_arrlen(t)-1]);  // Get the color for the file/dir name
            // printf("%s%s%s%s\n", COLOR_RESET, color, line, COLOR_RESET);
            snprintf(temp, sizeof(temp), "%s%s%s%s%s", COLOR_RESET, ft_substr(line, 0, ft_strlen(line) -ft_strlen(t[ft_arrlen(t)-1])), color, t[ft_arrlen(t)-1], COLOR_RESET);

            ft_strcat(s, temp);
        // }
        // else
        //     // printf("%s\n", line);
        //     ft_strcat(s, line);
        ft_strcat(s, "\n");
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
