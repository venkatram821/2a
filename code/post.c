 #include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "post.h"
#include "comment.h"

 
#define MAX_USERNAME_LENGTH 50
#define MAX_CAPTION_LENGTH 200
 
static char* string_allocation(const char* s, size_t max_length) {
    if (!s || strlen(s) > max_length) {
        return NULL;
    }
    char* d = malloc(strlen(s) + 1);
    if (d) {
        strcpy(d, s);
    }
    return d;
}

// fun to create post
struct post* createPost(char* username, char* caption) {
    if (!username || !caption) {
        return NULL;
    }

    struct post* p = malloc(sizeof(struct post));
    if (!p) {
        return NULL;
    }

    p->username = string_allocation(username, MAX_USERNAME_LENGTH);
    if (!p->username) {
        free(p);
        return NULL;
    }

    p->caption = string_allocation(caption, MAX_CAPTION_LENGTH);
    if (!p->caption) {
        free(p->username);
        free(p);
        return NULL;
    }

    p->comments = NULL;
    p->next = NULL;
    return p;
}


// fun to delete post

void freePost(struct post*p){
    if(!p) return;

    if(p->username) free(p->username);
    if(p->caption) free(p->caption);

    // Free all comments
    struct comment*c = p->comments;
    while(c){
        struct comment*cn = c->next;
        freeComment(c);
        c = cn;
    }
    
    
    free(p);
}