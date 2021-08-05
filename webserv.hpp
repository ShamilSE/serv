#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <iostream>
#include <exception>
#include "Request/Request.hpp"

std::string getCurrentUTCDate();
std::string readFile(std::string filepath);

std::string toNextSymbol(std::string str, std::string c);
std::map<std::string, std::string> strToMap(std::string src, std::string delimeter);
std::map<std::string, std::string> strToMap(std::string src, std::string delimeter, std::string eos);
std::vector<std::string> split(std::string src, std::string delimeter);
std::vector<std::string> parseConfig(std::string filename);
char** mapToCharArray(std::map<std::string, std::string> map);