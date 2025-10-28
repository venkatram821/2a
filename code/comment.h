#ifndef COMMENT_H
#define COMMENT_H

#include "reply.h"

struct comment{
char*username;
char*content;
struct reply*replies;
struct comment *next;

};


struct comment* createComment(char*username, char*content);

void freeComment(struct comment*c);



#endif