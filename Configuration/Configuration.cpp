#include "Configuration.hpp"

bool Configuration::validateRequiredFields() {
    if (fields.find("host") != fields.end() && fields.find("port") != fields.end())
        return true;
    return false;
}

// void Configuration::parseLocations(std::string loc) {
//     if (count_substrs(loc, "location") > 1)
//         current
//     while (std::string::npos != loc.find("location")) {
//         locations.push_back(strToMap(loc, " "));
//         if (std::string::npos == loc.find("location", 10))
//             break;
//         loc = loc.substr(loc.find("location", 8));
//     }
// }

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
