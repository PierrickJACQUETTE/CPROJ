#include "point.h"

void affichage(float x, float y){
  pixelRGBA(renderer,(x* zoom) + deplacX+ deplacZX,(y* zoom) + deplacY+ deplacZY,1,1,1,255);
}

void parcoursAvl(Avl **a, Bounds* bounds){
  if((*a)->left != NULL){
    parcoursAvl(&((*a)->left),bounds);
  }
  float wi = miseAEchelleX((*a)->node->c->x,bounds->max->x,windows_Width);
  float he = miseAEchelleY((*a)->node->c->y,bounds->max->y,windows_Height);
  affichage(wi,he);
  if((*a)->right != NULL){
    parcoursAvl(&((*a)->right),bounds);
  }
}
