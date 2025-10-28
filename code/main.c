 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "platform.h"

#define MAXLEN 200

int main()
{
    createPlatform();   // initialize global platform once

    printf("=Simple Social Media CLI =\n");
    printf("the following are the Commands:\n");
    printf(" create_platform\n add_post <user> <caption>\n view_post <n>\n delete_post <n>\n");
    printf(" add_comment <user> <content>\n view_comments\n delete_comment <n>\n");
    printf(" next_post / previous_post / current_post\n");
    printf(" add_reply <user> <content> <commentNo>\n delete_reply <commentNo> <replyNo>\n");
    printf(" view_history\n exit\n");
    printf("=================================\n\n");

    char cmd[50];
    char user[MAX_USERNAME_LENGTH + 1];
    char content[MAXLEN + 1];
    int n, m;

    while (1)
    {
        printf("> ");
        if (scanf("%s", cmd) != 1)
            break;

        // exit
        if (strcmp(cmd, "exit") == 0)
        {
            printf("Exiting form platform...\n");
            break;
        }

        // create_platform
        else if (strcmp(cmd, "create_platform") == 0)
        {
            createPlatform();
            printf("Platform created successfully.\n");
        }

        // add_post
        else if (strcmp(cmd, "add_post") == 0)
        {
            if (scanf("%s %s", user, content) == 2)
            {
                if (addPost(user, content))
                    printf("Post added by %s.\n", user);
                else
                    printf("Failed to add post.\n");
            }
            else
                printf("Usage: add_post <user> <caption>\n");
        }

        // view_post
        else if (strcmp(cmd, "view_post") == 0)
        {
            if (scanf("%d", &n) == 1)
            {
                struct post *p = viewPost(n);
                if (p)
                    printf("%s %s\n", p->username, p->caption);
                else
                    printf("Post %d does not exist.\n", n);
            }
            else
                printf("Usage: view_post <n>\n");
        }

        // delete_post
        else if (strcmp(cmd, "delete_post") == 0)
        {
            if (scanf("%d", &n) == 1)
            {
                if (deletePost(n))
                    printf("Post %d deleted.\n", n);
                else
                    printf("Failed to delete post %d.\n", n);
            }
            else
                printf("Usage: delete_post <n>\n");
        }

        // current_post
        else if (strcmp(cmd, "current_post") == 0)
        {
            struct post *p = currPost();
            if (p)
                printf("%s %s\n", p->username, p->caption);
            else
                printf("No post currently viewed.\n");
        }

        // previous_post
        else if (strcmp(cmd, "previous_post") == 0)
        {
            struct post *p = previousPost();
            if (p)
                printf("%s %s\n", p->username, p->caption);
            else
                printf("Previous post does not exist.\n");
        }

        // next_post
        else if (strcmp(cmd, "next_post") == 0)
        {
            struct post *p = nextPost();
            if (p)
                printf("%s %s\n", p->username, p->caption);
            else
                printf("Next post does not exist.\n");
        }

        // add_comment
        else if (strcmp(cmd, "add_comment") == 0)
        {
            if (scanf("%s %s", user, content) == 2)
            {
                if (addComment(user, content))
                    printf("Comment added by %s.\n", user);
                else
                    printf("Failed to add comment. Is a post viewed?\n");
            }
            else
                printf("Usage: add_comment <user> <content>\n");
        }

        // view_comments
        else if (strcmp(cmd, "view_comments") == 0 || strcmp(cmd, "view_all_comments") == 0)
        {
            struct post *p = currPost();
            if (!p)
            {
                printf("No post currently viewed.\n");
                continue;
            }

            struct comment *c = viewComment();
            int ci = 1;
            while (c)
            {
                printf("%s %s\n", c->username, c->content);
                struct reply *r = c->replies;
                while (r)
                {
                    printf("%s %s\n", r->username, r->content);
                    r = r->next;
                }
                c = c->next;
                ci++;
            }
        }

        // delete_comment
        else if (strcmp(cmd, "delete_comment") == 0)
        {
            if (scanf("%d", &n) == 1)
            {
                if (deleteComment(n))
                    printf("Comment %d deleted.\n", n);
                else
                    printf("Failed to delete comment %d.\n", n);
            }
            else
                printf("Usage: delete_comment <n>\n");
        }

        // add_reply
        else if (strcmp(cmd, "add_reply") == 0)
        {
            if (scanf("%s %s %d", user, content, &n) == 3)
            {
                if (addReply(user, content, n))
                    printf("Reply added by %s to comment %d.\n", user, n);
                else
                    printf("Failed to add reply.\n");
            }
            else
                printf("Usage: add_reply <user> <content> <commentNo>\n");
        }

        // delete_reply
        else if (strcmp(cmd, "delete_reply") == 0)
        {
            if (scanf("%d %d", &n, &m) == 2)
            {
                if (deleteReply(n, m))
                    printf("Reply %d to comment %d deleted.\n", m, n);
                else
                    printf("Failed to delete reply.\n");
            }
            else
                printf("Usage: delete_reply <commentNo> <replyNo>\n");
        }

        // view_history (optional)
        else if (strcmp(cmd, "view_history") == 0)
        {
            showViewedHistory();
        }

        else
        {
            printf("Unknown command: %s\n", cmd);
        }
    }
    freePlatform();

    return 0;
}
