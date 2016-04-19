CC = gcc
CFLAGS = -Wall
LDFLAGS = $(CFLAGS)
LDLIBS =  $(shell pkg-config --libs check) -lSDL2_gfx `sdl2-config --cflags --libs`
EXEC 	  = check_main

all: $(EXEC)

check_main: check_main.o ../conversionElements.o ../init.o ../delete.o ../Avl.o check_avl.o check_init.o check_fixture.o check_conversionElements.o
check_init:
check_fixture:
check_avl:
check_conversionElements:

clean:
	rm -f check_*.o

mrproper: clean
		rm -f $(EXEC)
		rm -f *.gch
