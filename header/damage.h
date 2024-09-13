#ifndef DAMAGE_H
#define DAMAGE_H

extern void dealDamage(OBJECT *attacker, OBJECT *weapon, OBJECT *victim);
extern OBJECT *getOptimalWeapon(OBJECT *attacker);

#endif