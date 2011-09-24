CC=gcc -std=c99 -Wall -g

BINARY=cs350sh
C_FILES=main.c io.c dispatch.c

all: $(C_FILES)
	$(CC) $(C_FILES) -o $(BINARY)

clean:
	rm -rf *.o *.dSYM $(BINARY)
