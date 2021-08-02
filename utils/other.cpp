#include "../webserv.hpp"

std::string readFile(std::string filepath) {
	std::ifstream in;
	std::ostringstream buf;

	in.open(filepath);
	if (!in)
		throw std::runtime_error("file can't be opened");
	buf << in.rdbuf();
	return buf.str();
}