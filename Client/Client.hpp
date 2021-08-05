#pragma once

#include <map>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <fcntl.h>
#include <arpa/inet.h>
#include "../Request/Request.hpp"
#include "../Response/Response.hpp"

class Client {
public:
    int fd;

    Request* request;
    Response* response;

public:
    struct sockaddr_in addr;

    Client();
    ~Client();

    void initClient();

    int getFD();


    void setRequest(Request*);
    void setResponse(Response*);
};

std::ostream& operator<<(std::ostream& out, const Client & client);