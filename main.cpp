#include "Server/Server.hpp"

void routing(Request& request, Response& response) {
	if (request.path == "/") {
		response.setStatus("200 OK");
		response.send("pages/index.html");
	}
	else if (request.path == "/run_script")
		std::cout << "run script" << std::endl;
	else {
		response.setStatus("404 Not Found");
		response.send("pages/404.html");
	}
}

int main(void) {
	Server server(routing);

	server.listen(5432);
}
