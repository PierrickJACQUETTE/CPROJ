#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "graphic.h"
/*
gcc fichier.c -o tutorial1 -lGL -lGLU `sdl2-config --cflags --libs`
)*/
#include <stdlib.h>
#include <GL/glu.h>

enum status {QUIT, CONTINUE};
int heigth = 400; // taille fenetre par défaut
int width = 600;
SDL_Renderer* renderer;
Avl* avl;

void affichage(int xClick,int yClick)
{

  glBegin(GL_POINTS);
  glColor3f(1,1,1);
  glVertex2i(xClick,yClick);  // xClick et yClick sont des int
  glEnd();
}

void parcoursAvl(Avl *a){
  if(a->left!=NULL){
    return parcoursAvl(a->left);
  }
  affichage(a->node->c->x,a->node->c->y);
  if(a->right!=NULL){
    return parcoursAvl(a->right);
  }
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

int printMap(Map* map){
  int tabX[10] = {0,60,100,150,200,300,100,150,300,400};
  int tabY[10] = {0,60,90,100,104,10,80,70,150,160};

  SDL_Window* window = NULL; // initiailisation de fenetre vide
  window = SDL_CreateWindow // creation fenetre
  (
    "Test", SDL_WINDOWPOS_UNDEFINED, // nom
    SDL_WINDOWPOS_UNDEFINED,
    width, heigth, // taille
    SDL_WINDOW_SHOWN
  );
  renderer = NULL; // initialise le fond de la fenetre
  renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED); // met le fond

  glClearColor( 0.0f, 0.0f, 0.0f, 0.0f ); // RGB + opacité
  /* Clear The Screen And The Depth Buffer */
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // nettoyer la fenetre
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glViewport(0,0,width,heigth);
  gluOrtho2D(0,width,0,heigth);
  affichage(300,100);
  affichage(200,100);
  int i;
  for(i=0;i<10;i++){
    affichage(tabX[i],tabY[i]);
  }
  SDL_RenderPresent(renderer);
  evenement();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
