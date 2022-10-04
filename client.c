#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc , char*argv[]){
    struct sockaddr_in server_addr = {0};

    server_addr.sin_family = AF_INET;
    unsigned long addr = (unsigned long)INADDR_LOOPBACK; // 0x7f000001 address of localhost
    server_addr.sin_addr.s_addr = htonl(addr);
    server_addr.sin_port = htons(1234);

    struct sockaddr server_info = {0};
    socklen_t server_info_len = sizeof(server_info);

    int socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_file_descriptor == -1){
        perror("socket");
        return -1;
    }
    //connect
    if(connect(socket_file_descriptor, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        perror("connect");
        return -1;
    }
    char buffer[1024];
    ssize_t read_size = recv(socket_file_descriptor, buffer, ((int)sizeof(buffer)) - 1, 0);
    printf("%s\n", buffer);
    close(socket_file_descriptor);
    return 0;
}