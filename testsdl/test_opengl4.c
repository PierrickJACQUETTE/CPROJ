#include "SDL.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>


/*
gcc fichier.c -o tutorial1 -lGL -lGLU `sdl2-config --cflags --libs`
)*/
#include <stdlib.h>
#include <GL/glu.h>

enum status {QUIT, CONTINUE};
#define COLOR_RUE 0,0,255
int heigth = 500;
int width = 500;

typedef struct Coordonnees{
	double latitude;
	double longitude;
} Coordonnees ;

void drawNoeud(float minHeight, float minWidth, float maxHeight, float maxWidth){

	int length = 10;
	Coordonnees *tab = malloc (length * sizeof (Coordonnees));
	int i;
//	for(i=0;i<length;i++){
		tab[0].latitude = -0.08;
		tab[0].longitude = 0.08;
		tab[1].latitude = -0.8;
		tab[1].longitude = 0.2;
		tab[2].latitude = 0.08;
		tab[2].longitude = 0.2;
		tab[3].latitude = -0.6;
		tab[3].longitude = 0.95;
		tab[4].latitude = 0.08;
		tab[4].longitude = -0.08;
		tab[5].latitude = -0.3;
		tab[5].longitude = 0.4;
		tab[6].latitude = -0.9;
		tab[6].longitude = 0.04;
		tab[7].latitude = -0.03;
		tab[7].longitude = 0.06;
		tab[8].latitude = -0.07;
		tab[8].longitude = 0.63;
		tab[9].latitude = -0.54;
		tab[9].longitude = 0.41;

//	}
	glColor3ub(COLOR_RUE);
	glBegin(GL_POLYGON);
	for(i=0;i<length;i++){
		glVertex2f(  0.0,  1.0); /* Top */
		glVertex2f( -1.0, -1.0); /* Bottom Left */
		glVertex2f(tab[i].latitude,tab[i].longitude);
		printf("p[%d] = (%lf, %lf)\n", i, tab[i].latitude, tab[i].longitude);
	}
	glEnd();//end drawing of polygon

}

void Display_Render( SDL_Renderer* displayRenderer)
{
	/* Set the background black */
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	/* Clear The Screen And The Depth Buffer */
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	drawNoeud(50,50,100,100);


	SDL_RenderPresent(displayRenderer);
}

void evenement(){
	enum status status = CONTINUE;
	do {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			switch (e.type) {
				case SDL_QUIT :
				printf("fermeture de la fenetre.\n");
				status = QUIT;
				break;

			}
		}
	}
	while (status != QUIT);
}

int main(int argc, char *argv[])
{

	heigth = 480;
	width = 600;

	SDL_Window* window = NULL;
	window = SDL_CreateWindow
	(
		"Test3", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, heigth,
		SDL_WINDOW_SHOWN
	);
	SDL_Renderer* renderer = NULL;
	renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

	Display_Render(renderer);

	evenement();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
