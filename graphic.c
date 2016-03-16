#include "graphic.h"

enum status {QUIT, CONTINUE};
int heigth = 600; // taille fenetre par défaut
int width = 800;
SDL_Renderer* renderer;

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
  SDL_Window* window = NULL; // initiailisation de fenetre vide
  window = SDL_CreateWindow // creation fenetre
  (
    "CPROJ", SDL_WINDOWPOS_UNDEFINED, // nom
    SDL_WINDOWPOS_UNDEFINED,
    width, heigth, // taille
    SDL_WINDOW_SHOWN
  );
  renderer = NULL; // initialise le fond de la fenetre
  renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED); // met le fond

  glClearColor( 225.0f, 220.0f, 225.0f, 0.0f ); // RGB + opacité
  /* Clear The Screen And The Depth Buffer */
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // nettoyer la fenetre
  glLoadIdentity();
  glViewport(0,0,width,heigth);
  gluOrtho2D(0,width,0,heigth);
  if(strcmp(typeOfDessin,"point")==0){
    parcoursAvl(&(map->avl),map->bounds,width,heigth);
  }
  else if(strcmp(typeOfDessin,"line")==0){
    parcoursListWay(map,width,heigth);
  }
  else{
    printf("Le deuxieme argument est inconnu %s\n", typeOfDessin);
  }

  SDL_RenderPresent(renderer);
  evenement();
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

}
