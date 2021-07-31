#include "Request.hpp"

Request::Request(std::string message) {
	std::string tmp;
	std::string key;
	std::string value;

	method = message.substr(0, message.find(" "));
	tmp = toNextSymbol(message, " ");
	path = tmp.substr(0, tmp.find(" "));
	std::cout << "request path '" << path << "'" << std::endl;
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