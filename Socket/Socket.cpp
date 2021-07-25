#include "Socket.hpp"

Socket::Socket(int family, int type, int port) {
	_socket = socket(family, type, 0);
	if (_socket == -1) {
		perror("error creating new socket");
		exit(1);
	}
	int opt = 1;
	if (-1 == setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		perror("setsockopt failed");
		exit(1);
	}

	bzero(&_addr, sizeof _addr);
	_addr.sin_family = family;
	_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	_addr.sin_port = htons(port);

	if (-1 == bind(_socket, (struct sockaddr*)&_addr, sizeof _addr)) {
		perror("error while binding socket to an address");
		exit(1);
	}
}

// backlog is queue
void Socket::listenSocket(int backlog) {
	if (-1 == listen(_socket, backlog)) {
		perror("listen error");
		exit(1);
	}

	while (1) {

		_connection_fd = accept(
			_socket,
			(struct sockaddr*)&_addr,
			(socklen_t*)&_addr
		);

		if (_connection_fd == -1) {
			perror("faliled connection to a socket");
			exit(1);
		}

		// write(_connection_fd, str.c_str(), str.size()); //sendResponce.send();
		close(_connection_fd);
	}
}
