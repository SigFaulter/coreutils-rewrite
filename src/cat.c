#include <stdio.h> // printf() fprintf()
#include <stdlib.h> // exit() malloc() free()
#include <errno.h>  // perror()
#include <unistd.h> // lseek() 
#include <string.h> // strerror()
#include <sys/stat.h> 
#include <sys/ioctl.h>
#include <fcntl.h>
#define BUFFER_SIZE 1 // maximum page file size (for optimisation)


int check_read_err(int retval) {
	if (retval == -1) { 
		perror("read()");
		return -1;
	}
}

int check_alloc(char *buff)  {
	if (buff == NULL) {
		fprintf(stderr, "Error: Could not allocate memory\n");
		return -1;
	}
}

void read_from_file(int fd) {
	char *buffer;

	int file_size = lseek(fd, 0, SEEK_END); // get the file size
	lseek(fd, 0, 0); // set back the cursor to the beginning (a.k.a rewind())

	// no need to flush the buffer, we will set the null byte accordingly
	buffer = malloc(file_size  + 1);

	while (1) {
		if (!check_alloc(buffer))
			break;	
		buffer[file_size + 1] = '\0';
		write(1, buffer, file_size);
		break;
	}

	close(fd);
	free(buffer);
}

void read_from_stdin() {
	char *buffer;
	int number_of_bytes;
	int total_size;
	int current_char;

	buffer = malloc(BUFFER_SIZE);
	number_of_bytes = read(0, buffer, BUFFER_SIZE);

	total_size = BUFFER_SIZE;
	while (1) {
		if (!check_read_err(number_of_bytes)) {
			exit(-1);
		}
		// we got to the EOF, print the input out	
		if (number_of_bytes == 0 || number_of_bytes < total_size) { 
			write(1, buffer, BUFFER_SIZE);
			break;
		} else { // reallocate and re-read again
			do {
				total_size = total_size * 2;
				if (!realloc(buffer, total_size)) {
					perror("realloc()");
					break;
				}
				number_of_bytes = read(0, buffer, total_size);
				if (!check_read_err(number_of_bytes)) {
					exit(-1);
				}
			} while (number_of_bytes < total_size);
		}
		write(1, buffer, total_size);
		break;
	}

	free(buffer);
}

int main(int argc, char **argv) {
	int fd; // fd to be used while opening the file

	if (argc == 1) {
		// intentional infinte loop, default behavior of GNU cat
		while (1) {
			read_from_stdin();
		}
	} else {
		for (int i = 1; i < argc; i++) {
			fd = open(argv[i], O_RDONLY);
			if (fd < 0) {
				fprintf(stderr, "%s: %s: %s\n", argv[0], argv[i], strerror(errno));
				continue;
			}
			read_from_file(fd);
		}
	}
	return 0;
}
