#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h> // this time i had to use args for a "basic" implementation
#include <unistd.h>
#define ERR_N_DIE(x) {perror(x); exit(EXIT_FAILURE);}
#define BUFFER_SIZE 4096

void print_help(char *file_path) {
    fprintf(stderr, "Usage: %s\n"
    "-c, --bytes\t\tprint the byte counts\n"
    "-l, --lines\t\tprint the newline counts\n"
    , file_path);
    exit(-1);
}

int count_bytes(int fd, char *file) {
    int size;
    if (file != NULL) { // file as arg
        size = lseek(fd, 0, SEEK_END);
        printf("%d %s\n", size, file);
    } 

}

int count_lines(char *file) {
    return 0;
}

int main(int argc, char **argv) {
    int option, fd;
    const struct option longopts[] = {
        {"bytes", 2, 0, 0},
        {"lines", 2, 0, 0},
        {"help", 0, 0, 0},
        {NULL, 0, 0, 0} // array terminator
    };
    
    while ((option = getopt_long(argc, argv, "c:l:h", longopts, NULL)) != -1) {
        switch (option) {
            case 'c':
                if (optarg) { // argument value was given
                    fd = open(optarg, O_RDONLY);
                    if (fd < 0)
                        ERR_N_DIE(argv[0]);
                    count_bytes(fd, optarg);
                }
                break;
            case 'l':
                count_lines(optarg);
                break;
            case 'h': // display's the help page, no need to define it since it will continue to the next cas
            case '?': // invalid option
                print_help(argv[0]);
            case -1:  // done with options
                break;
            default: // unexpected input
                exit(EXIT_FAILURE);
        }
    }

    return EXIT_SUCCESS;
}