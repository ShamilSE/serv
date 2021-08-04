#include "Server/Server.hpp"
#include "Main/Main.hpp"
#include "Server/Server.hpp"

Main* mainClass = Main::Instance();

void checkArgs(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "webserv: usage: " << "./webserv " << "[path_to_configuration]" << std::endl;
		exit(1);
	}
}

void _setFDSet(Server& server) {
	FD_SET(server.getSock(), &mainClass->rfds);
	for (size_t ii = 0; ii < server.clients.size(); ii++) {
		FD_SET(server.clients[ii]->fd, &mainClass->wfds);
		FD_SET(server.clients[ii]->fd, &mainClass->rfds);
		if (server.clients[ii]->fd > mainClass->max_fd)
			mainClass->max_fd = server.clients[ii]->fd;
	}
}

void _slct(int max_fd, fd_set *rfds, fd_set *wfds, fd_set *err, timeval *t) {
	if (-1 == (select(mainClass->max_fd + 1, rfds, wfds, err, t))) {
		if (errno != EINTR) {
			perror("select");
			exit(1);
		}
		else
			printf("signal");
	}
}

void _acceptConnection(Server& server) {
	Client* client = new Client();
	socklen_t client_len = sizeof(client->addr);
	int connection_fd = accept(
		server.getSock(),
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
	server.clients.push_back(client);
}

void _receive(Client* client) {
	char buf[1024];

	int bytes_read = read(client->fd, buf, 1024);
	if (bytes_read > 0) {
		buf[bytes_read] = 0;
		std::string str_buf(buf, bytes_read);
		client->request = new Request(str_buf);
		client->request->client_fd = client->fd;
		client->response = new Response(client->request);
		client->isWaitingForResponse = 1;
	}
	std::cout << "read() returned " << bytes_read << std::endl;
	if (bytes_read == 0) {
		close(client->fd);
		for (size_t i = 0; i < mainClass->servers.size(); i++) {
			for (size_t ii = 0; ii < mainClass->servers[i].clients.size(); ii++) {
				if (client == mainClass->servers[i].clients[ii]) {
					delete *(mainClass->servers[i].clients.begin() + ii);
					mainClass->servers[i].clients.erase(mainClass->servers[i].clients.begin() + ii);
					FD_ZERO(&mainClass->wfds);
					std::cout << "client " << *client << " disconnected" << std::endl;
					return;
				}
			}
		}
	}
}

void _send(Client* client) {
	mainClass->routing(*client->request, *client->response);
	client->isWaitingForResponse = 0;
	// delete client->request;
	// delete client->response;
}

int main(int argc, char** argv, char** env) {
	checkArgs(argc, argv);

	mainClass->servers = mainClass->getConfiguredServers("conf/webserv2.conf");
	
	mainClass->max_fd = mainClass->servers[mainClass->servers.size() - 1].getSock();
	while (1) {
		FD_ZERO(&mainClass->wfds);
		FD_ZERO(&mainClass->rfds);
		for (size_t index = 0; index < mainClass->servers.size(); index++) {
			_setFDSet(mainClass->servers[index]);
		}

		_slct(mainClass->max_fd + 1, &mainClass->rfds, nullptr, nullptr, nullptr);

		for (size_t index = 0; index < mainClass->servers.size(); index++) {
			if (FD_ISSET(mainClass->servers[index].getSock(), &mainClass->rfds))
				_acceptConnection(mainClass->servers[index]);
		}

		for (size_t i = 0; i < mainClass->servers.size(); i++) {
			for (size_t ii = 0; ii < mainClass->servers[i].clients.size(); ii++) {
				if (FD_ISSET(mainClass->servers[i].clients[ii]->fd, &mainClass->rfds)) {
					_receive(mainClass->servers[i].clients[ii]);
				}
				if (mainClass->servers[i].clients[ii]->isWaitingForResponse &&
					mainClass->servers[i].clients[ii]->request != nullptr && FD_ISSET(mainClass->servers[i].clients[ii]->fd, &mainClass->wfds)) {
					_send(mainClass->servers[i].clients[ii]);
				}
			}
		}
	}
	return 0;
}
