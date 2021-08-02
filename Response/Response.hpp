#pragma once

#include "../webserv.hpp"

class Response {
private:
	std::string _startingLine;
	std::string _protocolV;
	std::string _status;
	std::map<std::string, std::string> _headers;
	std::string _body;
	int _client_fd;

public:
	Response(Request*);

	void send(std::string);

	void setHeader(std::string, std::string);
	void setStatus(std::string);

	std::string getStartingLine();
	std::string getStatus();
	std::string getHeaders();
	std::string getBody();
};