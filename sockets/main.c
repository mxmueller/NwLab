#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void validIpAdress(char *arg) {
    // ! Set ip in Runner
    struct sockaddr_in sa; // IPv4
    struct sockaddr_in6 sa6; // IPv6

    if (inet_pton(AF_INET, arg, &(sa.sin_addr)) > 0) {
        char ip4[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);
        printf("IPv4: %s\n", ip4);
    } else if (inet_pton(AF_INET6, arg, &(sa6.sin6_addr)) > 0) {
        char ip6[INET_ADDRSTRLEN];
        inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);
        printf("IPv6: %s\n", ip6);
    } else {
        printf("Invalid IP address!");
    }
};

void getdns(char *arg) {
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    if (arg != 2) {
        fprintf(stderr, "usage: showip hostname\n");
    }

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // AF_INET or AF_INET6 to force version
    hints.ai_socktype = SOCK_STREAM; // TCP

    if ((status = getaddrinfo(arg, NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
    }

    printf("IP addresses for %s: \n\n", arg);

    for (p = res; p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;

        // get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *) p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *) p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
        // convert the IP to a string and print it:
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf(" %s: %s\n", ipver, ipstr);
    }

    freeaddrinfo(res); // free the linked list
}


int main(int argc, char *argv[]) {
    // validIpAdress(argv[1]);
    getdns(argv[1]);
}