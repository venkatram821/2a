#ifndef REPLY_H
#define REPLY_H



struct reply{
char *username;
char*content;
struct reply*next;
};


// functions in reply
struct reply*createReply(char* username, char* content);

void freeReply(struct reply*r);


#endif