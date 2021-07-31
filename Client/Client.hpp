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

struct Client {
    int connection_fd;
    Request *request;
    struct sockaddr_in addr;

    Client();
    void initClient();
    void log();
};