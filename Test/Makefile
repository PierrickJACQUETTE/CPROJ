CC = gcc
CFLAGS = -Wall
LDFLAGS = $(CFLAGS)
LDLIBS =  $(shell pkg-config --libs check)

all: check_main

check_main: check_main.o init.o check_init.o 
check_init: check_init.o

clean:
	rm -f check_*.o
