 # Simple Makefile for Task 2a - Social Media ADT

CC = gcc
CFLAGS = -Wall -g

OBJS = main.o platform.o post.o comment.o reply.o
TARGET = social_media

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c platform.h
	$(CC) $(CFLAGS) -c main.c

platform.o: platform.c platform.h post.h comment.h reply.h
	$(CC) $(CFLAGS) -c platform.c

post.o: post.c post.h
	$(CC) $(CFLAGS) -c post.c

comment.o: comment.c comment.h reply.h
	$(CC) $(CFLAGS) -c comment.c

reply.o: reply.c reply.h
	$(CC) $(CFLAGS) -c reply.c

clean:
	rm -f $(OBJS) $(TARGET)
