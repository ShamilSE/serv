#include "Request.hpp"

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
	std::map<std::string, std::string> headers = strToMap(message, ":");
}

Request::Request(std::string& message): message(message) {
	parseRequest(message);
	std::cout << "===============REQUEST==================" << std::endl;
	std::cout << message << std::endl;
	std::cout << "========================================" << std::endl;
}

Request::~Request() {
	headers.clear();
}