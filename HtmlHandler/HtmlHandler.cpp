#include "HtmlHandler.hpp"

HtmlHandler::HtmlHandler() {}

std::string HtmlHandler::htmlFileToString(std::string filepath) {
	std::ifstream file;
	std::ostringstream buf;

	file.open(filepath);
	if (!file) {
		perror("can't open requested file");
		exit(1);
	}
	buf << file.rdbuf();
	return buf.str();
}