#include "line.h"

int heigthR =0;
int widthR =0;

void printPoint(float x,float y){
  glVertex2f(x,y);
}

float echelle(float x, float y,int size){
  return x*size/y;
}

void startLine(){
  glBegin(GL_LINE_STRIP);
}

void endLine(){
  glEnd();
}

void sizeColor(Color * c){
  glColor3ub(c->red,c->green,c->blue);
}

void drawWay(Map* map,Way * way){
  ListNode * l = way->listNd;
  refListNode * current =l->firstRef;
  startLine();
  if(way->tag!=NULL){
    sizeColor(way->tag->c);
  }
  else{
    Color *c = malloc(sizeof(Color));
    c->red=255;
    c->blue=255;
    c->green=255;
    sizeColor(c);
  }
  while(current!=NULL){
    Node * currentNode =searchNode(map->avl,current->nd);
    float wi=echelle(currentNode->c->x,map->bounds->max->x,widthR);
    float he=echelle(currentNode->c->y,map->bounds->max->y,heigthR);
    printPoint(wi,he);
    current = current->next;
  }
  endLine();
}

void parcoursListWay(Map* map,int width,int heigth){
  heigthR=heigth;
  widthR=width;
  ListWay * l = map->listWay;
  refListWay * current =l->firstRef;
  while(current!=NULL){
    Way * currentWay =searchWay(map->avlWay,current->way);
   // printf("line.c currentway visible= %s\n",currentWay->visible);
    	if(strcmp(currentWay->visible,"true")==0){
    		drawWay(map,currentWay);
      }
      else if(strcmp(currentWay->visible,"false")!=0){
    		printf("Le champs visible du way %ld ne vaut ni true ni false mais %s\n",currentWay->id,currentWay->visible );
      }
    current = current->next;
  }
}
