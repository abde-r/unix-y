/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 17:45:32 by ael-asri          #+#    #+#             */
/*   Updated: 2024/08/29 16:39:20 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

// int comp(const void* a, const void* b) 
// {
//     return strcmp(*(const char**)b, *(const char**)a); 
// }

// size_t arr_length(char** arr) {
//     size_t i=0;
//     while (arr[i] != NULL)
//         ;
//     return i;
// }

// void    ls_r() {
//     char    *arr[9];
//     DIR *dir = opendir(".");
//     struct dirent *file;
//     int count=0;
//     // dir = ;
//     if (dir) {
//         while ((file = readdir(dir))) {
//             // if (file->d_name[0] == '.')
//             //     arr[count++] = strdup(file->d_name);
//             //     // flag && printf("%s ", file->d_name);
//             // else
//                 arr[count++] = strdup(file->d_name);
//                 // count++;
//                 // printf("%s ", file->d_name);
//         }
//         // closedir(dir);
//         // qsort(arr, sizeof(arr)/sizeof(arr[0]), sizeof(char), comp);
//         qsort(arr, sizeof(arr)/sizeof(arr[0]), sizeof(const char*), comp);
//         for (size_t i=0; i<9; i++)
//             printf("%s ", arr[i]);
//         printf("\n");
//     free(file);
//     }
//     free(dir);
// }





// void    ls_l(int flag) {
//     DIR *dir = opendir(".");
//     struct dirent *file;
//     // dir ;
//     if (dir) {
//         while ((file = readdir(dir)))
//             if (file->d_name[0] == '.')
//                 flag && printf("%s\n", file->d_name);
//             else
//                 printf("%s\n", file->d_name);
//         // closedir(dir);
//     free(file);
//     }
//     free(dir);
// }

// void    ls_R(t_list **output, char *path) {

//     struct dirent *entry;
//     DIR *dp = opendir(path);
//     if (dp == NULL) {
//         perror("opendir");
//         return ;
//     }

//     printf("%s: \n", path);
    
//     while ((entry = readdir(dp)) != NULL) {
//         if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
//             continue;
//         printf("%s ", entry->d_name);
//     }
//     printf("\n\n");
//     rewinddir(dp);

//     while ((entry = readdir(dp)) != NULL) {
//         if (ft_strcmp(entry->d_name, ".") == 0 || ft_strcmp(entry->d_name, "..") == 0)
//             continue;
        
//         char full_path[1024];
//         snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        
//         if (is_directory(full_path))
//             ls_R(output, full_path);
//         // printf("%s ", entry->d_name);
//     }
    
//     closedir(dp);
// }



// #define MAX_KEYS 100 // Maximum number of keys in the map 
 
// typedef struct { 
//     char* key; 
//     char* value; 
// } KeyValuePair; 
 
// typedef struct { 
//     KeyValuePair* pairs[MAX_KEYS]; 
//     int num_pairs;
// } Map; 
 
// void add_to_map(Map* map, char* key, char* value) { 
//     if (map->num_pairs >= MAX_KEYS) { 
//         printf("Error: map is full\n"); 
//         exit(1); 
//     } 
//     KeyValuePair* pair = malloc(sizeof(KeyValuePair)); 
//     pair->key = key; 
//     pair->value = value; 
//     map->pairs[map->num_pairs] = pair; 
//     map->num_pairs++; 
// }

// void    print_map(Map* map) { 
//     for (int i = 0; i < map->num_pairs; i++) {
//         printf("%s ", map->pairs[i]->key);
//     }
//     printf("\n");
// } 

// int compare(const void *a, const void *b) {
//     KeyValuePair *pairA = *(KeyValuePair **)a;
//     KeyValuePair *pairB = *(KeyValuePair **)b;
//     return strcmp(pairB->value, pairA->value);
// }

// void    ls_t(char *path) {
//     // char map[999][999];
//     Map map = {};
//     DIR *dir = opendir(".");
//     struct dirent *file;
//     struct stat buff;
//     // dir = ;
//     (void)path;

//     if (dir) {
//         while ((file = readdir(dir))) {
//             // printf("%s ", file->d_name);
//             int stat = lstat(file->d_name, &buff);
//             (void)stat;
//             char **t = ft_split(ctime(&buff.st_mtime), ' ');
//             // printf("haana %s\n", ft_strjoin(ft_substr(t[4], 0, ft_strlen(t[4])-1), t[2], t[3]));
//             char *correct_datetime_format = ft_strjoin(ft_substr(t[4], 0, ft_strlen(t[4])-1), t[2], t[3]);
//             add_to_map(&map, file->d_name, correct_datetime_format);
//             // map[file->d_name] = ctime(&buff.st_mtime);
//             // printf("lstat %s %d %s\n", path, stat, ctime(&buff.st_mtime));
//         }
//         // closedir(dir);

//         // printf("apple: %s\n", get_from_map(&map, "main.c"));
//         // print_map(&map);
//         qsort(map.pairs, map.num_pairs, sizeof(KeyValuePair*), compare);
//         // printf("---\n");
//         print_map(&map);

//     free(file);
//     }
//     free(dir);
    
// }












int main(int ac, char **av) {

    (void)ac;
    t_list  *output = 0;
    char *opts;
    
    // parse & error checking
    opts = opts_parser(av);
	
    if (ft_strchr(opts, 'R')) // if -R exists, execute ls with -R flag
        ls_R(&output, ".", 0);
    else if (!ft_strchr(opts, 'R')) // else if -R doesn't exist, execute default ls
        ls(&output, ".");
    
	// execute other options
    char *final_res = opts_executer(output, opts);

    // Print the final result
    printf("%s", final_res);
	
    // while (output != NULL)
	// {
    //     printf("linked list: %s\n", output->content);
	// 	output = output->next;
	// }

    
    
    // if (ac == 1) {
    //     ls(0);
    // }
    // else if (ac == 2) {
        // if ((ft_strlen(av[1]) >= 1 && ft_strlen(av[1]) <= 3) && av[1][0] == '-' && (av[1][1] == 'l' || av[1][1] == 'r' || av[1][1] == 'a' || av[1][1] == 't' || av[1][1] == 'R')) {
            
        // }
    //     else
    //         printf("invalid flag");
    // }
    // else {
    //     printf("invalid format");
    // }
    
    
    
    return (0);
}