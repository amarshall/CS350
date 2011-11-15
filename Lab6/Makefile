CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Werror -Wformat=2 -Wfloat-equal -Wshadow -Wwrite-strings -Winit-self -pedantic-errors
BINARY=signal_trap
SRC_FILES=main.c
.PHONY: clean

all: $(BINARY)

$(BINARY): $(SRC_FILES:%.c=%.o)
	@$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c %.h
	@$(CC) $(CFLAGS) -c $<

%.o: %.c
	@$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o *.dSYM *.plist $(BINARY)
