
#include "ls.h"

void    ls(int flag) {
    DIR *dir = opendir(".");
    struct dirent *file;
    // dir = ;
    if (dir) {
        while ((file = readdir(dir)))
            if (file->d_name[0] == '.')
                flag && printf("%s ", file->d_name);
            else
                printf("%s ", file->d_name);
        // closedir(dir);
    free(file);
    }
    free(dir);
}

void    ls_l(int flag) {
    DIR *dir = opendir(".");
    struct dirent *file;
    // dir ;
    if (dir) {
        while ((file = readdir(dir)))
            if (file->d_name[0] == '.')
                flag && printf("%s\n", file->d_name);
            else
                printf("%s\n", file->d_name);
        // closedir(dir);
    free(file);
    }
    free(dir);
}

int is_directory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0) {
        return 0;
    }
    return S_ISDIR(statbuf.st_mode);
}

void ls_R() {
    struct dirent *entry;
    DIR *dp = opendir(".");

    if (dp == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        if (entry->d_type == DT_DIR) {
            // Skip the "." and ".." directories
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            // Build the path to the directory entry
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", ".", entry->d_name);

            if (is_directory(full_path)) {
                printf("%s\n", full_path);
            }
        }
    }

    closedir(dp);
}


int main(int ac, char **av) {

    if (ac == 1) {
        ls(0);
    }
    else if (ac == 2) {
        if ((ft_strlen(av[1]) >= 1 && ft_strlen(av[1]) <= 3) && av[1][0] == '-' && (av[1][1] == 'l' || av[1][1] == 'r' || av[1][1] == 'a' || av[1][1] == 't' || av[1][1] == 'R')) {
            if (av[1][1] == 'l')
                if (ft_strlen(av[1]) == 3 && av[1][2] == 'a')
                    ls_l(1);
                else
                    ls_l(0);
            else if (av[1][1] == 'a')
                ls(1);
            else if (av[1][1] == 'R')
                ls_R();
            else
                printf("%s", av[1]);
        }
        else
            printf("invalid flag");
    }
    else {
        printf("invalid format");
    }
    return (0);
}