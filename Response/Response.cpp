#include "Response.hpp"

std::string Response::routing(std::string path) {
	if (path == "/") {
		return "<h1>index page</h1>";
	}
	return NULL;
}

Response::Response(Request* request) {
	startingLine = "HTTP/1.1 200 OK";
	body = routing(request->path);
}

void Response::send(int connection_fd) {
	std::string space = "\r\n\n";
	std::string response = startingLine + space + body;

	write(connection_fd, "HTTP/1.1 200 OK\r\n\n<h1>aboba</h1>", 32);
	std::cout << "data sent" << std::endl;
}