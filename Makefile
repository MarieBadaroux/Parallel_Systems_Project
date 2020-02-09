CC=gcc
CFLAGS=-Werror -Wall -Wextra -std=c99 -g
LDFLAGS=
EXEC=puissance4

all: $(EXEC)

puissance4: puissance4.o minmax.o
	$(CC) -o puissance4 puissance4.o minmax.o $(LDFLAGS)

puissance4.o: puissance4.c
	$(CC) -o puissance4.o -c puissance4.c $(CFLAGS)

minmax.o: minmax.c puissance4.h
	$(CC) -o minmax.o -c minmax.c $(CFLAGS)

clean: 
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
