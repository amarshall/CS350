CC=gcc -std=c99 -Wall -O -pedantic-errors

BINARY=cs350sh
O_FILES=io.o dispatch.o main.o

all: $(BINARY)
	
$(BINARY): $(O_FILES)
	$(CC) $(O_FILES) -o $(BINARY)

main.o: main.c
	$(CC) -c main.c

dispatch.o: dispatch.c dispatch.h
	$(CC) -c dispatch.c

io.o: io.c io.h
	$(CC) -c io.c

clean:
	rm -rf *.o *.dSYM $(BINARY)
