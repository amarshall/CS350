CC=gcc -std=c99 -Wall -pedantic-errors
BINARY=chat

all: chat

chat: main.c
	$(CC) main.c -o $(BINARY)

clean:
	rm -rf *.o $(BINARY)
