#include "Socket/Socket.hpp"

int socket(int domain, int type, int protocol);

int main(void) {
	Socket socket(AF_INET, SOCK_STREAM, 5432);

	socket.listenSocket(3);
	socket.acceptConnection();
}
