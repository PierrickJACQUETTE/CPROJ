CC = gcc
CFLAGS = -Wall -lm -lGL -lGLU -lSDL -lSDL_gfx `sdl2-config --cflags --libs` `xml2-config --cflags --libs`
EXEC = CPROJ
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c))

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(HEADERS)
	$(CC) -c $^ $(CFLAGS)

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(EXEC)
	rm -f *.gch
