#include <iostream>
#include <exception>

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