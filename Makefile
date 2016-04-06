CC 	  = gcc
CFLAGS  = -Wall 
HFLAGS  = -Ilib
HXML 	  = `xml2-config --cflags`
LIBXML  = `xml2-config --libs`  
HSDL 	  = `sdl2-config --cflags`
LIBSDL  = `sdl2-config --libs` -lSDL2_gfx -lm

EXEC 	  = CPROJ

HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))


all: $(EXEC)


CPROJ: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBXML) $(LIBSDL)

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) $(HXML) $(HSDL) $(HFLAGS)


clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC)
	rm -f *.gch
