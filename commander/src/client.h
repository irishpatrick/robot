#ifndef CLIENT_H
#define CLIENT_H

#include "packet.h"

#include <pthread.h>

typedef struct _client
{
    pthread_t thread;
    pthread_mutex_t comm_mutex;
    robot_pkt pkt_from[100];
    commander_pkt pkt_to[100];
} client;

int client_init(client*);
void client_start(client*);
void client_join(client*);
void* client_main(void*);

#endif /* CLIENT_H */
