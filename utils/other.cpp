#include "../webserv.hpp"

std::string readFile(std::string filepath) {
	std::ifstream in;
	std::ostringstream buf;

	in.open(filepath);
	if (!in)
		throw std::runtime_error("configuration file can't be opened");
	buf << in.rdbuf();
	in.close();
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

	return str_buf;
}

size_t count_substrs(std::string src, std::string substr) {
	size_t counter = 0;
	while (src.find(substr) != std::string::npos) {
		counter++;
		src = src.substr(src.find(substr, substr.size()));
	}
	return counter;
}
