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

struct Client {
    int fd;
    struct sockaddr_in addr;

    Request* request;
    Response* response;

    Client();
    ~Client();

    void initClient();
};

std::ostream& operator<<(std::ostream& out, const Client & client);