#pragma once

#include <string>
#include <unistd.h>

class CGI {
public:
    std::string exepath;

    CGI(std::string exepath);
    void execute();
};