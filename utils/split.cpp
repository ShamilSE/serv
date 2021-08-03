#include "../webserv.hpp"

std::vector<std::string> split(std::string src, std::string delimeter) {
    std::vector<std::string> v;
    while (1) {
        if (src.find(delimeter) == std::string::npos)
            break;
        v.push_back(src.substr(0, src.find(delimeter)));
        src = toNextSymbol(src, delimeter);
    }
    return v;
}
