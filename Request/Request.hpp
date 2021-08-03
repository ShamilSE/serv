#pragma once

#include <iostream>
#include <unistd.h>
#include <string>
#include <map>
#include "../webserv.hpp"

struct Request {
	Request(std::string&);
	~Request();

	std::string message;

	int client_fd;
	std::string method;
	std::string path;
	std::string protocolV;
	std::map<std::string, std::string> headers;

	void parseRequest(std::string);
	void initStartingLine(std::string starting_line);
};