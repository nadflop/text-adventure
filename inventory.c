#include <stdbool.h>
#include <stdio.h>
#include "header/object.h"
#include "header/misc.h"
#include "header/noun.h"
#include "header/move.h"
#include "header/match.h"

bool executeGet(void) {
    OBJECT *obj = getVisible("what you want to get", params[0]);
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
            if (obj->location != NULL && obj->location->health > 0) {
                printf("You should ask %s nicely.\n", obj->location->description);
            }
            //the object is not in possession of anyone, so player can have it
            else { 
                moveObject(obj,player);
            }
    }
    return true;
}

bool executeDrop(void) {
    moveObject(getPossession(player, "drop", params[0]), player->location);
    return true;
}

bool executeAsk(void) {
    moveObject(getPossession(actorHere(), "ask", params[0]), player);
    return true;
}

bool executeGive(void) {
    moveObject(getPossession(player, "give", params[0]), actorHere());
    return true;
}

bool executeInventory(void) {
    if (listObjectsAtLocation(player) == 0) {
        printf("You are empty-handed.\n");
    }
    return true;
}