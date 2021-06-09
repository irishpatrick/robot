#include "server.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdbool.h>

#include "msgq.h"

#define PORT 8082
#define MAXLEN 1024

static bool running;

typedef struct _server_data
{
    pthread_mutex_t* send_mutex;
    pthread_mutex_t* recv_mutex;
    bmsgq* chan;
} server_data;

static void error(char *msg)
{
    perror(msg);
    exit(1);
}

void* server_main(void* data)
{
    // unpack data
    server_data* sdat = (server_data*)data;
    bmsgq* chan = sdat->chan;
    pthread_mutex_t* send_mutex = sdat->send_mutex;
    pthread_mutex_t* recv_mutex = sdat->recv_mutex;

    // setup server
    char buf[MAXLEN];
    int clientlen;
    int sockfd;
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    struct hostent* hostp;
    char* hostaddrp;
    int optval;
    int n;

    /*
     * socket: create the parent socket
     */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        error("ERROR opening socket");
    }

    /* setsockopt: Handy debugging trick that lets
     * us rerun the server immediately after we kill it;
     * otherwise we have to wait about 20 secs.
     * Eliminates "ERROR on binding: Address already in use" error.
     */
    optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
           (const void *)&optval , sizeof(int));

    /*
     * build the server's Internet address
     */
    bzero((char *) &serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(PORT);

    /*
     * bind: associate the parent socket with a port
     */
    if (bind(sockfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
    {
        error("ERROR on binding");
    }

    /*
     * main loop: wait for a datagram, then echo it
     */
    clientlen = sizeof(clientaddr);
    while (running)
    {
        /*
        * recvfrom: receive a UDP datagram from a client
        */
        bzero(buf, MAXLEN);
        n = recvfrom(sockfd, buf, MAXLEN, 0,
           (struct sockaddr *) &clientaddr, &clientlen);
        if (n < 0)
        {
            error("ERROR in recvfrom");
        }

        /*
        * gethostbyaddr: determine who sent the datagram
        */
        hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
                sizeof(clientaddr.sin_addr.s_addr), AF_INET);
        if (hostp == NULL)
        {
            error("ERROR on gethostbyaddr");
        }
        hostaddrp = inet_ntoa(clientaddr.sin_addr);
        if (hostaddrp == NULL)
        {
            error("ERROR on inet_ntoa\n");
        }
        printf("server received datagram from %s (%s)\n", hostp->h_name, hostaddrp);
        printf("server received %d/%d bytes: %s\n", strlen(buf), n, buf);

        /*
        * sendto: echo the input back to the client
        */
        n = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *) &clientaddr, clientlen);
        if (n < 0)
        {
            error("ERROR in sendto");
        }
    }

    return NULL;
}

void server_stop()
{
    running = false;
}
