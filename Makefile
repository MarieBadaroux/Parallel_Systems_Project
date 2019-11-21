CC=gcc
CFLAGS=-Werror -Wall -std=c99 -g
LDFLAGS=
EXEC=puissance4

all: $(EXEC)

clean: 
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
