#ifndef MSGQ_H
#define MSGQ_H

#include <stdint.h>
#include <stdbool.h>

typedef struct _msgnode
{
    struct _msgnode* next;
    void* msg;
    uint32_t len;
} msgnode;

typedef struct _msgq
{
    msgnode* root;
    msgnode* reserve;
    msgnode** head_ptr;
} msgq;

typedef struct _bmsgq
{
    msgq miso;
    msgq mosi;
} bmsgq;

int msgq_init(msgq*);
int msgq_reserve(msgq*, uint32_t);
int bmsgq_init(bmsgq*);
void msgq_delete(msgq*);
void bmsgq_delete(bmsgq*);
bool msgq_available(msgq*);
int msgq_push(msgq*, void*, uint32_t);
uint32_t msgq_top(msgq*, void**);
void msgq_pop(msgq*);
int msgq_push_str(msgq*, const char*);
const char* msgq_pop_str(msgq*);

#endif /* MSGQ_H */
