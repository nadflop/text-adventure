#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "header/object.h"
#include "header/misc.h"

static bool objectHasTag(OBJECT *obj, const char *noun) {
    if (noun != NULL && *noun != '\0') {
        const char **tag;
        for (tag = obj->tags; *tag != NULL; tag++) {
            if (strcmp(*tag, noun) == 0) return true;
        }
    }
    return false;
}

static OBJECT ambiguousNoun;

static OBJECT *getObject(const char *noun, OBJECT *from, DISTANCE maxDistance) {
    OBJECT *obj, *res = NULL;
    for (obj = objs; obj < endOfObjs; obj++) {
        if (objectHasTag(obj, noun) && getDistance(from, obj) <= maxDistance) {
            //if the tag is an ambigious tag which is non-unique, it's an ambiguousNoun
            res = res == NULL ? obj : &ambiguousNoun;
        }
    }
    return res;
}

OBJECT *getVisible(const char *intention, const char *noun) {
    //get objects only within the player's visible range
    OBJECT *obj = getObject(noun, player, distOverthere);
    if (obj == NULL) {
        if (getObject(noun, player, distNotHere) == NULL) {
            printf("I don't understand %s.\n", intention);
        }
        else {
            printf("You don't see any %s here.\n", intention);
        }
    }
    else if (obj == &ambiguousNoun) {
        printf("Please be specific about which %s you mean.\n", noun);
        obj = NULL;
    }
    return obj;
}

OBJECT *getPosession(OBJECT *from, const char *verb, const char *noun) {
    OBJECT *obj = NULL;
    if (from == NULL) {
        printf("I don't understand what you want to %s.\n", verb);
    }
    //get objects that is NOT being held by player (& is not the player itself)
    else if ((obj = getObject(noun, from, distHeldContained)) == NULL) {
        if (getObject(noun, player, distNotHere) == NULL) {
            printf("I don't understand what you want to %s.\n", verb);
        }
        else if (from == player) {
            printf("You are not holding any %s.\n", noun);
        }
        else {
            printf("There appears to be no %s you can get from %s.\n",
                    noun, from->description);
        }
    }
    else if (obj == &ambiguousNoun) {
        printf("Please be specific about which %s you mean.\n", noun);
        obj = NULL;
    }
    
    else if (obj == from) {
        printf("You should not be doing that to %s.\n", obj->description);
        obj = NULL;
    }
    return obj;
}