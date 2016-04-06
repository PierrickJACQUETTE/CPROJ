#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SCREENW 1366
#define SCREENH 768

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool init_SDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n",SDL_GetError());
        return false;
    }
    window = SDL_CreateWindow("CPROJ",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,SCREENW,SCREENH,SDL_WINDOW_SHOWN);
    if(window == NULL) {
        printf("Window could not be created! SDL Error: %s\n",SDL_GetError());
        return false;
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n",SDL_GetError());
        return false;
    }
    if(SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF) < 0) {
        printf("Renderer color could not be set! SDL Error: %s\n",SDL_GetError());
        return false;
    }
    return true;
}

void close_SDL() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

void dessin(SDL_Renderer * screen){
 short s[9] = { 400, 450, 450, 425, 300, 421, 455, 420, 304 }; 
      short t[9] = { 400, 410, 450, 425, 500, 461, 415, 413, 504};

      filledPolygonRGBA(screen, 
                        s, t,
                        9,
                        255, 0, 255, 155);
}

int main(int argc,char *argv[]) {
    Sint16 topRightX = 100; 
    Sint16 topRightY = 100; 
    Sint16 bottomLeftX = 300;
    Sint16 bottomLeftY = 300; 
    Uint32 green = 0x00FF00FF;

    if(!init_SDL()) {
        exit(EXIT_FAILURE);
    }
    SDL_RenderClear(renderer);
	dessin(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    close_SDL();
    exit(EXIT_SUCCESS);
}
