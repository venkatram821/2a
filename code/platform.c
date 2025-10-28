 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "platform.h"
#include "post.h"
#include "comment.h"
#include "reply.h"

// global platform instance
struct platform platform_instance;

// initialize platform
struct platform* createPlatform() {
    platform_instance.p = NULL;
    platform_instance.lastViewedPost = NULL;
    platform_instance.viewHistory = NULL;
    return &platform_instance;
}

// add new post
bool addPost(char *username, char *caption) {
    struct post *p = createPost(username, caption);
    if (!p) return false;

    // add new post at head
    p->next = platform_instance.p;
    platform_instance.p = p;

    if (!platform_instance.lastViewedPost)
        platform_instance.lastViewedPost = p;

    return true;
}

// helper to get nth post
static struct post* getpostByIndex(int n, struct post **previous) {
    if (n <= 0) return NULL;

    struct post *cur = platform_instance.p;
    struct post *prev = NULL;
    int index = 1;

    while (cur && index < n) {
        prev = cur;
        cur = cur->next;
        index++;
    }

    if (previous)
        *previous = prev;
    return cur;
}

// view a specific post and record it in history
struct post* viewPost(int n) {
    struct post *p = getpostByIndex(n, NULL);
    if (!p) return NULL;

    platform_instance.lastViewedPost = p;

    // record viewed post in history
    struct viewedNode *node = malloc(sizeof(struct viewedNode));
    if (node) {
        node->post = p;
        node->next = platform_instance.viewHistory;
        platform_instance.viewHistory = node;
    }

    return p;
}

// return current viewed post
struct post* currPost() {
    return platform_instance.lastViewedPost;
}

// move to next (less recent) post
struct post* nextPost() {
    struct post *cur = platform_instance.lastViewedPost;
    if (!cur) return NULL;

    platform_instance.lastViewedPost = cur->next;

    if (!platform_instance.lastViewedPost)
        return NULL;
    return platform_instance.lastViewedPost;
}

// move to previous (more recent) post
struct post* previousPost() {
    struct post *cur = platform_instance.lastViewedPost;
    if (!cur || cur == platform_instance.p)
        return NULL;

    struct post *prev = platform_instance.p;
    while (prev && prev->next != cur)
        prev = prev->next;

    if (prev) {
        platform_instance.lastViewedPost = prev;
        return prev;
    }
    return NULL;
}

// delete post
bool deletePost(int n) {
    struct post *prev = NULL;
    struct post *p = getpostByIndex(n, &prev);
    if (!p) return false;

    // if deleted post is the currently viewed one
    if (platform_instance.lastViewedPost == p) {
        struct viewedNode *vh = platform_instance.viewHistory;
        struct post *newLast = NULL;

        while (vh) {
            if (vh->post && vh->post != p) {
                // check if this post still exists in platform list
                struct post *tmp = platform_instance.p;
                while (tmp) {
                    if (tmp == vh->post) {
                        newLast = vh->post;
                        break;
                    }
                    tmp = tmp->next;
                }
                if (newLast) break;
            }
            vh = vh->next;
        }

        platform_instance.lastViewedPost = newLast;
    }

    // unlink post
    if (prev)
        prev->next = p->next;
    else
        platform_instance.p = p->next;

    freePost(p);
    return true;
}

// add comment to current post
bool addComment(char *username, char *content) {
    struct post *p = currPost();
    if (!p) return false;

    struct comment *c = createComment(username, content);
    if (!c) return false;

    c->next = p->comments;
    p->comments = c;
    return true;
}

// delete comment from current post
bool deleteComment(int n) {
    struct post *p = currPost();
    if (!p || !p->comments) return false;

    int total = 0;
    struct comment *x = p->comments;
    while (x) { total++; x = x->next; }

    if (n <= 0 || n > total) return false;

    int target = total - n + 1;
    struct comment *cur = p->comments;
    struct comment *prev = NULL;
    int i = 1;

    while (cur && i < target) {
        prev = cur;
        cur = cur->next;
        i++;
    }

    if (!cur) return false;

    if (prev)
        prev->next = cur->next;
    else
        p->comments = cur->next;

    freeComment(cur);
    return true;
}

// view all comments of current post
struct comment* viewComment() {
    struct post *p = currPost();
    if (!p) return NULL;
    return p->comments;
}

// add reply to nth recent comment
bool addReply(char *username, char *content, int n) {
    struct post *p = currPost();
    if (!p || !p->comments) return false;

    int countC = 0;
    struct comment *x = p->comments;
    while (x) { countC++; x = x->next; }

    if (n <= 0 || n > countC) return false;
    int target = countC - n + 1;

    struct comment *cur = p->comments;
    int i = 1;
    while (cur && i < target) { cur = cur->next; i++; }

    if (!cur) return false;

    struct reply *r = createReply(username, content);
    if (!r) return false;

    r->next = cur->replies;
    cur->replies = r;
    return true;
}

// delete reply
bool deleteReply(int n, int m) {
    struct post *p = currPost();
    if (!p || !p->comments) return false;

    int countC = 0;
    struct comment *x = p->comments;
    while (x) { countC++; x = x->next; }

    if (n <= 0 || n > countC) return false;
    int targetC = countC - n + 1;

    struct comment *cur = p->comments;
    int i = 1;
    while (cur && i < targetC) { cur = cur->next; i++; }

    if (!cur || !cur->replies) return false;

    int countR = 0;
    struct reply *r = cur->replies;
    while (r) { countR++; r = r->next; }

    if (m <= 0 || m > countR) return false;
    int targetR = countR - m + 1;

    struct reply *prevR = NULL;
    struct reply *r2 = cur->replies;
    int j = 1;
    while (r2 && j < targetR) { prevR = r2; r2 = r2->next; j++; }

    if (!r2) return false;

    if (prevR)
        prevR->next = r2->next;
    else
        cur->replies = r2->next;

    freeReply(r2);
    return true;
}

// show all viewed posts history
void showViewedHistory() {
    struct viewedNode *cur = platform_instance.viewHistory;
    int i = 1;

    if (!cur) {
        printf("No viewed post history.\n");
        return;
    }

    printf("=== Viewed Post History ===\n");
    while (cur) {
        if (cur->post)
            printf("%d. %s - %s\n", i, cur->post->username, cur->post->caption);
        else
            printf("%d. [Deleted Post]\n", i);
        cur = cur->next;
        i++;
    }
    printf("===========================\n");
}

// free platform memory
void freePlatform() {
    struct post *p = platform_instance.p;
    while (p) {
        struct post *pn = p->next;
        freePost(p);
        p = pn;
    }

    struct viewedNode *vh = platform_instance.viewHistory;
    while (vh) {
        struct viewedNode *vn = vh->next;
        free(vh);
        vh = vn;
    }

    platform_instance.p = NULL;
    platform_instance.lastViewedPost = NULL;
    platform_instance.viewHistory = NULL;
}
