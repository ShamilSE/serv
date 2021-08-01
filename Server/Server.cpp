#include "Server.hpp"

Server::Server(void(*callback)(Request&, Response&)) {
	this->callback = callback;
}

void Server::_getServerAddr(int port) {
	this->port = port;
	bzero(&server_addr, sizeof server_addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);

	fcntl(sock, F_SETFL, O_NONBLOCK);
}

void Server::_createSocket() {
	sock = socket(AF_INET, SOCK_STREAM, 0);
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

void Server::_acceptConnection() {
	Client* client = new Client();
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

	std::cout << "incoming connection from " << *client << std::endl;
	client->fd = connection_fd;
	clients.push_back(client);
}

void Server::_lstn(int sock) {
	if (-1 == ::listen(sock, 3)) {
		perror("listen");
		exit(1);
	}
	std::cout << "server is listening for " << port << " port" << std::endl;
}

void Server::_slct(int max_fd, fd_set *rfds, fd_set *wfds, fd_set *err, timeval *t) {
	if (-1 == (select(max_fd + 1, rfds, wfds, err, t))) {
		if (errno != EINTR) {
			perror("select");
			exit(1);
		}
		else
			printf("signal");
	}
}

void Server::_setFDSet() {
	max_fd = sock;
	FD_ZERO(&wfds);
	FD_ZERO(&rfds);
	FD_SET(sock, &rfds);
	for (size_t index = 0; index < clients.size(); index++) {
		FD_SET(clients[index]->fd, &wfds);
		FD_SET(clients[index]->fd, &rfds);
		if (clients[index]->fd > max_fd)
			max_fd = clients[index]->fd;
	}
}

void Server::_receive(Client* client) {
	char buf[1024];

	int bytes_read = read(client->fd, buf, 1024);
	if (bytes_read > 0) {
		buf[bytes_read] = 0;
		std::string str_buf(buf, bytes_read);
		client->request = new Request(str_buf);
		client->request->client_fd = client->fd;
		client->response = new Response(client->request);
	}
	std::cout << "read() returned " << bytes_read << std::endl;
	if (bytes_read == 0) {
		close(client->fd);
		for (size_t index = 0; index < clients.size(); index++) {
			if (client == clients[index]) {
				clients.erase(clients.begin() + index);
				FD_ZERO(&wfds);
				std::cout << "client " << *client << " disconnected" << std::endl;
				return;
			}
		}
	}
}

void Server::_send(Client* client) {
	Response response(client->request);

	callback(*client->request, *client->response);
}

void Server::listen(int port) {
	_getServerAddr(port);
	_createSocket();
	_lstn(sock);
	
	while (1) {
		_setFDSet();
		_slct(max_fd + 1, &rfds, nullptr, nullptr, nullptr);
		if (clients.size())
			_slct(max_fd + 1, nullptr, &wfds, nullptr, nullptr);
		if (FD_ISSET(sock, &rfds)) {
			_acceptConnection();
		}

		for (size_t index = 0; index < clients.size(); index++) {
			if (FD_ISSET(clients[index]->fd, &rfds)) {
				_receive(clients[index]);
			}
			if (clients[index]->request != nullptr && FD_ISSET(clients[index]->fd, &wfds)) {
				_send(clients[index]);
			}
		}
	} // while
}
