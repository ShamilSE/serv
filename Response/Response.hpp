#pragma once

#include "../Request/Request.hpp"
#include <string>
#include <map>

struct Response {
	std::string startingLine;
	std::map<std::string, std::string> headers;
	std::string body;

	Response(Request*);
	void send(int);
	std::string routing(std::string path);
};