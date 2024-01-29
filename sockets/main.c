#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>

int main() {
    const char *hostname = "localhost";
    const char *port = "8080";

    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; // Wir wollen IPv4-Adressen
    hints.ai_socktype = SOCK_STREAM; // Wir wollen einen Stream-Socket

    int status = getaddrinfo(hostname, port, &hints, &res);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        return 1;
    }

    struct addrinfo *addr_info = res;
    struct sockaddr *addr = addr_info->ai_addr;
    struct sockaddr_in *addr_in = (struct sockaddr_in *)addr;

    printf("IP-Adresse: %s\n", inet_ntoa(addr_in->sin_addr));
    printf("Port: %d\n", ntohs(addr_in->sin_port));

    freeaddrinfo(res);

    return 0;
}