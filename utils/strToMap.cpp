#include "../webserv.hpp"

std::map<std::string, std::string> strToMap(std::string src, std::string delimeter) {
	std::map<std::string, std::string> map;
	std::string key;
	std::string value;

 	while (1) {
		key = src.substr(0, src.find(delimeter));
		if (src.find(delimeter) == std::string::npos)
			break;
		src = toNextSymbol(src, delimeter);
		value = src.substr(0, src.find("\n"));
		src = toNextSymbol(src, "\n");
		map[key] = value;
	}
	return map;
}

// eos - end of string
std::map<std::string, std::string> strToMap(std::string src, std::string delimeter, std::string eos) {
	std::map<std::string, std::string> map;
	std::string key;
	std::string value;

 	while (1) {
		key = src.substr(0, src.find(delimeter));
		if (src.find(delimeter) == std::string::npos)
			break;
		src = toNextSymbol(src, delimeter);
		value = src.substr(0, src.find(eos));
		src = toNextSymbol(src, eos);
		map[key] = value;
	}
	return map;
}