#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

int socket(int domain, int type, int protocol);

int main(void) {
	struct sockaddr_in addr;
	// AF_INET - ip + port
	// SOCK_STREAM - потоковое взаимодействие
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		perror("error occured while socket creating");
		exit(1);
	}

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET; 
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(5432); 

	if (-1 == bind(sockfd, (struct sockaddr*)&addr, sizeof(addr))) {
		perror("error occured while giving network address to a socket");
		exit(1);
	}

	if (listen(sockfd, 3) == -1) {
		perror("listen error");
		exit(1);
	}

	while (1) {
		int new_socket;
		if ((new_socket = accept(sockfd, (struct sockaddr *)&addr, (socklen_t*)&addr)) == -1)
		{
			perror("In accept");            
			exit(1);        
		}

		char buffer[1024];
		int bytes_read = read(new_socket, buffer, 1024);
		if (bytes_read == 0)
			std::cout << "0 bytes read" << std::endl;

		write(new_socket, "hello", 5);
		close(new_socket);
	}
}
