#include <iostream>

int show_it(int fd);

int show_it(int fd) {
    char buf[BUFSIZE];

    int n;
    while ((n = read(fd, buf, BUFSIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) != n) {
            // not quite perfect
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    int fd;

    int current_path = 1;
    if (argc > 1) {
        while (current_path < argc) {
            fd = open(argv[current_path], O_RDONLY);
            if (fd < 0) {
                perror(argv[current_path]);
                return -1;
            }

            if (show_it(fd) < 0) {
                perror(argv[current_path]);
                return -1;
            }

            current_path++;
        }
    } else {
        if (show_it(STDIN_FILENO) < 0) {
            perror("stdin");
            return -1;
        }
    }

    return 0;
}
