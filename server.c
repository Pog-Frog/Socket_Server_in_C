#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in server_addr = {0};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);
    
    struct sockaddr client_info = {0};
    socklen_t client_info_len = sizeof(client_info);

    int fd = socket(AF_INET, SOCK_STREAM, 0);

    int socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_file_descriptor == -1)
    {
        perror("socket");
        return -1;
    }

    //bind
    if (bind(socket_file_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("bind");
        return -1;
    }

    //listen
    if(listen(socket_file_descriptor, 0) == -1)
    {
        perror("listen");
        return -1;
    }

    //accept
    int client_socket_file_descriptor = accept(socket_file_descriptor, &client_info, &client_info_len);
    if(client_socket_file_descriptor == -1)
    {
        perror("accept");
        return -1;
    }

    char *buffer = "Hello World";
    send(client_socket_file_descriptor, buffer, strlen(buffer), 0);
    close(client_socket_file_descriptor);
    return 0;
}