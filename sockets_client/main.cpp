#include <strings.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>

#define MAXLINE 4096
#define BACKLOG 10


void err_quit(char *str) {
    printf("ERRORMSG: %s\n", str);
    _exit(-1);
}

int
main(int argc, char **argv)
{
	int fd;
	int n;
	struct sockaddr_in servaddr;
	char buff[MAXLINE];

	if (argc != 2) {
		printf("usage: %s <host-IP>\n",argv[0]);
		return -1;
	}

	fd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_port        = htons(13);	/* daytime server */
        if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		printf("invalid address %s\n",argv[1]);
		return -1;
	}

        if (connect(fd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		printf("unable to connect to %s\n",argv[1]);
		return -1;
	}

        while ( (n = read(fd, buff, MAXLINE)) > 0) {
                buff[n] = 0;        /* null terminate */
                printf("%s\n",buff);
	}
	close(fd);
}