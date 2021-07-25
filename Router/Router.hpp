#pragma once

#include <iostream>
#include <string>
#include "../Request/Request.hpp"
#include "../HtmlHandler/HtmlHandler.hpp"

class Router {
private:
	std::string* _request;
	HtmlHandler html;

public:
	Router();
	std::string route(std::string);
};
