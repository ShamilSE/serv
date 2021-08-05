#pragma once

#include <iostream>
#include <unistd.h>
#include <string>
#include <map>
#include "../webserv.hpp"

class Request {
public:
	std::string message;
	int client_fd;
	std::string method;
	std::string path;
	std::string protocolV;
	std::map<std::string, std::string> headers;

public:
	Request(std::string&);
	~Request();

	void parseRequest(std::string);
	void initStartingLine(std::string starting_line);

	void setClientFD(int);

	std::string getMethod() const;
	std::string getPath() const;
	std::string getProtocolV() const;
	std::string getHeaderByKey(std::string) const;
	std::string getMessage() const;
	int getClientFD() const;
};