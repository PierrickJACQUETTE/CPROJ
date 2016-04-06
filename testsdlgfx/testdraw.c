#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const char* WINDOW_TITLE = "SDL Start";

int main(int argc, char **argv)
{
	//SDL_Window* window = 0; // initiailisation de fenetre vide
  /*window = SDL_CreateWindow // creation fenetre
  (
    "CPROJ", SDL_WINDOWPOS_UNDEFINED, // nom
    SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH, WINDOW_HEIGHT, // taille
    SDL_WINDOW_SHOWN
  );
  renderer = NULL; // initialise le fond de la fenetre
  renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED); // met le fond
   */
   //SDL_Surface* screen = SDL_GetWindowSurface(window);
   /*SDL_Renderer* renderer = 0;

   SDL_Init( SDL_INIT_EVERYTHING );
   SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
   SDL_SetRenderDrawColor(renderer,100,100,100,255);
   SDL_RenderClear(renderer);
   SDL_RenderPresent(renderer);	*/
   

   SDL_Surface* screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, 
      SDL_SWSURFACE | SDL_DOUBLEBUF );
   SDL_WM_SetCaption( WINDOW_TITLE, 0 );
	
  //SDL_Event event;
   int i = 0;

   /*while (i == 0)
   {
      if (SDL_PollEvent(&event))
      {
         if (event.type == SDL_QUIT)
         {
            i = 1;
         }
      }*/

      /*pixelRGBA(screen, 
                10, 15, 
                255, 255, 255, 255);

      lineRGBA(screen, 
               20, 10,
               70, 90, 
               255, 0, 0, 255);

      trigonRGBA(screen,
                 500, 50,
                 550, 200, 
                 600, 150, 
                 0, 255, 255, 255);

      filledTrigonRGBA(screen,
                       200, 200,
                       300, 50,    
                       400, 200, 
                       0, 0, 255, 255);

      rectangleRGBA(screen, 
                    -10, 300, 
                    100, 380,
                    0, 255, 0, 255);

      boxRGBA(screen, 
              210, 76, 
              325, 300,
              255, 0, 0, 150);

      ellipseRGBA(screen,
                  600, 400,
                  50, 90,
                  255, 255, 0, 200);

      filledEllipseRGBA(screen,
                        600, 400,
                        25, 150,
                        0, 255, 0, 255);

      short x[6] = { 350, 275, 300, 325, 350, 400 }; 
      short y[6] = { 325, 325, 390, 390, 375, 300 };

      polygonRGBA(screen, 
                  x, y,
                  6,
                  255, 255, 255, 155);*/

      short s[9] = { 400, 450, 450, 425, 300, 421, 455, 420, 304 }; 
      short t[9] = { 400, 410, 450, 425, 500, 461, 415, 413, 504};

      filledPolygonRGBA(screen, 
                        s, t,
                        9,
                        255, 0, 255, 155);

      //SDL_Flip(screen);
		//SDL_RenderPresent(renderer);
   //}

  //SDL_Delay(6000);
  
  //SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

   return 0;
}
