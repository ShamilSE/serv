#include "Request.hpp"

void Request::initHeaders(std::string tmp) {
	std::string key;
	std::string value;

	while (1) {
		key = tmp.substr(0, tmp.find(":"));
		if (tmp.find(" ") == std::string::npos)
			break;
		tmp = toNextSymbol(tmp, " ");
		value = tmp.substr(0, tmp.find("\r"));
		tmp = toNextSymbol(tmp, "\n");
		headers[key] = value;
	}
}

void Request::initStartingLine(std::string starting_line) {
	method = starting_line.substr(0, starting_line.find(" "));
	starting_line = toNextSymbol(starting_line, " ");
	path = starting_line.substr(0, starting_line.find(" "));
	starting_line = toNextSymbol(starting_line, " ");
	protocolV = starting_line.substr(0, starting_line.find("\r"));
}

void Request::parseRequest(std::string message) {
	initStartingLine(message.substr(0, message.find("\r")));
	message = toNextSymbol(message, "\n");
	initHeaders(message);
}

Request::Request(std::string& message): message(message) {
	parseRequest(message);
	// std::cout << "===============REQUEST==================" << std::endl;
	// std::cout << message << std::endl;
	// std::cout << "========================================" << std::endl;
}

Request::~Request() {
	headers.clear();
}

void Request::setClientFD(int fd) {this->client_fd = fd;}

std::string Request::getMethod() const {return method;}
std::string Request::getPath() const {return path;}
std::string Request::getProtocolV() const {return protocolV;}
std::string Request::getHeaderByKey(std::string key) {return headers[key];}
std::string Request::getMessage() const {return message;}
int Request::getClientFD() const {return client_fd;}
