#include "Server.hpp"

Server::Server(int family, int type, int port): port(port) {
	initServer(family);
	std::cout << "creating new socket..." << std::endl;
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
	std::cout << "bind socket..." << std::endl;
	if (-1 == bind(sock, (struct sockaddr*)&server_addr, sizeof server_addr)) {
		perror("bind");
		exit(1);
	}
	std::cout << "waiting for connection at port " << port << "..." << std::endl;
}

void Server::initServer(int family) {
	bzero(&server_addr, sizeof server_addr);
	server_addr.sin_family = family;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);
	FD_ZERO(&wfds);
	FD_ZERO(&rfds);
	/* Set nonblock for stdin. */
	int flag = fcntl(sock, F_GETFL, 0);
	flag |= O_NONBLOCK;
	fcntl(sock, F_SETFL, flag);
	max_fd = 0;
}

void Server::acceptConnection() {
	SmartPointer<Client> client(new Client());

	socklen_t client_len = sizeof(client->addr);
	int connection_fd = accept(
		sock,
		(struct sockaddr*)&client->addr,
		&client_len
	);
	if (connection_fd == -1) {
		perror("accept");
		exit(1);
	}
	fcntl(connection_fd, F_SETFL, O_NONBLOCK);
	// if (connection_fd > max_fd)
	// 	max_fd = connection_fd;

	client->log(); // info about new client

	client->connection_fd = connection_fd;
	clients.push_back(client.getPointer());
}

void Server::lstn(int sock, int backlog) {
	if (-1 == listen(sock, backlog)) {
		perror("listen");
		exit(1);
	}
}

void Server::slct(int max_fd, fd_set *rfds, fd_set *wfds, fd_set *err, timeval *t) {
	if (-1 == (select(max_fd + 1, rfds, wfds, NULL, NULL))) {
		if (errno == EINTR) {
			perror("select");
			exit(1);
		}
		else
			printf("signal");
	}
}

void Server::receive(Client * client) {
	char buf[1024];

	int bytes_read = read(client->connection_fd, buf, 1024);
	if (bytes_read > 0) {
		buf[bytes_read] = 0;
		std::string str_buf(buf, bytes_read);
		client->request = new Request(str_buf);
		std::cout << "received " << bytes_read << " from client" << std::endl;
		return;
	}
	// close connection if client closed connection (bytes_read == 0)
	closeConnection(client);
}

void Server::send(Client* client) {
	Response response(client->request);

	response.send(client->connection_fd);
}

void Server::closeConnection(Client* client) {
	FD_CLR(client->connection_fd, &wfds);
	FD_CLR(client->connection_fd, &rfds);
	close(client->connection_fd);
	// remove client from vector
	// max_fd--;
}

void Server::listenSocket(int backlog) {
	lstn(sock, backlog);
	FD_SET(sock, &rfds);
	max_fd = sock;
	while (1) {
		for (size_t index = 0; index < clients.size(); index++) {
			FD_SET(clients[index]->connection_fd, &wfds);
			FD_SET(clients[index]->connection_fd, &rfds);
			if (clients[index]->connection_fd > max_fd)
				max_fd = clients[index]->connection_fd;
		}

		slct(max_fd + 1, &rfds, NULL, NULL, NULL);
		if (FD_ISSET(sock, &rfds)) {
			acceptConnection();
		}

		for (size_t index = 0; index < clients.size(); index++) {
			if (FD_ISSET(clients[index]->connection_fd, &rfds)) {
				receive(clients[index]);
			}
			if (FD_ISSET(clients[index]->connection_fd, &wfds)) {
				std::cout << "client is ready to receive info" << std::endl;
				send(clients[index]);
				// closeConnection(clients[index]);
			}
		}
	}
}
