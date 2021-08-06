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
    void routing(Request&, Response&, Configuration*);
    void setFDSet(Server&);
    void slct(int, fd_set*, fd_set*, fd_set*, timeval*);
    void acceptConnection(Server&);
    void receive(Client*);
    void send(Client*, Configuration*);
    void cycle();
    std::vector<std::string> parseConfig(std::string);

private:
    Main(){}
    Main(const Main& root);
    Main& operator=(const Main&);

};
