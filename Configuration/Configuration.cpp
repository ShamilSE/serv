#include "Configuration.hpp"

bool Configuration::validateRequiredFields() {
    if (fields.find("host") != fields.end() && fields.find("port") != fields.end())
        return true;
    return false;
}

void Configuration::parseLocations(std::string loc) {
    std::string currentLocation;
    std::string target = "location";
    size_t string_current_position = 0;
    if (count_substrs(loc, target) > 1)
        currentLocation = loc.substr(0, loc.find(target, target.size()));
    else
        currentLocation = loc;
    while (1) {
        locations.push_back(strToMap(currentLocation, " "));
        string_current_position += currentLocation.size();
        if (loc.find(target, string_current_position) == std::string::npos)
            break;
        currentLocation = loc.substr(loc.find(target, string_current_position));
    }
}

void Configuration::parseConfig(std::string configContent) {
    if (configContent.find("location") == std::string::npos) {
        std::cerr << "at least one location / block" << std::endl;
        exit(1);
    }
    std::string locations = configContent.substr(configContent.find("location"));
    parseLocations(locations);
    configContent = configContent.substr(0, configContent.find("location"));
    fields = strToMap(configContent, " ");
    if (!validateRequiredFields())
    {
        std::cerr << "invalid configuration (host/port)" << std::endl;
        exit(1);
    }
}

Configuration::Configuration(std::string configContent) {
    parseConfig(configContent);
}
