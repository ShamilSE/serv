#pragma once

#include <string>
#include <iostream>
#include <map>

class Request {
private:
	std::string _req_message;
	std::string _page;

	std::map<std::string, std::string> _starting_line;


public:
	Request(std::string);
	std::string getFullRequest();
	std::string getRequestedPage();
};