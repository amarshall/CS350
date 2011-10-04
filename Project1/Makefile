CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror -Wformat=2 -Wfloat-equal -Wshadow -Wwrite-strings -Winit-self -Wmissing-declarations -pedantic-errors # -Winline -Wpadded
BINARY=cs350sh
SRC_FILES=io.c dispatch.c main.c
.PHONY: clean

RELEASE ?= 0
ifeq ($(RELEASE), 1)
    CFLAGS+=-O2
else
    CFLAGS+=-g
endif

all: $(BINARY)

$(BINARY): $(SRC_FILES:%.c=%.o)
	@$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c %.h
	@$(CC) $(CFLAGS) -c $<

%.o: %.c
	@$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o *.dSYM $(BINARY)
