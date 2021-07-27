#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include "../Client/Client.hpp"
#include "../SmartPointer/SmartPointer.hpp"

class Server {
private:
	fd_set wfds, rfds;
	int _socket;
	struct sockaddr_in _addr;
	int _connection_fd;
	std::vector<Client*> _clients;

public:
	Server(int, int, int);
	void listenSocket(int);
	int acceptConnection();
};

