/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:38:25 by ael-asri          #+#    #+#             */
/*   Updated: 2024/09/09 12:47:43 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

char	*print_permissions(mode_t mode, const char *path) {

    char *s = ft_calloc(999, 1);

    s = ft_strjoin(s, (S_ISDIR(mode)) ? "d" : "-", "");
    s = ft_strjoin(s, (mode & S_IRUSR) ? "r" : "-", "");
    s = ft_strjoin(s, (mode & S_IWUSR) ? "w" : "-", "");
    s = ft_strjoin(s, (mode & S_IXUSR) ? "x" : "-", "");
    s = ft_strjoin(s, (mode & S_IRGRP) ? "r" : "-", "");
    s = ft_strjoin(s, (mode & S_IWGRP) ? "w" : "-", "");
    s = ft_strjoin(s, (mode & S_IXGRP) ? "x" : "-", "");
    s = ft_strjoin(s, (mode & S_IROTH) ? "r" : "-", "");
    s = ft_strjoin(s, (mode & S_IWOTH) ? "w" : "-", "");
    s = ft_strjoin(s, (mode & S_IXOTH) ? "x" : "-", "");
    
    if (has_acl(path))
		s = ft_strjoin(s, "x", "");
	else if (has_extended_attributes(path))
		s = ft_strjoin(s, "@", "");
	else
		s = ft_strjoin(s, " ", "");

	return s;
}

char	*print_file_info(char *filename, const struct stat *file_stat, int _hide_owner, int _hide_group_info_, const char *path) {
    
	struct stat statbuf;
    char fullpath[1024];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", ".", filename);
    
    if (stat(fullpath, &statbuf) == -1) {
        perror("stat");
        exit(1);
    }
    char *s = ft_calloc(999, 1);

    // Get file permissions
    s = ft_strjoin(s, print_permissions(file_stat->st_mode, path), " ");

    // Print number of hard links
    // printf(" %ld", file_stat->st_nlink);
	char *st_link = malloc(999);
	snprintf(st_link, 999, "%lu", file_stat->st_nlink);
    s = ft_strjoin(s, st_link, " ");

    if (_hide_owner == 1) { // Print the owner name (exclude group info)
		struct passwd *pwd = getpwuid(statbuf.st_uid);
		// printf("%s ", pwd->pw_name);
		s = ft_strjoin(s, pwd->pw_name, " ");
	}


    if (_hide_group_info_ == 1) { // Get group information
		struct group *grp = getgrgid(file_stat->st_gid);
		// printf(" %s", grp->gr_name);
		s = ft_strjoin(s, grp->gr_name, " ");
	}


    // Print file size
    // printf(" %ld", file_stat->st_size);
	char *st_size = malloc(999);
	snprintf(st_size, 999, "%ld",file_stat->st_size);
    s = ft_strjoin(s, st_size, " ");

    // Print last modification time
    char time_str[80];
    strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&(file_stat->st_mtime)));
    // printf(" %s", time_str);
    s = ft_strjoin(s, time_str, " ");
    

    // Print file name
    // printf(" %s\n", filename);
    s = ft_strjoin(s, filename, "\0");

	return s;
}



// char* generate_final_res(t_list* head, char delim) {
//     char* result = malloc(1);
//     result[0] = '\0';  // Initialize empty result string

//     while (head != NULL) {
//         struct stat file_stat;
//         lstat(head->content, &file_stat);  // Get file metadata

//         const char* color = get_file_color(head->content);  // Get color based on file type
//         char* file_info_with_color = malloc(strlen(head->content) + strlen(color) + strlen(COLOR_RESET) + 1);
        
//         // Format file name with color
//         sprintf(file_info_with_color, "%s%s%s", color, head->content, COLOR_RESET);

//         // Join the file info with the result
//         result = realloc(result, strlen(result) + strlen(file_info_with_color) + 2);  // Allocate extra space
//         strcat(result, file_info_with_color);  // Append the colored file info

//         if (head->next != NULL) {
//             // Add the delimiter between nodes
//             size_t len = strlen(result);
//             result[len] = delim;
//             result[len + 1] = '\0';
//         }

//         free(file_info_with_color);  // Free the temporary color string

//         head = head->next;  // Move to the next node
//     }

//     return result;  // Return the final result string
// }

char	*generate_final_res(t_list *head, char delim) {

    char *t = ft_calloc(ft_lstcontentsize(head), 1);

	while (head != NULL) {
        struct stat file_stat;
        lstat(head->content, &file_stat);
        
		if (head->next != NULL)
			t = ft_strchrjoin(t, head->content, delim);
			// t = print_file_info(head->content, lstat(head->content));
		else
			t = ft_strchrjoin(t, head->content, '\0');
		head = head->next;
	}

	return t;
}

char	*generate_final_lres(t_list *head, char delim, int _hide_owner, int _hide_group_info_, const char *path) {

	struct stat buff;
    char *t = ft_calloc(999, 1);

	while (head != NULL) {
        
		lstat(head->content, &buff);
		if (head->next != NULL)
			t = ft_strchrjoin(t, print_file_info(head->content, &buff, _hide_owner, _hide_group_info_, path), delim);
		else
			t = ft_strchrjoin(t, print_file_info(head->content, &buff, _hide_owner, _hide_group_info_, path), '\0');
		head = head->next;
	}

	return t;
}

// char *generate_final_Rres(t_list *head, char delim) {
//     // if (head == NULL) return NULL;

//     char *t = ft_calloc(ft_lstcontentsize(head), 1);

//     while (head != NULL) {
//         if (head->subdirectory != NULL) {
//             char *subdir_res = generate_final_Rres(head->subdirectory, delim);
//             t = ft_strchrjoin(t, ft_strjoin(head->content, ":", ""), '\n');
//             t = ft_strchrjoin(t, subdir_res, '\n');
//             free(subdir_res);
//         } else {
//             if (head->next != NULL) {
//                 t = ft_strchrjoin(t, head->content, delim);
//             } else {
//                 t = ft_strchrjoin(t, head->content, '\0');
//             }
//         }
//         head = head->next;
//     }

//     return t;
// }

char *generate_final_Rres(t_list *head, char delim) {
    if (head == NULL) return NULL;

    // Allocate memory for the result string
    char *result = ft_calloc(1, 1);  
    char *temp;

    // List all files and directories in the current directory
    t_list *current = head;
    char *t = current->content;
    while (current != NULL) {
        if (current->subdirectory == NULL || ft_strcmp(t, current->content)) {  // If it's a file or a simple directory without subdirectories
            temp = ft_strchrjoin(result, current->content, delim);
            free(result);  // Free the old result before reassigning
            result = temp;
        }
        current = current->next;
    }

    // Now process each subdirectory
    current = head;

    while (current != NULL) {
        if (current->subdirectory != NULL) {  // If it's a directory with subdirectories
            // Generate content for the subdirectory
            char *subdir_res = generate_final_Rres(current->subdirectory, delim);

            // Append the directory name and its content
            temp = ft_strjoin(current->content, ":\n", "");
            // printf("TEMPPPPPP %s\n", temp);
            result = ft_strchrjoin(result, temp, '\0');
            free(temp);
            result = ft_strchrjoin(result, subdir_res, '\0');
            free(subdir_res);
        }
        current = current->next;
    }

    return result;
}





void	remove_hiddens(t_list **head) {
	t_list* current = *head;
    t_list* prev = NULL;

    // Iterate over the linked list
    while (current != NULL) {
        if (current->content[0] == '.') {
            if (prev == NULL) {
                // This node is the head of the list
                *head = current->next;
                // free(current->content);
                free(current);
                current = *head;
            } else {
                // This node is not the head, remove it from the list
                prev->next = current->next;
                free(current->content);
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}

// void ls_R(t_list **head, char *path) {
//     struct dirent *entry;
//     struct stat statbuf;
//     DIR *dp = opendir(path);

//     if (dp == NULL) {
//         perror("opendir");
//         return;
//     }

// 	// (void)depth;
// 	insert_node(head, path);
	
//     while ((entry = readdir(dp)) != NULL) {
//         if (/*ft_strcmp(entry->d_name, ".") == 0 || */ft_strcmp(entry->d_name, "..") == 0) {
//             continue;
//         }

//         char *temp = ft_calloc(999, 1);
//         ft_strcat(temp, path);
//         ft_strcat(temp, "/");
//         ft_strcat(temp, entry->d_name);
//         char full_path[999];
//         printf("gg %d %d %s", stat(temp, &statbuf), S_ISDIR(statbuf.st_mode), temp);
//         if (stat(temp, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
//             ft_strcat(full_path, temp);

// 		insert_node(head, entry->d_name);

// 		// printf("path %s dname %s\n", path, entry->d_name);
//         // if (stat(full_path, &statbuf) == -1) {
//         //     perror("stat");
//         //     continue;
//         // }
//         // struct stat path_stat;
//         // stat(path, &path_stat);
//         // int st = stat(full_path, &statbuf);
//         // printf("stat buff %s %u\n", full_path, S_ISDIR(path_stat.st_mode));
//         // printf("%s\n", path);

//         if ((stat(full_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) || !ft_strcmp(path, ".")) {
// 			printf("wach dkholti?%s\n", full_path);
//             t_list *subdir = NULL;
//             ls_R(&subdir, full_path);

// 			t_list *current = *head;
// 			while (current->next != NULL)
// 				current = current->next;

// 			current->subdirectory = subdir;
// 			sort_list(&subdir);
//         }
//     }

//     closedir(dp);
// }

void remove_R_hiddens(t_list *head) {
    t_list *current = head;
    t_list *prev = NULL;

    while (current != NULL) {
        // First, handle the subdirectory recursively
        if (current->subdirectory != NULL) {
            remove_hiddens(&(current->subdirectory));
        }

        // Then, check if the current node should be removed
        if (current->content[0] == '.') {
            if (prev == NULL) {
                // This node is the head of the list
                head = current->next;
                free(current->content);
                free(current);
                current = head;
            } else {
                // This node is not the head, remove it from the list
                prev->next = current->next;
                free(current->content);
                free(current);
                current = prev->next;
            }
        } else {
            prev = current;
            current = current->next;
        }
    }
}




// void lssss_R(t_list **head, const char *path, int depth) {
//     DIR *dir = opendir(path);
//     if (!dir) {
//         perror("opendir");
//         return;
//     }

//     struct dirent *entry;
//     struct stat statbuf;

//     while ((entry = readdir(dir)) != NULL) {
//         if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
//             continue;
//         }

//         // Construct the full path
//         char full_path[1024];
//         snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

//         // Insert the entry into the list
//         insert_node(head, entry->d_name);

//         // Get file status to check if it's a directory
//         if (stat(full_path, &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
//             t_list *subdir_head = NULL;
//             lssss_R(&subdir_head, full_path, depth + 1);

//             // Find the last node of the current list
//             t_list *current = *head;
//             while (current->next != NULL) {
//                 current = current->next;
//             }

//             // Attach the subdirectory list to the last node
//             current->subdirectory = subdir_head;
//         }
//     }

//     closedir(dir);
// }



void print_list(t_list* node) {

    while (node) {
    printf("hola\n");
        printf("%s:\n", node->content);

        // Print all files and directories in the current directory
        t_list* content = node->subdirectory;
        while (content) {
            printf("%s\n", content->content);
            content = content->next;
        }

        // Print a newline for separation
        printf("\n");

        // Recursively print subdirectories
        content = node->subdirectory;
        while (content) {
            if (content->subdirectory) {
                print_list(content);
            }
            content = content->next;
        }

        node = node->next;
    }
}

// int is_direc`



// void ls_f(const char *path) {
//     struct dirent *entry;
//     struct stat statbuf;
//     DIR *dp = opendir(path);

//     if (dp == NULL) {
//         perror("opendir");
//         return;
//     }

//     while ((entry = readdir(dp)) != NULL) {
//         char full_path[1024];
//         snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

//         // Get file status
//         if (lstat(full_path, &statbuf) == -1) {
//             perror("stat");
//             continue;
//         }

//         // Print the entry name
//         printf("%s", entry->d_name);

//         // If it's a directory, append '/'
//         if (S_ISDIR(statbuf.st_mode)) {
//             printf("/");
//         }

//         printf("  "); // Space between entries
//     }

//     printf("\n");
//     closedir(dp);
// }

// #include <stdio.h>
// #include <sys/stat.h>
// #include <sys/types.h>
// #include <dirent.h>
// #include <pwd.h>
// #include <grp.h>
// #include <time.h>
// #include <unistd.h>
// #include <string.h>

// void print_permissions(mode_t mode) {
//     printf((S_ISDIR(mode)) ? "d" : "-");
//     printf((mode & S_IRUSR) ? "r" : "-");
//     printf((mode & S_IWUSR) ? "w" : "-");
//     printf((mode & S_IXUSR) ? "x" : "-");
//     printf((mode & S_IRGRP) ? "r" : "-");
//     printf((mode & S_IWGRP) ? "w" : "-");
//     printf((mode & S_IXGRP) ? "x" : "-");
//     printf((mode & S_IROTH) ? "r" : "-");
//     printf((mode & S_IWOTH) ? "w" : "-");
//     printf((mode & S_IXOTH) ? "x" : "-");
// }

// Function to print the file details without the owner


// Function to list directory contents in `ls -g` format
// void ls_g(const char *path) {
//     DIR *dir = opendir(path);
//     if (!dir) {
//         perror("opendir");
//         return;
//     }

//     struct dirent *entry;
//     struct stat file_stat;
//     char fullpath[1024];

//     while ((entry = readdir(dir)) != NULL) {
//         // Skip "." and ".."
//         if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
//             continue;
//         }

//         // Build the full path to the file
//         snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

//         // Get file metadata
//         if (lstat(fullpath, &file_stat) == -1) {
//             perror("lstat");
//             continue;
//         }

//         // Print file details in `ls -g` format
//         print_file_info(entry->d_name, &file_stat);
//     }

//     closedir(dir);
// }


// #define MAX_FILES 1000

// // Structure to hold file information
// typedef struct {
//     char name[256];
//     time_t access_time;
// } FileInfo;

// int compare(const void *a, const void *b) {
//     FileInfo *fileA = (FileInfo *)a;
//     FileInfo *fileB = (FileInfo *)b;
//     return (fileA->access_time - fileB->access_time);
// }

// Function to list files and sort by access time
// void ls_u(const char *path) {
//     DIR *dir;
//     struct dirent *entry;
//     struct stat file_stat;
//     FileInfo files[MAX_FILES];
//     int count = 0;

//     // Open the directory
//     dir = opendir(path);
//     if (!dir) {
//         perror("opendir");
//         return;
//     }

//     // Iterate over directory entries
//     while ((entry = readdir(dir)) != NULL) {
//         // Skip "." and ".." entries
//         if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
//             continue;
//         }

//         // Construct full path to the file
//         char full_path[512];
//         snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

//         // Get file metadata
//         if (stat(full_path, &file_stat) == -1) {
//             perror("stat");
//             continue;
//         }

//         // Store file name and access time
//         strncpy(files[count].name, entry->d_name, sizeof(files[count].name));
//         files[count].access_time = file_stat.st_atime; // Last access time
//         count++;
//     }

//     // Sort files by access time
//     qsort(files, count, sizeof(FileInfo), compare);

//     // Display sorted files
//     for (int i = 0; i < count; i++) {
//         printf("%s\n", files[i].name);
//     }

//     // Close the directory
//     closedir(dir);
// }


// void print_file_infoo(const char *path, const char *filename) {
//     struct stat statbuf;
//     char fullpath[1024];
//     snprintf(fullpath, sizeof(fullpath), "%s/%s", path, filename);
    
//     if (stat(fullpath, &statbuf) == -1) {
//         perror("stat");
//         return;
//     }

//     // Print file type and permissions
//     printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-");
//     printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
//     printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
//     printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
//     printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
//     printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
//     printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
//     printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
//     printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
//     printf((statbuf.st_mode & S_IXOTH) ? "x" : "-");
    
//     // Print the number of links
//     printf(" %ld ", statbuf.st_nlink);

//     // Print the owner name (exclude group info)
//     struct passwd *pwd = getpwuid(statbuf.st_uid);
//     printf("%s ", pwd->pw_name);

//     // Print the file size
//     printf("%ld ", statbuf.st_size);

//     // Print the last modification time
//     char timebuf[64];
//     struct tm *tm_info = localtime(&statbuf.st_mtime);
//     strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);
//     printf("%s ", timebuf);

//     // Print the file name
//     printf("%s\n", filename);
// }

// void ls_o(const char *path) {
//     DIR *dir;
//     struct dirent *entry;

//     if ((dir = opendir(path)) == NULL) {
//         perror("opendir");
//         return;
//     }

//     while ((entry = readdir(dir)) != NULL) {
//         // Skip "." and ".."
//         if (entry->d_name[0] == '.' && 
//             (entry->d_name[1] == '\0' || (entry->d_name[1] == '.' && entry->d_name[2] == '\0'))) {
//             continue;
//         }

//         // Print the file information
//         print_file_infoo(path, entry->d_name);
//     }

//     closedir(dir);
// }

char	*opts_executer(t_list **head, const char *opts, const char *path) {
    
	char *t = ft_calloc(999, 1);
    // 1- d
    // 2- R
    // 3- a
    // 4- t
    // 5- r
    // 6- l
    
	
    if (ft_strchr(opts, 'R')) { // if -R exists
        if (!ft_strchr(opts, 'a')) { // remove hidden files and dirs => anything start with a dot
            t_list *h = *head;
            remove_R_hiddens(h);
        }
        // if (ft_strchr(opts, 't')) // sort by time
        //     sort_by_time(head);
        // if (ft_strchr(opts, 'r')) // reverse the order
        //     reverse_order(head);
        
        // printf("res gen %s\n", generate_final_res(output, '\n'));
        
        if (ft_strchr(opts, 'l')) // generate a string joined by new line
            t = generate_final_Rres(*head, '\n');
        else if (!ft_strchr(opts, 'l')) // generate a string joined by space
            t = generate_final_Rres(*head, ' ');
        
        // printf("t -%s-\n", t);
    }
    else if (!ft_strchr(opts, 'R')) { // else if -R doesn't exist
        if (!ft_strchr(opts, 'a') && !ft_strchr(opts, 'f')) // remove hidden files and dirs => anything start with a dot
            remove_hiddens(head);
        
        if (!ft_strchr(opts, 'f')) // No sorting and includes hidden files
        	sort_list(head);
        
        // if (ft_strchr(opts, 'g')) // Hide the owner of the file
        //     ls_g(".");
        if (ft_strchr(opts, 't')) // sort by time
            sort_by_time(head);
        if (ft_strchr(opts, 'r')) // reverse the order
            reverse_order(head);
        if (ft_strchr(opts, 'u')) // Sort by last access time
            // ls_u(".");
            sort_by_access_time(head);

        // if (ft_strchr(opts, 'o')) // Hide the group name
        //     ls_o(".");
        
        // printf("res gen %s\n", generate_final_res(output, '\n'));
        
        if (ft_strchr(opts, 'l') || ft_strchr(opts, 'g') || ft_strchr(opts, 'o')) { // generate a string joined by new line
			int _hide_owner;
			int	_hide_group_info_;

			_hide_owner = ft_strchr(opts, 'g') ? 0 : 1; // Hide the owner of the file
			_hide_group_info_ = ft_strchr(opts, 'o') ?  0 : 1; // Hide the group name
	        
			t = generate_final_lres(*head, '\n', _hide_owner, _hide_group_info_, path);
		}
        else if (!ft_strchr(opts, 'l') && !ft_strchr(opts, 'g') && !ft_strchr(opts, 'o')) // generate a string joined by space
            t = generate_final_res(*head, ' ');
    }
    
    

	return t;
    
}