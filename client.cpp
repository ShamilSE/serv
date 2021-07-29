// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>

#define PORT 5432

int main(int argc, char const *argv[])
{
    int sock = 0; long valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    if (bind(sock, (struct sockaddr*)&serv_addr, sizeof serv_addr) == -1) {
        perror("error.");
        exit(1);
    }
    
    memset(&serv_addr, '0', sizeof(serv_addr));
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    int connect_code = connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    std::cout << connect_code << std::endl;
    if (connect_code == -1)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, flags, O_NONBLOCK);
    char buf[1024];
    int bytes_read = read(sock, buf, 14);
    buf[bytes_read] = 0;
    printf("%s\n", buf);
    write(sock , "message to server" , 18);
    valread = read( sock , buffer, 1024);
    return 0;
}
