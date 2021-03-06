#pragma once

#include <map>
#include <string>
#include "../webserv.hpp"

struct Configuration {
    Configuration(std::string);
    void parseConfig(std::string);
    void parseLocations(std::string);

    bool validateRequiredFields();

    std::map<std::string, std::string> fields;
    std::vector<std::map<std::string, std::string> > locations;
};
