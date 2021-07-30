#pragma once

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <iostream>
#include <cstring>
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
	int max_fd;

	void acceptConnection();
	void lstn(int, int);
	void slct(int max_fd, fd_set *wfds, fd_set *rfds, fd_set *err, timeval *t);
	void initServer(int);

public:
	Server(int, int, int);
	void listenSocket(int);
	void receive(Client*);
	void send(Client*);
	void closeConnection(Client* client);
};

