#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define BUFSIZE 1024

int main(int argc, char* argv[]) {

    clock_t start = clock();

    char *buf[BUFSIZE];
    int n;

    if (argc > 1) { // erstes nicht reinschreiben !
        for (int i = 1; i < argc; i++) {
            int fd = open(argv[i], O_RDONLY);

            if (fd < 0) {
                printf("Fehler beim Öffnen der Datei %s\n", argv[i]);
                return -1;
            }

            while ((n = read(fd, buf, BUFSIZE)) > 0) {
                if (write(STDOUT_FILENO, buf, n) != n) {
                    printf("error");
                }
            }
        }

        clock_t stop = clock();
        double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
        printf("\nTime: %.5f\n", elapsed);
        return 0;

    } else {
        printf("argc !> 1 \n");
    }

    return 0;
}
