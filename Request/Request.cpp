#include "Request.hpp"

Request::Request(std::string req): _req_string(req) {
	_page = req.substr(req.find("/"), req.find("H"));
	std::cout << "req page is " << _page << std::endl;
}

std::string Request::getFullRequest() {return _req_message;}
std::string Request::getRequestedPage() {return _page;}