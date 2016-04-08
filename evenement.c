#include "evenement.h"

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
