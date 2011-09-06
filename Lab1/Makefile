CC=cc -Wall -std=c99
BINARY=outputsaver

all: $(BINARY)

$(BINARY): main.c
	$(CC) main.c -o $(BINARY)

clean:
	rm -rf *.o *~ core *.exe $(BINARY)
