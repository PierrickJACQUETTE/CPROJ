#include "evenement.h"

void drawMapSa(){
  colorBackgroundDefault();
  SDL_RenderClear(renderer);
  if(strcmp(typeOfDraw,"point") ==0){
    parcoursAvl(&(map->avl),map->bounds);
  }
  else if(strcmp(typeOfDraw,"line") ==0){
    parcoursListWay();
  }
  else{
    fprintf(stderr,"Le deuxieme argument est inconnu %s\n", typeOfDraw);
  }
  SDL_RenderPresent(renderer);
}

void drawMap(Map* m,char* typeOfDessin){
  map = m;
  typeOfDraw = typeOfDessin;
  zoom = 1;
  deplacX = 0;
  deplacY = 0;
  deplacZX = 0;
  deplacZY = 0;
  pasSourisX = 0;
  pasSourisY = 0;
  clicker = 0;
  drawMapSa();
}

float clavier(SDL_Event e,float i){
  switch(e.key.keysym.sym){

    case SDLK_p:
    i = calculateZoom(windows_Width/2,windows_Height/2,i,0);
    drawMapSa();
    break;

    case SDLK_m:
    if(zoom >= 2){
      i = calculateZoom(windows_Width/2,windows_Height/2,i,1);
      drawMapSa();
    }
    break;

    case SDLK_UP:
    deplacY += PASCLAVIER;
    drawMapSa();
    break;

    case SDLK_DOWN:
    deplacY -= PASCLAVIER;
    drawMapSa();
    break;

    case SDLK_RIGHT:
    deplacX -= PASCLAVIER;
    drawMapSa();
    break;

    case SDLK_LEFT:
    deplacX += PASCLAVIER;
    drawMapSa();
    break;

    case SDLK_q :
    printf("fermeture de la fenetre.\n");
    quit = 0;
    break;

    default:
    break;
  }
  return i;
}

void windowEvent(SDL_Event e){
  switch (e.window.event) {
    case SDL_WINDOWEVENT_RESIZED:
    windows_Width = e.window.data1;
    windows_Height = e.window.data2;
    drawMapSa();
    break;

    default:
    break;
  }
}

void evenement(){
  int sourisX = 0;
  int sourisY = 0;
  float i = 0;
  do {
    SDL_Event e;
    if (SDL_PollEvent(&e)) { // detecte si il y a un even
      switch (e.type) {

        case SDL_MOUSEWHEEL :
        if(e.motion.x>0){
          i = calculateZoom(sourisX,sourisY,i,0);
          drawMapSa();
        }
        else if (zoom >= 2){
          i = calculateZoom(sourisX,sourisY,i,1);
          drawMapSa();
        }
        break;

        case SDL_MOUSEBUTTONDOWN:
        pasSourisX = e.motion.x;
        pasSourisY = e.motion.y;
        clicker = 1;
        break;

        case SDL_MOUSEMOTION :
        sourisX = e.motion.x;
        sourisY = e.motion.y;
        if(clicker == 1){
          deplacX += -(pasSourisX - sourisX);
          deplacY += -(pasSourisY - sourisY);
          pasSourisX = sourisX;
          pasSourisY = sourisY;
          drawMapSa();
        }
        break;

        case SDL_WINDOWEVENT :
        windowEvent(e);
        break;

        case SDL_MOUSEBUTTONUP:
        clicker = 0;
        break;

        case SDL_KEYDOWN:
        i =	clavier(e,i);
        break;

        case SDL_QUIT :
        printf("fermeture de la fenetre.\n");
        quit = 0;
        break;

        default:
        break;
      }
    }
  }
  while (quit == 1);
}
