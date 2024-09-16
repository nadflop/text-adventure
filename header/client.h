#ifndef CLIENT_H
#define CLIENT_H

typedef struct {
    int fd;
    OBJECT *obj;
    INBUF inbuf;
} CLIENT;

extern void clientInit(void);
extern CLIENT *clientGet(int i);
extern CLIENT *clientGetFree(void);

#endif