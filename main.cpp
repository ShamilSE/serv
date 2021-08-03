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

int main(int argc, char** argv, char** env) {
	if (argc != 2) {
		std::cout << "webserv: usage: " << "./webserv " << "[path_to_configuration]" << std::endl;
		exit(1);
	}

	std::string config(argv[1]);
	std::vector<std::string> configurations = parseConfig(config);
	std::vector<Server> servers;
	servers.reserve(configurations.size());

	for (size_t index = 0; index < configurations.size(); index++) {
		Server server(routing, configurations[index]);
		servers.push_back(server);
	}
	// for (size_t index = 0; index < servers.size(); index++) {
	// 	servers[index].listen();
	// }
	servers[0].listen();
}
