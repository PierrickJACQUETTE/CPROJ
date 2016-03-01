#include "graphic.h"


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

int miseAEchelleAbs(float x, Bounds* bounds){
	return (int)(x*width/(bounds->max->x));
}

int miseAEchelleOrd(float x, Bounds* bounds){
	return (int)(x*heigth/(bounds->max->y));
}

void parcoursAvl(Avl *a, Bounds* bounds){
  if(a->left!=NULL){
    return parcoursAvl(a->left,bounds);
  }
  
  int h=miseAEchelleAbs(a->node->c->x,bounds);
  int w=miseAEchelleOrd(a->node->c->y,bounds);
  affichage(h,w);
  
  if(a->right!=NULL){
    return parcoursAvl(a->right,bounds);
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

void printMap(Map* map){
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
  
  parcoursAvl(map->avl,map->bounds);
  
  SDL_RenderPresent(renderer);
  evenement();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

}
