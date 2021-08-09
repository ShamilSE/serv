#include "Main.hpp"

Main* Main::Instance() {
    static Main* main = new Main();
    return main;
}

std::vector<std::string> Main::parseConfig(std::string filename) {
	std::string configContent;
	try {
		configContent = readFile(filename);
	}
	catch (std::runtime_error & e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}

	std::vector<std::string> configurations;
	while (1) {
		if (configContent.find("}") == std::string::npos)
			break;
		configContent = toNextSymbol(configContent, "\n", 7);
		configurations.push_back(configContent.substr(0, configContent.find("}")));
		configContent = toNextSymbol(configContent, "}", 0);
	}
	return configurations;
}

void Main::configureServers(std::string config) {
    std::vector<std::string> configurations = parseConfig(config);
	servers.reserve(configurations.size());

	for (size_t index = 0; index < configurations.size(); index++) {
		Server server(configurations[index]);
		servers.push_back(server);
	}
}

void Main::setFDSet(Server& server) {
	FD_SET(server.getSock(), &rfds);
	for (size_t ii = 0; ii < server.clients.size(); ii++) {
		FD_SET(server.clients[ii]->fd, &wfds);
		FD_SET(server.clients[ii]->fd, &rfds);
		if (server.clients[ii]->fd > max_fd)
			max_fd = server.clients[ii]->fd;
	}
}

void Main::slct(int max_fd, fd_set *rfds, fd_set *wfds, fd_set *err, timeval *t) {
	if (-1 == (select(max_fd + 1, rfds, wfds, err, t))) {
		if (errno != EINTR) {
			perror("select");
			exit(1);
		}
		else
			printf("signal");
	}
}

void Main::acceptConnection(Server& server) {
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

void Main::receive(Client* client) {
	char buf[1024];

	int bytes_read = read(client->fd, buf, 1024);
	if (bytes_read > 0) {
		buf[bytes_read] = 0;
		std::string str_buf(buf, bytes_read);
		client->setRequest(new Request(str_buf));
		client->request->setClientFD(client->fd);
		client->setResponse(new Response(client->request));
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

void Main::send(Client* client, Configuration* serverConfig) {
	routing(*client->request, *client->response, serverConfig);
	delete client->request;
	delete client->response;
	client->request = nullptr;
	client->response = nullptr;
}

void Main::routing(Request& request, Response& response, Configuration* serverConfig) {
	response.setStatus("200 OK");
	if (request.getPath() == "/")
		response.send("pages/index.html");
	else if (request.getPath() == "/form") {
		if (request.getMethod() == "GET")
			response.send("pages/form.html");
		else if (request.getMethod() == "POST") {
			response.setStatus("201 Created");
			response.send();
			CGI cgi(request, serverConfig);
			cgi.execute("CGI/formHandler");
		}
	}
	else if (request.getPath() == "/uploading") {
		response.send("pages/uploading.html");
	}
	else {
		response.setStatus("404 Not Found");
		response.send("pages/404.html");
	}
}

void Main::cycle() {
	max_fd = servers[servers.size() - 1].getSock();
	while (1) {
		FD_ZERO(&wfds);
		FD_ZERO(&rfds);
		for (size_t index = 0; index < servers.size(); index++) {
			setFDSet(servers[index]);
		}

		slct(max_fd + 1, &rfds, nullptr, nullptr, nullptr);

		for (size_t index = 0; index < servers.size(); index++) {
			if (FD_ISSET(servers[index].getSock(), &rfds))
				acceptConnection(servers[index]);
		}

		for (size_t i = 0; i < servers.size(); i++) {
			for (size_t ii = 0; ii < servers[i].clients.size(); ii++) {
				if (FD_ISSET(servers[i].clients[ii]->fd, &rfds)) {
					receive(servers[i].clients[ii]);
				}
				if (servers[i].clients[ii]->request != nullptr && FD_ISSET(servers[i].clients[ii]->fd, &wfds)) {
					send(servers[i].clients[ii], servers[i].getConfig());
				}
			}
		}
	}
}
