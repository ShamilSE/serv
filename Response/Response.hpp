#pragma once

#include "../Request/Request.hpp"
#include <string>
#include <map>
#include <fstream>
#include <sstream>

struct Response {
	std::string startingLine;
	std::map<std::string, std::string> headers;
	std::string body;
	int client_fd;

	Response(Request*);

	void send();
	void send(std::string);
	std::string routing(std::string path);
	void setHeader(std::string, std::string);

	std::string getHeaders();
};