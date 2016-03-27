#include "graphic.h"

enum status {QUIT, CONTINUE};
int heigth = 600; // taille fenetre par défaut
int width = 800;
SDL_Renderer* renderer;
SDL_Window *window;

int init_SDL() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n",SDL_GetError());
    return 0;
  }
  window = SDL_CreateWindow("CPROJ",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,width,heigth,SDL_WINDOW_SHOWN);
  if(window == NULL) {
    printf("Window could not be created! SDL Error: %s\n",SDL_GetError());
    return 0;
  }
  renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
  if(renderer == NULL) {
    printf("Renderer could not be created! SDL Error: %s\n",SDL_GetError());
    return 0;
  }
  if(SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF) < 0) {
    printf("Renderer color could not be set! SDL Error: %s\n",SDL_GetError());
    return 0;
  }
  return 1;
}

void close_SDL() {
  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;
  SDL_Quit();
}

void evenement(){
  enum status status = CONTINUE; // enumeration de statuts == while infini
  do {
    SDL_Event e;
    if (SDL_PollEvent(&e)) { // detecte si il y a un even
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

void printMap(Map* map,char* typeOfDessin){
  if(init_SDL()==0) {
    exit(EXIT_FAILURE);
  }
  SDL_RenderClear(renderer);
  if(strcmp(typeOfDessin,"point")==0){
    parcoursAvl(&(map->avl),map->bounds,width,heigth,renderer);
  }
  else if(strcmp(typeOfDessin,"line")==0){
    parcoursListWay(map,width,heigth,renderer);
  }
  else{
    printf("Le deuxieme argument est inconnu %s\n", typeOfDessin);
  }
  SDL_RenderPresent(renderer);
  evenement();
  close_SDL();
  exit(EXIT_SUCCESS);

}
