CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror -Wformat=2 -Wfloat-equal -Wshadow -Wwrite-strings -Winit-self -Wmissing-declarations -pedantic-errors
BINARY=chat
SRC_FILES=main.c
.PHONY: clean

RELEASE ?= 0
ifeq ($(RELEASE), 1)
    CFLAGS+=-O2
else
    CFLAGS+=-O -g
endif

all: $(BINARY)

$(BINARY): $(SRC_FILES:%.c=%.o)
	@$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c %.h
	@$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o $(BINARY)
