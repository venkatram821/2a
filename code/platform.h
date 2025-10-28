 #ifndef PLATFORM_H
#define PLATFORM_H
#include <stdbool.h>
#include "post.h"
#include "comment.h"
#include "reply.h"

// Node to store view history
struct viewedNode {
    struct post *post;                
    struct viewedNode *next;
};

// Main platform structure
struct platform {
    struct post *p;                 // head of all posts
    struct post *lastViewedPost;    // last viewed post
    struct viewedNode *viewHistory; // linked list of viewed posts
};

// Function declarations
struct platform* createPlatform();

bool addPost(char *username, char *caption);
bool deletePost(int n);

struct post* viewPost(int n);
struct post* currPost();
struct post* nextPost();
struct post* previousPost();

bool addComment(char *username, char *content);
bool deleteComment(int n);
struct comment* viewComment();

bool addReply(char *username, char *content, int n);
bool deleteReply(int n, int m);

void showViewedHistory();
void freePlatform();

#endif
