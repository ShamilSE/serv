#pragma once

#include <string>
#include <map>

class Response {
	std::string startingLine;
	std::map<std::string, std::string> headers;
	std::string body;

	Response();
};