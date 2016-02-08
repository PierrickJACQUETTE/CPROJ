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

void test(){   glBegin( GL_TRIANGLES );            /* Drawing Using Triangles */
      glVertex2f(  0.0,  1.0); /* Top */
      glVertex2f( -1.0, -1.0); /* Bottom Left */
      glVertex2f(  1.0, -1.0); /* Bottom Right */
    glEnd( );                           /* Finished Drawing The Triangle */



	glColor3ub(0, 0, 255); // on demande du bleu
    glBegin(GL_POLYGON);//begin drawing of polygon
      glVertex2f(-0.5,0.5);//first vertex
      glVertex2f(0.5,0.5);//second vertex
      glVertex2f(1.0,0.0);//third vertex
      glVertex2f(0.5,-0.5);//fourth vertex
      glVertex2f(-0.5,-0.5);//fifth vertex
      glVertex2f(-1.0,0.0);//sixth vertex
    glEnd();//end drawing of polygon
} 

void Display_Render( SDL_Renderer* displayRenderer)
{
    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    /* Clear The Screen And The Depth Buffer */
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	test();


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

	int heigth = 480;
	int width = 600; 

    SDL_Window* window = NULL;
    window = SDL_CreateWindow
    (
        "Jeu de la vie", SDL_WINDOWPOS_UNDEFINED,
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
