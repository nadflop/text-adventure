#include <stdbool.h>
#include <stdio.h>
#include "header/object.h"
#include "header/misc.h"
#include "header/noun.h"
#include "header/move.h"

void executeGet(const char *noun) {
    OBJECT *obj = getVisible("what you want to get", noun);
    switch (getDistance(player, obj))
    {
    case distSelf:
        printf("You should not be doing that to yourself.\n");
        break;
    case distHeld:
        printf("You already have %s.\n", obj->description);
        break;
    case distOverthere:
        printf("Too far away, move closer please.\n");
        break;
    case distUnknownObject:
        //already handled by getVisible
        break;
    default:
        //the object is being held by someone else
        if (obj->location == guard) {
            printf("You should ask %s nicely.\n", obj->location->description);
        }
        //the object is not in possession of anyone, so player can have it
        else { 
            moveObject(obj,player);
        }
        break;
    }
}

void executeDrop(const char *noun) {
    moveObject(getPosession(player, "drop", noun), player->location);
}

void executeAsk(const char *noun) {
    moveObject(getPosession(actorHere(), "ask", noun), player);
}

void executeGive(const char *noun) {
    moveObject(getPosession(player, "give", noun), actorHere());
}

void executeInventory() {
    if (listObjectsAtLocation(player) == 0) {
        printf("You are empty-handed.\n");
    }
}