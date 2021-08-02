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

std::string getCurrentUTCDate() {
	// current date/time based on current system
	time_t now = time(0);

	// convert now to string form
	char* dt = ctime(&now);

	// convert now to tm struct for UTC
	tm *gmtm = gmtime(&now);
	dt = asctime(gmtm);
	std::string str_buf(dt);

	std::cout << str_buf << std::endl;
	return str_buf;
}
