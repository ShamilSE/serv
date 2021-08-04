#pragma once
#include "../webserv.hpp"
#include "../Server/Server.hpp"
#include "../Request/Request.hpp"
#include "../Response/Response.hpp"

class Main {
public:
    fd_set wfds, rfds;
    int max_fd;
    std::vector<Server> servers;

    static Main* Instance();

    std::vector<Server> getConfiguredServers(std::string);

    void routing(Request&, Response&);

private:        
    Main(){}
    Main(const Main& root) = delete;
    Main& operator=(const Main&) = delete;

};
