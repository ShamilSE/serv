#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

int socket(int domain, int type, int protocol);

int main(void) {
	sockaddr s_addr;
	// AF_INET - ip + port
	// SOCK_STREAM - потоковое взаимодействие
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		perror("error occured while socket creating");
	if (-1 == bind(sockfd, &s_addr, sizeof(s_addr))) // did I give a size correctly?
		perror("error occured while giving network address to a socket");
	
}
