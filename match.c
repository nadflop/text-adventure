#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "header/object.h"
#include "header/misc.h"
#include "header/match.h"

const char *params[MAX_PARAMS];

static const char *skipSpaces(const char *src) {
    while (isspace(*src)) {
        src++;
    }
    return src;
}

//match a stretch of whitespaces, either between two words or posibly zero width at end of input string
//starts parsing at character pointed to by parameter src
static const char *matchSpaces(const char *src) {
    return *src == '\0' || isspace(*src) ? skipSpaces(src) : NULL;
}

//matches particular character, case-insensitive. if the required char is space, it'll try to match the space
static const char *matchTerminal(const char *src, char terminal) {
    return terminal == ' ' ? matchSpaces(src) : tolower(*src) == tolower(terminal) ? src + 1 : NULL;
}

//matches particular word, case-insensitive. if parameter atEnd is true, matching will only succeed if the word is last in input string
static const char *matchTag(const char *src, const char *tag, bool atEnd) {
    while (src != NULL && *tag != '\0') {
        src = matchTerminal(src, *tag++);
    }
    return atEnd && src != NULL && *skipSpaces(src) != '\0' ? NULL : src;
}

//matches and capture a nonterminal. will scan all tags to find the longest matching tag
//array pointed by par will be filled with pointer to the matching tag (if there is any)
//param loose is set to match a 'loose' nonterminal. if its true, it will consume the entire input string
static const char *matchParam(const char *src, const char **par, bool loose) {
    const char *restOfSrc = loose ? src + strlen(src) : NULL;
    OBJECT *obj;
    for (obj = objs; obj < endOfObjs; obj++) {
        const char **tag;
        for (tag = obj->tags; *tag != NULL; tag++) {
            const char *behindMatch = matchTag(src, *tag, loose);
            if (behindMatch != NULL && strlen(*tag) > strlen(*par)) {
                *par = *tag;
                restOfSrc = behindMatch;
            }
        }
    }
    if (**par == '\0') {
        *par = src;
    }
    return restOfSrc;
}

//matches an entire pattern, capturing nonterminals into array params
bool matchCommand(const char *src, const char *pattern) {
    const char **par;
    for (par = params; par < params + MAX_PARAMS; par++) {
        *par = "";
    }
    for (src = skipSpaces(src); src != NULL && *pattern != '\0'; pattern++) {
        src = isupper(*pattern) ? matchParam(src, paramByLetter(*pattern), pattern[1] == '\0') : matchTerminal(src, *pattern);
    }
    return src != NULL && *skipSpaces(src) == '\0';
}