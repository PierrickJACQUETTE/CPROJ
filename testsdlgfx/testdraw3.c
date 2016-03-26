#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL2_gfxPrimitives.h>

int main()
{
   SDL_Window* window = nullptr;
   SDL_Renderer* renderer = nullptr;

   if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
   {
      std::cout << "Could not initialise" << std::endl;
      return 1;
   }

   window = SDL_CreateWindow("MyGame",
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             640,
                             480,
                             SDL_WINDOW_SHOWN);
   if(!window)
   {
      std::cout << "Could not create the window" << std::endl;
      return 1;
   }

   renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
   SDL_RenderClear(renderer);

   Sint16 circleR = 100;
   Sint16 circleX = 300;
   Sint16 circleY = 300;
   SDL_Surface* windowSurface = SDL_GetWindowSurface(window);
   Uint32 circleColour = SDL_MapRGB(windowSurface->format, 255, 0, 0);

   int result = filledCircleColor(renderer, circleX, circleY, circleR, circleColour);

   std::cout << "drawing the circle r " << circleR << " x " << circleX << " y " << circleY << " circleColour " << circleColour << std::endl;
   std::cout << "draw circle result " << result << std::endl;

   SDL_RenderPresent(renderer);

   bool run = true;
   while(run)
   {
      SDL_Event event;
      while (SDL_PollEvent(&event))
      {
         if(event.type == SDL_QUIT)
         {
            run = false;
         }
      }

   }

   SDL_Quit();
   return 0;
}
