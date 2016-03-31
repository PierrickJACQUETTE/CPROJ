#include "point.h"

void affichage(float x, float y){
  pixelRGBA(renderer,x,y,1,1,1,155);
}

void parcoursAvl(Avl **a, Bounds* bounds){
  if((*a)->left != NULL){
    parcoursAvl(&((*a)->left),bounds);
  }
  float wi = miseAEchelleX((*a)->node->c->x,bounds->max->x,width);
  float he = miseAEchelleY((*a)->node->c->y,bounds->max->y,heigth);
  affichage(wi,he);

  if((*a)->right != NULL){
    parcoursAvl(&((*a)->right),bounds);
  }
}
