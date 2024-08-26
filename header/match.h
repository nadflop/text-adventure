#ifndef MATCH_H
#define MATCH_H

#define MAX_PARAMS  26

extern const char *params[];

#define paramByLetter(letter)   (params + (letter) - 'A')

extern bool matchCommand(const char *src, const char *pattern);

#endif