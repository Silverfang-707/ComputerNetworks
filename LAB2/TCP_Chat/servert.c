#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#define MAX 80
#define PORT 52000
#define SA struct sockaddr// Function designed for chat between client and server

void func(int connfd)
{
    char buff[MAX];
    int n;

    for (;;) 
    {
        bzero(buff, MAX);
        read(connfd, buff, sizeof(buff));// read the message from client and copy it in buffer
        printf("From client: %s\t To client: ", buff);// print buffer which contains the client contents
        bzero(buff, MAX);
        n = 0;

        while ((buff[n++] = getchar()) != '\n')
        {
            write(connfd,buff,sizeof(buff));
        }

        if (strncmp("exit", buff, 4) == 0)// if msg contains "Exit" then server exit and chat ended
        {
            printf("Server Exit...\n");
            break;
        }
    }
}

int main()
{
    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }

    else
    {
        printf("Socket successfully created..\n");
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) 
    {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
    {
        printf("Socket successfully binded..\n");
    }
    if ((listen(sockfd, 5)) != 0) 
    {
        printf("Listen failed...\n");
        exit(0);
    }
    else
    {
        printf("Server listening..\n");
    }

    len = sizeof(cli);
    connfd = accept(sockfd, (SA*)&cli, &len);
    
    if (connfd < 0)
    {
        printf("server accept failed...\n");
        exit(0);
    }
    else
    {
        printf("server accept the client...\n");
    }

    func(connfd);// Function for chatting between client and server
    close(sockfd);// After chatting close the socket
}
