CC=gcc
CFLAGS=-Wall -lm `xml2-config --cflags --libs` `sdl2-config --cflags --libs`
HEADERS = $(wildcard *.h)
OBJECTS = $(patsubst %.c, %.o, $(wildcard *.c)) 
EXEC=conversionElements Avl parseur
Exe= projet conversionElements Avl parseur

all: $(EXEC)

#main: parseur.o Avl.o conversionElements.o main.o
#	$(CC) -o projet conversionElements.o main.o

conversionElements.o: conversionElements.c conversionElements.h
	$(CC) -o conversionElements.o -c conversionElements.c $(CFLAGS)

conversionElements:conversionElements.o
	$(CC) -o conversionElements conversionElements.o $(CFLAGS)

Avl.o: Avl.c Avl.h
	$(CC) -o Avl.o -c Avl.c $(CFLAGS)

Avl:Avl.o
	$(CC) -o Avl Avl.o $(CFLAGS)

parseur.o: parseur.c parseur.h

	$(CC) -o parseur.o -c parseur.c $(CFLAGS)

parseur: parseur.o
	$(CC) -o parseur parseur.o $(CFLAGS)

#%.o: %.c $(HEADERS)
#	$(CC) -c $^

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -f $(Exe)
	rm -f *.gch


