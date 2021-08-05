#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <map>
#include "../Request/Request.hpp"
#include "../webserv.hpp"

class CGI {
private:
    std::map<std::string, std::string> _env;

public:
    Request& request;
    std::string exepath;

    CGI(Request&);
    void execute();
};