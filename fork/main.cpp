#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int i;
    pid_t pid;
    int status;
    int maxprocs = 500;
    int procs;

    for (procs = 0; procs < maxprocs; procs++) {
        if ((pid = fork()) < 0) {
            printf("Fehler beim Forken\n");
            return 0;
        }
        if (pid == 0) {
            srand((unsigned int)time(NULL) ^ getpid());
            for (i = 0; i < 5; i++) {
                printf("Kind im Schleifendurchlauf Nummer %d\n", i);
                sleep(1 + rand() % 5);
            }
            printf("Ende des Kindprozesses\n");
            return 0;
        }
    }

    while (waitpid(-1, &status, 0) > 0);
    printf("Elternprozess abgeschlossen\n");
    return 0;
}