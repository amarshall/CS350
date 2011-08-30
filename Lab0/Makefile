GXX=gcc -Wall

all: fib

fib: main.o fib.o
	$(GXX) main.o fib.o -o fib

main.o: main.c
	$(GXX) -c main.c

fib.o: fib.h fib.c
	$(GXX) -c fib.c

clean:
	rm -rf *.o *~ core *.exe
