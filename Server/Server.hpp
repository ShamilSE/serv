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
#include "../SmartPointer.hpp"
#include "../Response/Response.hpp"
#include "../Client/Client.hpp"

class Server {
private:
	fd_set wfds, rfds;
	int sock, port;
	struct sockaddr_in server_addr;
	int max_fd;
	std::vector<Client*> clients;

	void _acceptConnection();
	void _lstn(int, int);
	void _slct(int max_fd, fd_set *wfds, fd_set *rfds, fd_set *err, timeval *t);
	void _getServerAddr();
	void _receive(Client*);
	void _send(Client*);
	void _resetFDSet();

public:
	Server(int);
	void listen(int);
};
