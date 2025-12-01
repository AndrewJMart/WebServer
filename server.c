#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main() {

    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    char ipstr[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // IP Agnostic, Not Choosing Between V4/6
    hints.ai_socktype = SOCK_STREAM; // TCP Stream Sockets
    hints.ai_flags = AI_PASSIVE; // Fill In IP

    if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
        fprintf(stderr, "gai error: %s\n", gai_strerror(status));
        exit(1);
    }

    void *addr;
    void *ipver;
    struct sockaddr_in *ipv4;
    struct sockaddr_in6 *ipv6;

    // Print Info 
    if (servinfo->ai_family == AF_INET) {
        ipv4 = (struct sockaddr_in *)servinfo->ai_addr;
        addr = &(ipv4->sin_addr);
        ipver = "IPv4";
    } else {
        ipv6 = (struct sockaddr_in6 *)servinfo->ai_addr;
        addr = &(ipv6->sin6_addr);
        ipver = "IPv6";
    }

    inet_ntop(servinfo->ai_family, addr, ipstr, sizeof ipstr);
    printf("%s: %s\n", ipver, ipstr);

    freeaddrinfo(servinfo);

    return 0;

}
