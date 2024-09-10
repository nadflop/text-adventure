#ifndef NOUN_H
#define NOUN_H

extern OBJECT *getVisible(const char *intention, const char *noun);
extern OBJECT *getPossession(OBJECT *from, const char *verb, const char *noun);
extern OBJECT *getTopic(const char *noun);

#endif