#include "Request.hpp"

void Request::parseRequest(std::string message) {
	std::string tmp;
	std::string key;
	std::string value;

	method = message.substr(0, message.find(" "));
	tmp = toNextSymbol(message, " ");
	path = tmp.substr(0, tmp.find(" "));
	tmp = toNextSymbol(tmp, " ");
	protocolV = tmp.substr(0, tmp.find("\r"));
	tmp = toNextSymbol(tmp, "\n");

	size_t found;
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

Request::Request(std::string& message): message(message) {
	parseRequest(message);
	std::cout << "===============REQUEST==================" << std::endl;
	std::cout << message << std::endl;
	std::cout << "========================================" << std::endl;
}

Request::~Request() {
	headers.clear();
}