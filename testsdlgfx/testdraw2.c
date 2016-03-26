#include<SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include<stdio.h>
 

const int WIDTH  = 640;
const int HEIGHT = 480;
 
 
void dessin(SDL_Renderer * ren) 
{
  Uint8 r,g,b,a;
  Sint16 x,y,rx,ry;
  int n;
 
  for(n=0;n<50;n++)
	 {
		x = rand()%WIDTH;
		y = rand()%HEIGHT;
		rx = rand()%30+10;
		ry = rand()%30+10;
		r = rand()%256;
		g = rand()%256;
		b = rand()%256;
		a = rand()%256;
		filledEllipseRGBA(ren,x,y,rx,ry,r,g,b,a);
	 }
  SDL_RenderPresent(ren);
 
}

int main(int argc, char** argv)
{
  SDL_Window *win = 0;
  SDL_Renderer *ren = 0;
 
  /* Initialisation de la SDL. Si ça se passe mal, on quitte */
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
      fprintf(stderr,"Erreur initialisation\n");
      return -1;
  }
  /* Création de la fenêtre et du renderer */
  SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren); // SDL_WINDOW_SHOWN|SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC,&win,&ren);
 
  if (!win || !ren) 
	 {
		fprintf(stderr,"Erreur à la création des fenêtres\n");
		SDL_Quit();
		return -1;
	 }
  /* Affichage du fond noir */
  SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
  SDL_RenderClear(ren);
  SDL_RenderPresent(ren);
 
dessin(ren) ;
  SDL_Delay(4000);
 
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}


