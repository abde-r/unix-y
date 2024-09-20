/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_display.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 12:49:56 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/20 09:53:26 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

// Function to get the terminal width
int get_terminal_width() {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("ioctl");
        return 80;  // Default to 80 columns if terminal size cannot be determined
    }
    return w.ws_col;
}

// Function to calculate the maximum item length for formatting columns
size_t calculate_max_len(char **items, int count) {
    size_t max_len = 0;
    for (int i = 0; i < count; i++) {
        size_t len = ft_strlen(items[i]);
		// printf("s -%s- len %zu max len %zu\n", items[i], ft_strlen(items[i]), max_len);
        if (len > max_len) {
            max_len = len;
        }
    }
    return max_len;
}

// Function to print the items in a columnar format
char *print_in_columns(char **items, int count, int max_len) {
    int term_width = get_terminal_width();  // Get terminal width
    int num_columns = term_width / (max_len + 2);  // Max length + 2 for padding
    if (num_columns == 0) num_columns = 1;  // Ensure at least one column

    int num_rows = (count + num_columns - 1) / num_columns;

    // Estimate the maximum size needed for the string `s`
    int estimated_size = (max_len + 2 + 10) * count + num_rows;  // Rough estimate of total size (including color codes)
    char *s = malloc(estimated_size);
    if (s == NULL) {
        perror("malloc");
        return NULL;
    }
    s[0] = '\0';  // Initialize the string as empty

    // Print the items row by row and store the output in `s`
    char temp[1024];  // Temporary buffer to hold formatted strings
    for (int row = 0; row < num_rows; row++) {
        for (int col = 0; col < num_columns; col++) {
            int index = row + col * num_rows;
            if (index < count) {
                const char *color = get_file_color(items[index]);  // Get the color for the file
                snprintf(temp, sizeof(temp), "%s%-*s%s", color, max_len + 2, items[index], COLOR_RESET);  // Format the item with color
                strcat(s, temp);  // Append the formatted item to `s`
            }
        }
        strcat(s, "\n");  // Append a newline at the end of each row
    }
    
    // printf("ha li mchaaa %s\n", s);
    return s;  // Return the final string
}

// Function to manage columns
char	*manage_columns(char *joined_string) {
    int count=0;
    
    char **items = ft_split(joined_string, ' ');
	while (items[count]) {
		count++;
    }
    if (count == 0)
        return "";

    int max_len = calculate_max_len(items, count);  // Calculate the max length of items
    char	*s = print_in_columns(items, count, max_len);  // Print the items in columns

    // Free allocated memory
    for (int i = 0; i < count; i++) {
        free(items[i]);
    }
    free(items);

	return s;
}
