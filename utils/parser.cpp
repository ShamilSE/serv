#include "../webserv.hpp"

std::string toNextSymbol(std::string str, std::string c, size_t pos) {
	std::string tmp;
	try {
		tmp = str.substr(str.find(c, pos));
		tmp = tmp.substr(1);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return tmp;
}

char** mapToCharArray(std::map<std::string, std::string> map, std::string delimeter) {
	char** array = new char*[map.size()];

	std::map<std::string, std::string>::iterator it = map.begin();
	for (size_t index = 0; index < map.size(); index++, it++) {
		array[index] = new char[(it->first + delimeter + it->second).size()];
		strcpy(array[index], (it->first + delimeter + it->second).c_str());
	}
	array[map.size()] = NULL;
	return array;
}
