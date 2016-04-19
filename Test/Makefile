CC = gcc
CFLAGS = -Wall
LDFLAGS = $(CFLAGS)
LDLIBS =  $(shell pkg-config --libs check) -lSDL2_gfx `sdl2-config --cflags --libs`
EXEC 	  = check_main

all: $(EXEC)

check_main: check_main.o check_init.o ../conversionElements.o ../init.o ../delete.o ../Avl.o check_avl.o
check_init: check_init.o
check_avl:

clean:
	rm -f check_*.o

mrproper: clean
		rm -f $(EXEC)
		rm -f *.gch
