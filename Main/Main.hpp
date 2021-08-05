#pragma once
#include "../webserv.hpp"
#include "../Server/Server.hpp"
#include "../Request/Request.hpp"
#include "../Response/Response.hpp"
#include "../Client/Client.hpp"
#include "../CGI/CGI.hpp"

class Main {
public:
    fd_set wfds, rfds;
    int max_fd;
    std::vector<Server> servers;

    static Main* Instance();

    void configureServers(std::string);
    void routing(Request&, Response&);
    void setFDSet(Server&);
    void slct(int, fd_set*, fd_set*, fd_set*, timeval*);
    void acceptConnection(Server&);
    void receive(Client*);
    void send(Client*);
    void cycle();

private:
    Main(){}
    Main(const Main& root);
    Main& operator=(const Main&);

};
