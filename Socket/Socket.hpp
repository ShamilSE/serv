#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

class Socket {
private:
	int _socket;
	struct sockaddr_in _addr;
	int _connection_fd;

public:
	Socket(int, int, int);
	void listenSocket(int);
};

