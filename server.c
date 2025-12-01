#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BACKLOG 10

int main() {

    int status, sockfd, bindnum;
    struct addrinfo hints;
    struct addrinfo *servinfo;
    char ipstr[INET6_ADDRSTRLEN];

    // Get And Print Host Name For Client Use
    char hostname[256];

    if (gethostname(hostname, sizeof(hostname)) == -1) {
        perror("gethostname");
        exit(1);
    }

    printf("Host Name: %s\n", hostname);


    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // IP Agnostic, Not Choosing Between V4/6
    hints.ai_socktype = SOCK_STREAM; // TCP Stream Sockets
    hints.ai_flags = AI_PASSIVE; // Fill In IP
    
    // Get Personal IP
    getaddrinfo(NULL, "3490", &hints, &servinfo);

    inet_ntop(servinfo->ai_family,
          &((struct sockaddr_in*)servinfo->ai_addr)->sin_addr,
          ipstr, sizeof ipstr);
    printf("Server listening on IP: %s\n", ipstr);

    // Make A Socket From Resulting IP

    sockfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);

    if (sockfd < 0) {
        perror("Socket Error\n");
        exit(1);
    }

    printf("Socket Number: %d", sockfd);

    // Now Bind Socket To Port Passed Into GetAddrInfo
    if (bind(sockfd, servinfo->ai_addr, servinfo->ai_addrlen) < 0) {
        perror("Server Error: Bind\n");
        exit(1);
    }
    
    // Now Have Server Listen On Said Port
    if (listen(sockfd, BACKLOG) < 0) {
        perror("Server Error: Listen\n");
        exit(1);
    }


    // Now Have Server Take Requests Infinitely
    while (1) {
        // Create New Stack Variables Per Acceptance
        struct sockaddr_storage inc_addr;
        socklen_t addr_size = sizeof inc_addr;
        int acceptfd;

        // Accept Incoming Requests
        acceptfd = accept(sockfd, (struct sockaddr *)&inc_addr, &addr_size);

        char *msg = "Does This Even Work?";
        int len, bytes_sent;

        len = strlen(msg);

        // Send String Package
        bytes_sent = send(acceptfd, msg, len, 0);

        // Close Accept Socket?
    }

    // Close Socket FD ??

    freeaddrinfo(servinfo);
    return 0;

}
