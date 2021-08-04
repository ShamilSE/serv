#include "Main.hpp"

Main* Main::Instance() {
    static Main* main = new Main();
    return main;
}

std::vector<Server> Main::getConfiguredServers(std::string config) {
    std::vector<std::string> configurations = parseConfig(config);
	std::vector<Server> servers;
	servers.reserve(configurations.size());

	for (size_t index = 0; index < configurations.size(); index++) {
		Server server(configurations[index]);
		servers.push_back(server);
	}
	return servers;
}

void Main::routing(Request& request, Response& response) {
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
