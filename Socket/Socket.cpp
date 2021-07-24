#include "Socket.hpp"

Socket::Socket(int family, int type, int port) {
	_socket = socket(family, type, 0);
	if (_socket == -1) {
		perror("error creating new socket");
		exit(1);
	}

	bzero(&_addr, sizeof _addr);
	_addr.sin_family = family;
	_addr.sin_addr.s_addr = htonl(0);
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
}

int Socket::acceptConnection() {
	while (1) {
		_connection = accept(_socket, (struct sockaddr*)&_addr, (socklen_t*)&_addr);
		if (_connection == -1) {
			perror("faliled connection to a socket");
			exit(1);
		}

		char buf[1024];

		int bytes_read = read(_connection, buf, sizeof buf);
		if (bytes_read == -1) {
			perror("error reading from connection");
			exit(1);
		}
		buf[bytes_read] = 0;

		std::cout << buf << " read from connection" << std::endl;
		close(_connection);
	}
}