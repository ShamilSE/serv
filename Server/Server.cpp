#include "Server.hpp"

Server::Server(int family, int type, int port) {
	_socket = socket(family, type, 0);
	if (_socket == -1) {
		perror("error creating new socket");
		exit(1);
	}
	// to reuse port
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

	FD_ZERO(&wfds);
	FD_ZERO(&rfds);
}

int Server::acceptConnection() {
	int fd = accept(_socket, (struct sockaddr*)&_addr, (socklen_t*)&_addr);
	if (fd == -1) {
		perror("faliled connection to a socket");
		exit(1);
	}
	const int flags = fcntl(_connection_fd, F_GETFL, 0);
	if (-1 == fcntl(_connection_fd, flags, O_NONBLOCK)) {
		perror("error.");
		exit(1);
	}
	return fd;
}

// backlog is queue
void Server::listenSocket(int backlog) {
	if (-1 == listen(_socket, backlog)) {
		perror("listen error");
		exit(1);
	}
	while (1) {
		// _connection_fd = acceptConnection();
		int max_fd = _socket;
		int fd;
		FD_SET(_socket, &rfds);

		if (-1 == (select(max_fd + 1, &rfds, NULL, NULL, NULL))) {
			perror("error.");
			exit(1);
		}
		if (FD_ISSET(_socket, &rfds)) {
			_connection_fd = accept(_socket, (sockaddr*)&_addr, (socklen_t*)&_addr);
			SmartPointer<Client> client(new Client(_connection_fd));
			_clients.push_back(client.getPointer());
			if (-1 == _connection_fd) {
				perror("error.");
				exit(1);
			}
		}
		char buf[1024];
		int bytes_read = read(_connection_fd, buf, 1024);
		buf[bytes_read] = 0;
		printf("%s\nclients_size = %lu", buf, _clients.size());
		write(_connection_fd, "HTTP<h1>hello</h1>", 14); //sendResponce.send();
		close(_connection_fd);
	}
}
