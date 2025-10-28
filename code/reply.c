#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "reply.h"

// reply memory allocation

static char* string_allocation(const char*s){
    if(!s){
        return NULL;
    }
    char *d = malloc(strlen(s) + 1);
     if(d){
        strcpy(d, s);
     }
     return d;
}

//create reply

struct reply* createReply(char*username, char*content){
    struct reply*r = malloc(sizeof(struct reply));
    if(!r) return NULL;
    
    r->username = string_allocation(username);
    r->content = string_allocation(content);
    r->next = NULL;
    
     
    if (!r->username || !r->content) {
        if (r->username) free(r->username);
        if (r->content) free(r->content);
        free(r);
        return NULL;
    }
    
    
    return r; 
}

// delete reply

void freeReply(struct reply*r){
    if(!r)return;
    if(r->username)free(r->username);
    if(r->content)free(r->content);
    free(r);
}