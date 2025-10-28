#ifndef POST_H
#define POST_H

#include "comment.h"

#define MAX_USERNAME_LENGTH 50
#define MAX_CAPTION_LENGTH 200

 struct post{
 char*username;
 char*caption;
 struct comment *comments;
 struct post* next;


 };

 struct post*createPost(char*username, char*caption);
 void freePost(struct post*p);





 #endif

 