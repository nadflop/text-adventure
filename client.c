#include <stdbool.h>
#include <stdio.h>
#include "header/object.h"
#include "header/telnet.h"
#include "header/client.h"

#define MAX_CLIENTS 30

static CLIENT clients[MAX_CLIENTS];

void clientInit(void) {
    int i;
    for (i = 0; i < MAX_CLIENTS; i++) clients[i].fd = -1;
}

//find existing clients
CLIENT *clientGet(int i) {
    return i < MAX_CLIENTS ? clients + i : NULL;
}

//find a free slot. if all slots are taken, return NULL
CLIENT *clientGetFree(void) {
    CLIENT *client;
    int i;
    for (i = 0; (client = clientGet(i)) != NULL && client->fd != -1; i++);
    return client;
}