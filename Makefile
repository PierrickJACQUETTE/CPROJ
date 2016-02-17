CC=gcc
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c)) 
EXEC=XML SDL
Exe= ./XML ./SDL

all: $(EXEC)

XML: *.c
	$(CC) $^ -o XML `xml2-config --cflags --libs`

SDL: *sdl.c
	$(CC) $^ -o SDL -lGL -lGLU `sdl2-config --cflags --libs` 

#%.o: %.c $(HEADERS)
#	$(CC) -c $^

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(Exe)


