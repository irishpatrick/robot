#include "msgq.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int msgq_init(msgq* q)
{
    q->root = NULL;
    q->reserve = NULL;
    q->head_ptr = &q->root;
    return 0;
}

int msgq_reserve(msgq* q, uint32_t n)
{
    if (n < 1)
    {
        return 1;
    }

    q->reserve = malloc(sizeof(msgnode));
    if (!q->reserve)
    {
        return 1;
    }

    msgnode* cur = q->reserve;
    
    for (int i = 0; i < n - 1; ++i)
    {
        cur->next = malloc(sizeof(msgnode));
        if (!cur->next)
        {
            return 1;
        }
    }

    cur->next = NULL;

    return 0;
}

int bmsgq_init(bmsgq* q)
{
    msgq_init(&q->miso);
    msgq_init(&q->mosi);
    return 0;
}

void msgq_delete(msgq* q)
{
    msgnode* trash;

    while(q->root)
    {
        trash = q->root;
        q->root = q->root->next;
        free(trash);
    }
    
    while(q->reserve)
    {
        trash = q->reserve;
        q->reserve = q->reserve->next;
        free(trash);
    }
}

void bmsgq_delete(bmsgq* q)
{
    msgq_delete(&q->miso);
    msgq_delete(&q->mosi);
}

bool msgq_available(msgq* q)
{
    return q->root != NULL;
}

int msgq_push(msgq* q, void* data, uint32_t len)
{
    *q->head_ptr = malloc(sizeof(msgnode));
    if (!*q->head_ptr)
    {
        return 1;
    }

    msgnode* head = *q->head_ptr;

    head->next = NULL;
    head->msg = data;
    head->len = len;

    q->head_ptr = &head->next;

    return 0;
}

uint32_t msgq_top(msgq* q, void** dp)
{
    *dp = q->root->msg;
    return q->root->len;
}

void msgq_pop(msgq* q)
{
    msgnode* trash = q->root;
    q->root = q->root->next;
    free(trash);
}

