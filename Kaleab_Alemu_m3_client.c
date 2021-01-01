// CLIENT
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0, portno;
    char recvBuff[1025];
    char message [100];
    struct sockaddr_in serv_addr;
    memset(recvBuff, '0', sizeof(recvBuff));

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket error\n");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    portno = atoi(argv[1]);
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (const struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("connect error\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        bzero(message, 100);
        bzero(recvBuff, 1025);
       
        printf("Please enter a message> ");
        fgets(message,100,stdin);
        message[strlen(message) -1] = '\0';
        write (sockfd, message, strlen(message));

        if (strncmp("quit", message, 4) == 0)
            break;
        
        if((n = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
            printf("%s\n", recvBuff);      
        
    }

    if (n < 0)
    {
        printf("read error\n");
    }
    return 0;
}