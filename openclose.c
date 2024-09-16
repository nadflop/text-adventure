#include <stdbool.h>
#include <stdio.h>
#include "header/object.h"
#include "header/reach.h"
#include "header/match.h"

int executeOpen(void) {
    OBJECT *obj = reachableObject("what you want to open", params[0]);
    if (obj != NULL) {
        (*obj->open)();
    }
    return 0;
}

int executeClose(void) {
    OBJECT *obj = reachableObject("what you want to close", params[0]);
    if (obj != NULL) {
        (*obj->close)();
    }
    return 0;
}

int executeLock(void) {
    OBJECT *obj = reachableObject("what you want to lock", params[0]);
    if (obj != NULL) {
        (*obj->lock)();
    }
    return 0;
}

int executeUnlock(void) {
    OBJECT *obj = reachableObject("what you want to unlock", params[0]);
    if (obj != NULL) {
        (*obj->unlock)();
    }
    return 0;
}