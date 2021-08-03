#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <ctime>
#include "Request/Request.hpp"


std::string getCurrentUTCDate();
std::string readFile(std::string filepath);

std::string toNextSymbol(std::string str, std::string c);
