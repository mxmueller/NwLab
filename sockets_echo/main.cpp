#include <strings.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define BACKLOG 10
#define MAXLINE 4096

int
main(int argc, char **argv)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    pid_t threadid;
    char buff[MAXLINE];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(7);	/* echo server */

    bind(listenfd, (const struct sockaddr *) &servaddr, sizeof(servaddr));

    listen(listenfd, BACKLOG);

    for ( ; ; ) {
        connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);

        if ((threadid = fork()) == 0) { // hat geklappt einen fork bzw. thread zu erstellen
            close(listenfd);

            write(connfd, "ECHO LISTENING:\n", 14);

            while (1) { // Endlosschliefe
                int n=0;
                // an die Stelle n des Puffers wird
                while ((read(connfd, &buff[n], 1) > 0) && (buff[n] != '\n') && (n < MAXLINE-1))
                    n++;

                buff[n]=0;

                if (n < MAXLINE-1)
                    buff[n-1] = '\n';

                write(connfd, buff, strlen(buff));
            }
            _exit(0);
            close(connfd);
        }
        close(connfd);
        while (waitpid(-1, NULL, WNOHANG) > 0)
            ; // Clean up zombie processes
    }
}