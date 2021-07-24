#ifndef SOCKET_HPP
#define SOCKET_HPP

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
	int _connection;

public:
	Socket(int, int, int);
	void listenSocket(int);
	int acceptConnection();
};

#endif