#include "Server/Server.hpp"
#include "Main/Main.hpp"
#include "Server/Server.hpp"

int main(int argc, char** argv, char** env) {
	if (argc != 2) {
		std::cout << "webserv: usage: " << "./webserv " << "[path_to_configuration]" << std::endl;
		exit(1);
	}
	Main* mainClass = Main::Instance();

	mainClass->configureServers(argv[1]);
	mainClass->cycle();
	return 0;
}
