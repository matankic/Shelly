#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void list_directory(char* path) {
    DIR* dir;
    struct dirent* entry;
    struct stat file_info;

    // Open the directory
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Loop through the entries in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Get information about the file
        char full_path[PATH_MAX];
        snprintf(full_path, PATH_MAX, "%s/%s", path, entry->d_name);
        if (lstat(full_path, &file_info) == -1) {
            perror("lstat");
            exit(EXIT_FAILURE);
        }

        // Print the file name and type
        printf("%s", entry->d_name);
        if (S_ISDIR(file_info.st_mode)) {
            printf("/");
        } else if (S_ISLNK(file_info.st_mode)) {
            printf("@");
        } else if (S_ISREG(file_info.st_mode) && (file_info.st_mode & S_IXUSR)) {
            printf("*");
        }
        printf("\n");
    }

    // Close the directory
    if (closedir(dir) == -1) {
        perror("closedir");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char** argv) {
    char* path;
    if (argc == 1) {
        // No arguments provided, use the current directory
        path = ".";
    } else {
        // Use the provided path
        path = argv[1];
    }

    list_directory(path);

    return EXIT_SUCCESS;
}
