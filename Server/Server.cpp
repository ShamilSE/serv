#include "Server.hpp"

Server::Server(int family, int type, int port): port(port) {
	initServer(family);
	sock = socket(family, type, 0);
	if (sock == -1) {
		perror("sock");
		exit(1);
	}
	int opt = 1;
	if (-1 == setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
		perror("setsockopt");
		exit(1);
	}
	if (-1 == bind(sock, (struct sockaddr*)&server_addr, sizeof server_addr)) {
		perror("bind");
		exit(1);
	}
}

void Server::initServer(int family) {
	bzero(&server_addr, sizeof server_addr);
	server_addr.sin_family = family;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);
	FD_ZERO(&wfds);
	FD_ZERO(&rfds);
}

void Server::acceptConnection() {
	SmartPointer<Client> client(new Client());

	int connection_fd = accept(
		sock,
		(struct sockaddr*)&client.getPointer()->client_addr,
		(socklen_t*)&client.getPointer()->client_addr
	);
	if (connection_fd == -1) {
		perror("accept");
		exit(1);
	}
	if (-1 == fcntl(connection_fd, F_SETFL, O_NONBLOCK)) {
		perror("fcntl");
		exit(1);
	}
	client->connection_fd = connection_fd;
	std::cout << "new connection at " << client->connection_fd << std::endl;
	clients.push_back(client.getPointer());
	// FD_SET(connection_fd, &rfds);
}

void Server::lstn(int sock, int backlog) {
	if (-1 == listen(sock, backlog)) {
		perror("listen");
		exit(1);
	}
}

void Server::slct(int max_fd, fd_set *rfds, fd_set *wfds, fd_set *err, timeval *t) {
	if (-1 == (select(max_fd + 1, rfds, NULL, NULL, NULL))) {
		if (errno == EINTR)
			perror("select");
		else
			printf("signal\n");
		exit(1);
	}
}

std::string Server::receive(Client * client) {
	std::cout << "receive data" << std::endl;
	char buf[1024];

	int bytes_read = read(client->connection_fd, buf, 1024);
		std::cout << "debug" << std::endl;
	if (bytes_read > 0) {
		buf[bytes_read] = 0;
		std::string str_buf(buf, bytes_read);
		client->request = new Request(str_buf);
		return str_buf;
	}
	return NULL;
}

void Server::listenSocket(int backlog) {
	lstn(sock, backlog);
	FD_SET(sock, &rfds);
	while (1) {
		int max_fd = sock;

		slct(max_fd + 1, &rfds, NULL, NULL, NULL);
		if (FD_ISSET(sock, &rfds)) {
			std::cout << "accept connection" << std::endl;
			acceptConnection();
		}

		// for (size_t index = 0; index < clients.size(); index++) {
		// 	if (FD_ISSET(sock, &rfds))
		// 		receive(clients[index]);
		// }
	}
}
