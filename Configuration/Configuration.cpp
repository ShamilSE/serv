#include "Configuration.hpp"

bool Configuration::validateRequiredFields() {
    if (fields.find("host") != fields.end() && fields.find("port") != fields.end())
        return true;
    return false;
}

void Configuration::parseConfig(std::string configContent) {
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
