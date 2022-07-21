#include <cstdio>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

const int MAXLINE = 1024;

int main (int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;
    if ( argc != 2 )
    {
        std::cout << "usage: <prog name> <IP address>" << std::endl;
        exit(1);
    }
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    {
        perror ("socket");
        exit(1);
    }
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13);
    
    if ( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        perror ("inet_pton");
        exit(1);
    }

    if ( connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr)) < 0 )
    {
        perror ("connect");
        exit(1);
    }


    while( (n = read(sockfd, recvline, MAXLINE)) > 0 )
    {
        recvline[n] = 0;
        if ( fputs(recvline, stdout) == EOF )
        {
            std::cout << "fputs error" << std::endl;
        }
    }
    if ( n < 0 )
    {
        std::cout << "read error" << std::endl;
    }
    
    exit(0);
}
