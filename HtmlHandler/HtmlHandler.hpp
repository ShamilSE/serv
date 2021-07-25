#pragma once

#include <string>
#include <fstream>
#include <sstream>

class HtmlHandler {
public:
	HtmlHandler();
	std::string htmlFileToString(std::string);
};