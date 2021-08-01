#include "Server/Server.hpp"

int main(void) {
	Server server(5432);

	server.listen(3);
}
