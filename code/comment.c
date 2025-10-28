 #include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "comment.h"
#include "reply.h" 

static char* string_allocation(const char*s){
    if(!s){
        return NULL;
    }
     
    char *d = malloc(strlen(s) +1);
    if(d){
        strcpy(d, s);
    }
    return d;
}


// create comment function

struct comment* createComment(char*username, char* content){
    struct comment*c = malloc(sizeof(struct comment));
    if(!c){
        return NULL;
    }
    c->username =string_allocation(username);
    c->content = string_allocation(content);
    c->replies = NULL;
    c->next = NULL;
    
    
    if (!c->username || !c->content) {
        if (c->username) free(c->username);
        if (c->content) free(c->content);
        free(c);
        return NULL;
    }
    
    return c;
}

//delete comment

void freeComment(struct comment*c){
    if(!c) return;
    
     
    if(c->username) free(c->username);
    if(c->content) free(c->content);
    
    // Free all the replies
    struct reply*r =  c->replies;
    while(r){
        struct reply*rn = r->next;
        freeReply(r);
        r = rn;
    }
   
    free(c);
}