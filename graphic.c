#include "graphic.h"

SDL_Window *window;

int colorBackground(){
  if(SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF) < 0) {
    printf("Renderer color could not be set! SDL Error: %s\n",SDL_GetError());
    return 0;
  }
  return 1;
}

void sizeWindows(Map* map){
  float minX = map->bounds->min->x;
  float maxX = map->bounds->max->x;
  float minY = map->bounds->min->y;
  float maxY = map->bounds->max->y;
  float diffX = maxX - minX;
  float diffY = maxY - minY;
  float QX = windows_Width/diffX;
  float QY = windows_Height/diffY;
  if(QX > QY){
    windows_Width = diffX*QY;
    windows_Height = diffY*QY;
  }
  else{
    windows_Width = diffX*QX;
    windows_Height = diffY*QX;
  }
}

int init_SDL() {
  if(SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n",SDL_GetError());
    return 0;
  }
  windows_Width = 800;
  windows_Height = 600;
  window = SDL_CreateWindow("CPROJ",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,windows_Width,windows_Height,SDL_WINDOW_SHOWN);
  if(window == NULL) {
    printf("Window could not be created! SDL Error: %s\n",SDL_GetError());
    return 0;
  }
  renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
  if(renderer == NULL) {
    printf("Renderer could not be created! SDL Error: %s\n",SDL_GetError());
    return 0;
  }
  return colorBackground();
}

void close_SDL() {
  SDL_DestroyRenderer(renderer);
  renderer = NULL;
  SDL_DestroyWindow(window);
  window = NULL;
  SDL_Quit();
}

void drawMap(Map* map,char* typeOfDessin){
  colorBackground();
  SDL_RenderClear(renderer);
  if(strcmp(typeOfDessin,"point") ==0){
    parcoursAvl(&(map->avl),map->bounds);
  }
  else if(strcmp(typeOfDessin,"line") ==0){
    parcoursListWay(map);
  }
  else{
    printf("Le deuxieme argument est inconnu %s\n", typeOfDessin);
  }
  SDL_RenderPresent(renderer);
}

void printMap(Map* map,char* typeOfDessin){
  if(map == NULL){
    fprintf(stderr,"La map vaut null : %s\n","fonction printMap");
    exit(EXIT_FAILURE);
  }
  if(map->bounds == NULL){
    fprintf(stderr,"Les bounds de la map vaut null : %s\n","fonction printMap");
    exit(EXIT_FAILURE);
  }
  if(map->bounds->min == NULL){
    fprintf(stderr,"Le min de la bound de la map vaut null : %s\n","fonction printMap");
    exit(EXIT_FAILURE);
  }
  if(map->bounds->max == NULL){
    fprintf(stderr,"Le max de la bound de la map vaut null : %s\n","fonction printMap");
    exit(EXIT_FAILURE);
  }
  sizeWindows(map);
  quit = 1;
  if(init_SDL()==0) {
    exit(EXIT_FAILURE);
  }
  drawMap(map, typeOfDessin);
  evenement();
  close_SDL();
  exit(EXIT_SUCCESS);

}
