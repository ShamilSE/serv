#include "Response.hpp"

std::string Response::getHeaders() {
	std::string s_headers;
	std::map<std::string, std::string>::iterator it = _headers.begin();
	for (; it != _headers.end(); it++)
		s_headers += it->first + ": " + it->second + "\n";
	return s_headers;
}

Response::Response(Request* request): _client_fd(request->client_fd) {}

void Response::setHeader(std::string key, std::string value) {_headers[key] = value;}
void Response::setStatus(std::string status) {_status = status;}

std::string Response::getStartingLine() {return "HTTP/1.1 " + _status + "\n";}
std::string Response::getStatus() {return _status;}
std::string Response::getBody() {return _body;}

void Response::send(std::string filepath) {
	_body = readFile(filepath);
	setHeader("Content-Length", std::to_string(_body.size()));
	setHeader("Connection", "Keep-Alive");
	setHeader("Keep-Alive", "timeout=5, max=10");
	setHeader("Status", getStatus());

	std::string response = getStartingLine() + getHeaders() + "\n" + getBody();
	int bytes_sent = write(_client_fd, response.c_str(), response.size());

	if (response.size() == bytes_sent)
		std::cout << "all data sent" << std::endl;
	else
		std::cout << "part of data sent" << std::endl;
}
