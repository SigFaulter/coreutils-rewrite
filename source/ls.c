#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h> 

int check_err(int retval, char *func_name) {
    if (retval < 0) {
        perror(func_name);
        return -1;
    }
}

void list_dirs(int fd) {
    
}

int main(int argc, char **argv) {
    int fd;
    if (argc == 1) {
        fd = open(".", O_DIRECTORY|O_RDONLY);
        if (!check_err(fd, "."))
            return EXIT_FAILURE;

        list_dirs(fd);
    } else {
        for (int i = 1; i < argc; i++) {
            fd = open(".", O_DIRECTORY|O_RDONLY);
            if (!check_err(fd, "."))
                return EXIT_FAILURE;

            list_dirs(fd);
        }
    }

    return 0;
}