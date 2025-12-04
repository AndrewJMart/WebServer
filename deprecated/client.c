#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {

    struct addrinfo hints, *res, *p;
    int sockfd;

    if (argc != 3) {
        fprintf(stderr, "Usage: Client Hostname Port");
        exit(1);
    }

    // Set Up Hints For GetAddrInfo
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(argv[1], argv[2], &hints, &res) < 0) {
       perror("getaddrinfo");
       exit(1);
    }

    // Loop Through And Attempt To Connect To IPs
    for (p = res; p != NULL; p = p->ai_next) {
        // Process Current Address
        int connect_status;

        // 1 - Create Socket
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (sockfd < 0) {
            perror("Socket");
            continue;
        }
        
        // 2 - Connect To Socket
        connect_status = connect(sockfd, p->ai_addr, p->ai_addrlen);
        if (connect_status < 0) {
            perror("Connect");

            // No Longer Need Socket
            close(sockfd);
            continue;
        }

        // Once Connected, We Can Break As Connection Established
        break;
    }

    // Check If Connection Formed
    if (p == NULL) {
        perror("Failed To Connect");
        exit(1);
    }
    
    char *send_message_back = "Sent Message Back";
    // Send Message Back To Server
    send(sockfd, send_message_back, strlen(send_message_back), 0);

    close(sockfd);

    return 0;
}
