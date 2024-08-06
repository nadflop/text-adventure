#ifndef NOUN_H
#define NOUN_H

extern OBJECT *getVisible(const char *intention, const char *noun);
extern OBJECT *getPosession(OBJECT *from, const char *verb, const char *noun);

#endif