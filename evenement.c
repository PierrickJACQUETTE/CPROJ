#include "evenement.h"

void drawMap(Map* map,char* typeOfDessin){
  colorBackgroundDefault();
  SDL_RenderClear(renderer);
  if(strcmp(typeOfDessin,"point") ==0){
    parcoursAvl(&(map->avl),map->bounds);
  }
  else if(strcmp(typeOfDessin,"line") ==0){
    parcoursListWay(map);
  }
  else{
    fprintf(stderr,"Le deuxieme argument est inconnu %s\n", typeOfDessin);
  }
  SDL_RenderPresent(renderer);
}

void evenement(){
  do {
    SDL_Event e;
    if (SDL_PollEvent(&e)) { // detecte si il y a un even
      switch (e.type) {
        case SDL_QUIT :
        printf("fermeture de la fenetre.\n");
        quit = 0;
        break;
      }
    }
  }
  while (quit == 1);
}
