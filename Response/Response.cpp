#include "Response.hpp"

std::string Response::routing(std::string path) {
	std::ifstream	in;
	std::ostringstream buf;

	if (path == "/") {

		in.open("/Users/mismene/Desktop/serv/pages/index.html");
		if (!in) {
			std::cout << "cannot open index.html file" << std::endl;
			return NULL;
		}
		buf << in.rdbuf();
		return buf.str();
	}

	else
		return "<h1>404</h1>";
	return NULL;
}

Response::Response(Request* request) {
	startingLine = "HTTP/1.1 200 OK";
	body = routing(request->path);
}

void Response::send(int connection_fd) {
	std::string space = "\r\n\n";
	std::string response = startingLine
		+ "\n"
		+ "Content-Length: "
		+ std::to_string(body.size())
		+ "\n"
		+ "Connection: Keep-Alive"
		+ "\n"
		+ "Keep-Alive: timeout=5, max=10"
		+ "\t\n\n"
		+ body;

	int bytes_sent = write(connection_fd, response.c_str(), response.size());
	// int bytes_sent = write(connection_fd, "HTTP/1.1 200 OK\r\n\n<h1>hello</h1>", 32);
	std::cout << "data sent (" << bytes_sent << ") bytes" << std::endl;
}