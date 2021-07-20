#include <sys/types.h>
#include <sys/socket.h>

int socket(int domain, int type, int protocol);

int main(void) {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
}