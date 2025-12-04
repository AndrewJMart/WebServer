#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>

#include "httpthread.h"

#define MAX_BUFFER_LIMIT 1000

void *handle_request(void  *arg) {
	// Cast Acceptfd Back To Int
	int acceptfd = *((int *)arg);

	// Set Initial Buffer Limit
	char receive_buffer[MAX_BUFFER_LIMIT];

	// Receive Client Info
	recv(acceptfd, receive_buffer, sizeof receive_buffer, 0);

	printf("String Received %s", receive_buffer);

	close(acceptfd);

	return NULL;

}
