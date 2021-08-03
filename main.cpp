#include "Server/Server.hpp"

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

int main(void) {
	Server server(routing);

	server.listen(5432);
}
