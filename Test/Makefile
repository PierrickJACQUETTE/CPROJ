CC = gcc
CFLAGS = -Wall
LDFLAGS = $(CFLAGS)
LDLIBS =  $(shell pkg-config --libs check)
EXEC 	  = check_main

all: $(EXEC)

check_main: check_main.o init.o check_init.o ../Avl.o check_avl.o
check_init: check_init.o
check_avl: check_avl.o

clean:
	rm -f check_*.o

mrproper: clean
		rm -f $(EXEC)
		rm -f *.gch
