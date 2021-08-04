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
#include "../Request/Request.hpp"
#include "../Response/Response.hpp"
#include "../Client/Client.hpp"
#include "../Configuration/Configuration.hpp"

class Server {
private:
	int sock;
	int port;
	struct sockaddr_in server_addr;
	Configuration* _conf;

	void _getServerAddr();
	void _createSocket();
	void _lstn(int sock);

public:
	Server(std::string);
	// Server(const Server&);
	// Server& operator=(const Server&);
	~Server();

	int getSock();
	std::vector<Client*> clients;
};
