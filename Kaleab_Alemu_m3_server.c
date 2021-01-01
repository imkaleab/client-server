// SERVER
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0, cli_size, portno, readn;
    struct sockaddr_in serv_addr, cli_addr;
    char sendBuff[1025]; 
    char message [100]; 
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        printf("socket error\n");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff));
    serv_addr.sin_family = AF_INET;    
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    portno = atoi(argv[1]);
    serv_addr.sin_port = htons(portno);    
    int on = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    if (bind(listenfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1)
    {
        printf("bind error\n");
        exit(EXIT_FAILURE);
    }

    if (listen(listenfd, 5) == -1)
    {
        printf("listen error\n");
        exit(EXIT_FAILURE);
    }
    cli_size = sizeof(cli_addr);
    if ((connfd = accept(listenfd,(struct sockaddr *) &cli_addr,&cli_size)) == -1)
    {
        printf("accept error\n");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        bzero(message, 100);
        if (readn = read(connfd, message,100) == -1)
            printf("read error\n");
        strcpy(sendBuff, "What do you mean by ");
        strcat(sendBuff, "'");
        strcat(sendBuff, message);
        strcat(sendBuff, "'?");
        
        write(connfd, sendBuff, strlen(sendBuff));
        if (strncmp("quit", message, 4) == 0)
            break;
    } 
    close(connfd);    
    sleep(1);

    return 0;
}