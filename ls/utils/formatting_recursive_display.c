/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_recursive_display.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:13:51 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/16 19:51:40 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

char *list_directory(const char *dir_path) {
    DIR *dir;
    struct dirent *entry;
    char *buffer = malloc(4096);  // Adjust buffer size as needed
    buffer[0] = '\0';

    if ((dir = opendir(dir_path)) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                strcat(buffer, entry->d_name);
                strcat(buffer, " ");
            }
        }
        closedir(dir);
    } 
    else {
        perror("Could not open directory");
    }

    return buffer;
}

int count_tokens(const char *str, const char *delim) {
    int count = 0;
    const char *temp = str;
    while ((temp = strstr(temp, delim)) != NULL) {
        count++;
        temp += strlen(delim);
    }
    return count + 1;
}

// Function to split string by string delimiter
char **split_string(const char *str, const char *delim) {
    int tokens_count = count_tokens(str, delim);
    char **result = malloc((tokens_count + 1) * sizeof(char *));
    const char *start = str;
    const char *end;
    int i = 0;

    while ((end = strstr(start, delim)) != NULL) {
        int len = end - start;
        result[i] = malloc(len + 1);
        strncpy(result[i], start, len);
        result[i][len] = '\0';
        i++;
        start = end + strlen(delim);
    }

    // Copy the last token
    result[i] = strdup(start);
    result[tokens_count] = NULL;  // Null-terminate the array

    return result;
}

// Function to free allocated memory for split strings
void free_split_string(char **split_array) {
    for (int i = 0; split_array[i] != NULL; i++) {
        free(split_array[i]);
    }
    free(split_array);
}

int is_directory_header(const char *line) {
    size_t len = strlen(line);
    return (len > 0 && line[len - 1] == ':');
}

// Helper function to skip '.' and '..' entries
int is_current_or_parent_directory(const char *name) {
    return (strcmp(name, "./.:") == 0 || strcmp(name, "./..:") == 0);
}

char *manage_recursive_columns(const char *joined_string) {

    char *s = ft_calloc(9999, 1);  // Duplicate the input to avoid modifying the original string

    // char *line = strtok(data, "\n");  // Start by splitting the string by newlines
    int in_directory = 0;  // Flag to track if we're inside a directory

    char **items = ft_split(joined_string, '\n');
    int i=0;
    while (items[i] != NULL) {
        // If the line is a directory header (ends with a colon)
        if (is_directory_header(items[i])) {
            // Print the directory name (skip first empty line before the first directory)
            if (in_directory) {
                // printf("\n");
                ft_strcat(s, "\n");
            }

            // Print the directory name, skipping '.' and '..' directories inside subdirectories
            if (!is_current_or_parent_directory(items[i])) {
                // printf("%s\n", items[i]);
                ft_strcat(s, items[i]);
                ft_strcat(s, "\n");
            }

            // Mark that we are inside a directory
            in_directory = 1;
        } else {
            // If it's a file entry, print it but skip '.' and '..'
            if (!is_current_or_parent_directory(items[i])) {
                // printf("%s\n", items[i]);
                ft_strcat(s, manage_columns(items[i]));
                ft_strcat(s, "\n");
            }
        }

        // Get the next line
        // line = strtok(NULL, "\n");
        i++;
    }

    // free(data);
    return s;
}
