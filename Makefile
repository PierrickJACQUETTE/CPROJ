CC=gcc
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c)) 
EXEC=XML SDL
Exe= ./a.out ./tutorial

all: $(EXEC)

XML: *.c
	$(CC) $^ `xml2-config --cflags --libs` 

SDL: *sdl.c
	$(CC) $^ -o tutorial1 -lGL -lGLU `sdl2-config --cflags --libs` 

#%.o: %.c $(HEADERS)
#	$(CC) -c $^

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(Exe)


