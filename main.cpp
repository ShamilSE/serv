#include "Server/Server.hpp"
#include "CGI/CGI.hpp"
#include "webserv.hpp"

void routing(Request& request, Response& response) {
	response.setStatus("200 OK");
	if (request.path == "/")
		response.send("pages/index.html");
	else if (request.path == "/form")
		response.send("pages/form.html");
	else {
		response.setStatus("404 Not Found");
		response.send("pages/404.html");
	}
}


std::vector<Server> getConfiguredServers(std::string);
std::vector<Server> servers = getConfiguredServers("conf/webserv2.conf");

void checkArgs(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "webserv: usage: " << "./webserv " << "[path_to_configuration]" << std::endl;
		exit(1);
	}
}

fd_set wfds, rfds;
int max_fd = 0;

void _setFDSet(Server& server) {
	FD_SET(server.getSock(), &rfds);
	for (size_t ii = 0; ii < server.clients.size(); ii++) {
		FD_SET(server.clients[ii]->fd, &wfds);
		FD_SET(server.clients[ii]->fd, &rfds);
		if (server.clients[ii]->fd > max_fd)
			max_fd = server.clients[ii]->fd;
	}
}

void _slct(int max_fd, fd_set *rfds, fd_set *wfds, fd_set *err, timeval *t) {
	if (-1 == (select(max_fd + 1, rfds, wfds, err, t))) {
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
	}
	std::cout << "read() returned " << bytes_read << std::endl;
	if (bytes_read == 0) {
		close(client->fd);
		for (size_t i = 0; i < servers.size(); i++) {
			for (size_t ii = 0; ii < servers[i].clients.size(); ii++) {
				if (client == servers[i].clients[ii]) {
					delete *(servers[i].clients.begin() + ii);
					servers[i].clients.erase(servers[i].clients.begin() + ii);
					FD_ZERO(&wfds);
					std::cout << "client " << *client << " disconnected" << std::endl;
					return;
				}
			}
		}
	}
}

void _send(Client* client) {
	routing(*client->request, *client->response);
	// delete client->request;
	// delete client->response;
}

std::vector<Server> getConfiguredServers(std::string config) {
	std::vector<std::string> configurations = parseConfig(config);
	std::vector<Server> servers;
	servers.reserve(configurations.size());

	for (size_t index = 0; index < configurations.size(); index++) {
		Server server(routing, configurations[index]);
		servers.push_back(server);
	}
	return servers;
}

int main(int argc, char** argv, char** env) {
	checkArgs(argc, argv);

	max_fd = servers[servers.size() - 1].getSock();
	while (1) {
		FD_ZERO(&wfds);
		FD_ZERO(&rfds);
		for (size_t index = 0; index < servers.size(); index++) {
			_setFDSet(servers[index]);
		}

		_slct(max_fd + 1, &rfds, nullptr, nullptr, nullptr);

		for (size_t index = 0; index < servers.size(); index++) {
			if (FD_ISSET(servers[index].getSock(), &rfds))
				_acceptConnection(servers[index]);
		}

		for (size_t i = 0; i < servers.size(); i++) {
			for (size_t ii = 0; ii < servers[i].clients.size(); ii++) {
				if (FD_ISSET(servers[i].clients[ii]->fd, &rfds)) {
					_receive(servers[i].clients[ii]);
				}
				if (servers[i].clients[ii]->request != nullptr && FD_ISSET(servers[i].clients[ii]->fd, &wfds)) {
					_send(servers[i].clients[ii]);
				}
			}
		}
	}
	return 0;
}
