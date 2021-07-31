#pragma once

#include <iostream>
#include <unistd.h>
#include <string>
#include <map>
#include "../webserv.hpp"

struct Request {
	std::string method;
	std::string path;
	std::string protocolV;
	std::map<std::string, std::string> headers;

	Request(std::string);
	void parseRequest(std::string);
};