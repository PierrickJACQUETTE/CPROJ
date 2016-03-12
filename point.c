#include "point.h"

void affichage(float x,float y){
  glBegin(GL_POINTS);
  glColor3f(1,1,1);
  glVertex2f(x,y);
  glEnd();
}

float miseAEchelle(float x, float y,int size){
  return x*size/y;
}

void parcoursAvl(Avl **a, Bounds* bounds,int w,int h){
  if((*a)->left!=NULL){
    parcoursAvl(&((*a)->left),bounds,w,h);
  }
  float wi=miseAEchelle((*a)->node->c->x,bounds->max->x,w);
  float he=miseAEchelle((*a)->node->c->y,bounds->max->y,h);
  affichage(wi,he);

  if((*a)->right!=NULL){
    parcoursAvl(&((*a)->right),bounds,w,h);
  }
}
