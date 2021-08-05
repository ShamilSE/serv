#include "../webserv.hpp"

std::string toNextSymbol(std::string str, std::string c) {
	std::string tmp;
	try {
		tmp = str.substr(str.find(c));
		tmp = tmp.substr(1);
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return tmp;
}

std::vector<std::string> parseConfig(std::string filename) {
	std::string configContent;
	try {
		configContent = readFile(filename);
	}
	catch (std::exception & e) {
		std::cerr << e.what();
	}

	std::vector<std::string> configurations;
	while (1) {
		if (configContent.find("}") == std::string::npos)
			break;
		configContent = toNextSymbol(configContent, "{");
		configurations.push_back(configContent.substr(0, configContent.find("}")));
		configContent = toNextSymbol(configContent, "}");
	}
	return configurations;
}

char** mapToCharArray(std::map<std::string, std::string> map) {
	char** array = (char**)malloc(map.size() + 1);

	std::map<std::string, std::string>::iterator it = map.begin();
	for (size_t index = 0; index < map.size(); index++, it++) {
		array[index] = strdup((it->first + ": " + it->second).c_str());
	}
	array[map.size()] = NULL;
	return array;
}
