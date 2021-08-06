#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <map>
#include "../Request/Request.hpp"
#include "../webserv.hpp"
#include "../Configuration/Configuration.hpp"

class CGI {
private:
    std::map<std::string, std::string> _env;
    char** _char_env;
    int _fd;
    Configuration* serverConfiguration;

    void freeCharEnv();
    void initEnv();

public:
    Request& request;
    std::string exepath;

    CGI(Request&, Configuration*);
    void setEnv(std::string, std::string);
    void execute();
};