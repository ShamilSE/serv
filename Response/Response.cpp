#include "Response.hpp"

void Response::setHeader(std::string key, std::string value) {headers[key] = value;}

std::string Response::getHeaders() {
	std::string s_headers;
	std::map<std::string, std::string>::iterator it = headers.begin();
	for (; it != headers.end(); it++) {
		s_headers += it->first + ": " + it->second + "\n";
	}
	return s_headers;
}

std::string Response::routing(std::string path) {
	std::ifstream	in;
	std::ostringstream buf;

	if (path == "/") {

		in.open("./pages/index.html");
		if (!in) {
			std::cout << "cannot open index.html file" << std::endl;
			return "";
		}
		buf << in.rdbuf();
		return buf.str();
	}

	else
		return "<h1>404</h1>";
	return "";
}

Response::Response(Request* request) {
	startingLine = "HTTP/1.1 200 OK\n";
	body = routing(request->path);
	this->client_fd = request->client_fd;
}

std::string readFile(std::string filepath) {
	std::ifstream in;
	std::ostringstream buf;

	in.open(filepath);
	if (!in)
		throw std::runtime_error("file can't be opened");
	buf << in.rdbuf();
	return buf.str();
}

void Response::send(std::string filepath) {
	body = readFile(filepath);
	setHeader("Content-Length", std::to_string(body.size()));
	setHeader("Connection", "Keep-Alive");
	setHeader("Keep-Alive", "timeout=5, max=10");

	std::string response = startingLine + getHeaders() + "\n" + body;
	int bytes_sent = write(client_fd, response.c_str(), response.size());
	if (response.size() == bytes_sent)
		std::cout << "all data sent" << std::endl;
	else
		std::cout << "part of data sent" << std::endl;
}
