#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 8882
#define MAXLEN 1024

static void error(char* msg)
{
    perror(msg);
    exit(1);
}

void* client_main(void* data)
{
    int sockfd;
    int n;
    int serverlen;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char *hostname = "0.0.0.0";
    char buf[MAXLEN];

    /* socket: create the socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }

    /* gethostbyname: get the server's DNS entry */
    server = gethostbyname(hostname);
    if (server == NULL)
    {
        fprintf(stderr,"ERROR, no such host as %s\n", hostname);
        exit(0);
    }

    /* build the server's Internet address */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
	  (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(PORT);

    /* get a message from the user */
    bzero(buf, MAXLEN);
    printf("Please enter msg: ");
    fgets(buf, MAXLEN, stdin);

    /* send the message to the server */
    serverlen = sizeof(serveraddr);
    n = sendto(sockfd, buf, strlen(buf), 0, &serveraddr, serverlen);
    if (n < 0) 
    {
        error("ERROR in sendto");
    }    
    /* print the server's reply */
    n = recvfrom(sockfd, buf, strlen(buf), 0, &serveraddr, &serverlen);
    if (n < 0) 
    {
        error("ERROR in recvfrom");
    }
    printf("Echo from server: %s", buf);

    return NULL;
}
