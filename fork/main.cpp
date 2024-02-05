#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[]) {
    int i;
    pid_t pid;
    int status;
    int maxprocs = 500; // https://apple.stackexchange.com/questions/373063/why-is-macos-limited-to-1064-or-2088-processes#:~:text=In%20macOS%2C%20the%20system%20is,Why%20is%20there%20a%20limit%3F
    int procs;

    for (procs = 0; procs < maxprocs; procs++) {
        if ((pid = fork()) < 0) {
            printf("Fehler beim Forken\n");
            return 0;
        }
        if (pid == 0) {

            pid = getpid();

            for (i = 0; i < 5; i++) {
                printf("Kind im Schleifendurchlauf Nummer %d\n", i);
                sleep(pid % 10);
            }
            printf("Ende des Kindprozesses\n");
            return 0;
        }
    }

    while (waitpid(-1, &status, 0) > 0);
    printf("Elternprozess abgeschlossen\n");
    return 0;
}