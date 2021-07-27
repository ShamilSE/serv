#include "Server/Server.hpp"

int main(void) {
	Server server(AF_INET, SOCK_STREAM, 5432);

	server.listenSocket(3);
}
