#include "point.h"

void affichage(float x, float y, SDL_Renderer* renderer){
  pixelRGBA(renderer,x,y,1,1,1,155);
}

void parcoursAvl(Avl **a, Bounds* bounds, int w, int h, SDL_Renderer* renderer){
  if((*a)->left != NULL){
    parcoursAvl(&((*a)->left),bounds,w,h,renderer);
  }
  float wi = miseAEchelleX((*a)->node->c->x,bounds->max->x,w);
  float he = miseAEchelleY((*a)->node->c->y,bounds->max->y,h);
  affichage(wi,he,renderer);

  if((*a)->right != NULL){
    parcoursAvl(&((*a)->right),bounds,w,h,renderer);
  }
}
