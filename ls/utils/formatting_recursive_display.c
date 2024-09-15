/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_recursive_display.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:13:51 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/15 10:39:10 by ael-asri         ###   ########.fr       */
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

char *manage_recursive_columns(char *joined_string, char *path) {

    // printf("ha li wsal ---%s---\n", joined_string);
    int count = 0;
    (void)path;
    char **items = ft_split(joined_string, ' '); // Assuming this splits the input
    while (items[count]) {
        count++;
    }
    if (count == 0)
        return "";

    // printf("----joined string %s----\n", joined_string);
    int max_len = calculate_max_len(items, count);  // Calculate max length of items
    char *s = print_in_columns(items, count, max_len);  // Print the items in columns

    // Handle subdirectories
    for (int i = 0; i < count; i++) {
        if (is_directory(items[i])) {  // Check if the item is a directory
            // printf("\n%s:\n", items[i]);  // Print the directory name
            char *subdir_items = list_directory(items[i]);  // List the subdir contents
            manage_recursive_columns(subdir_items, path);  // Recursive call to handle subdir items
            free(subdir_items);  // Clean up after listing the subdirectory
        }
    }

    // Free allocated memory
    for (int i = 0; i < count; i++) {
        free(items[i]);
    }
    free(items);

    // printf("wa s %s\n", s);
    return s;
}
