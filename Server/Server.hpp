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
#include "../SmartPointer.hpp"
#include "../Response/Response.hpp"

#define MAX_CLIENTS 10

class Server {
private:
	fd_set wfds, rfds;
	int sock, port;
	struct sockaddr_in server_addr;
	std::vector<Client*> clients;

	void acceptConnection();
	void lstn(int, int);
	void slct(int max_fd, fd_set *wfds, fd_set *rfds, fd_set *err, timeval *t);
	void initServer(int);

public:
	Server(int, int, int);
	void listenSocket(int);
	std::string receive(Client*);
};

