CC=gcc
CFLAGS=-lrt -std=c99 -Wall -Wextra -Wformat=2 -Wfloat-equal -Wshadow -Wwrite-strings -Winit-self -pedantic-errors
.PHONY: clean

all: PartA PartB

PartA: PartA.c
	@$(CC) $(CFLAGS) $^ -o $@

PartB: PartB.c
	@$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o *.dSYM *.plist PartA PartB
