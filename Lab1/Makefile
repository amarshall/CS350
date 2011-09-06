CC=gcc -Wall
BINARY=outputsaver

all: $(BINARY)

$(BINARY): main.c
	$(CC) main.c -o $(BINARY)

clean:
	rm -rf *.o *~ core *.exe $(BINARY)
