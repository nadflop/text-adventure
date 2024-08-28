#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "header/object.h"
#include "header/misc.h"
#include "header/noun.h"
#include "header/match.h"

bool executeLookAround(void) {
   printf("You are in %s.\n", player->location->description);
   listObjectsAtLocation(player->location);
   return true;
}

bool executeLook(void) {
   OBJECT *obj = getVisible("what you want to look at", params[0]);
   switch (getDistance(player, obj))
   {
   case distHereContained:
      printf("Hard to see, try to get it first.\n");
      break;
   case distOverthere:
      printf("Too far away, move closer please.\n");
      break;
   case distNotHere:
      printf("You don't see any %s here.\n", params[0]);
      break;
   case distUnknownObject:
      // already handled by getVisible
      break;
   default:
      printf("%s\n", obj->details);
      listObjectsAtLocation(obj);
   }
   return true;
}

static void movePlayer(OBJECT *passage) {
   printf("%s\n", passage->textGo);
   if (passage->destination != NULL)
   {
      player->location = passage->destination;
      printf("\n");
      executeLookAround();
   }
}

bool executeGo(void) {
   OBJECT *obj = getVisible("where you want to go", params[0]);
   switch (getDistance(player, obj))
   {
   case distOverthere:
      movePlayer(getPassage(player->location, obj));
      break;
   case distNotHere:
      printf("You don't see any %s here.\n", params[0]);
      break;
   case distUnknownObject:
      // already handled by getVisible
      break;
   default:
      movePlayer(obj);
   }
   return true;
}
