#include "Server/Server.hpp"

void routing(Request& request, Response& response) {
	std::cout << "this is callback" << std::endl;

	if (request.path == "/")
		response.send("pages/index.html");
	else
		response.send("pages/404.html");
}

int main(void) {
	Server server(routing);

	server.listen(5432);
}
