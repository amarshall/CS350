CC=gcc -std=c99 -Wall -g

BINARY=cs350sh

all: $(BINARY)

$(BINARY): main.o io.o
	$(CC) main.o io.o -o $(BINARY)

main.c:
	$(CC) main.c

io.c: io.h
	$(CC) io.c

clean:
	rm -rf *.o $(BINARY)
