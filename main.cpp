#include "Server/Server.hpp"

void routing(Request& request, Response& response) {
	if (request.path == "/")
		response.send("pages/index.html");
	else if (request.path == "/run_script")
		std::cout << "run script" << std::endl;
	else
		response.send("pages/404.html");
}

int main(void) {
	Server server(routing);

	server.listen(5432);
}
