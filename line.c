#include "line.h"

int heigthR =0;
int widthR =0;

void printLine(float x,float y){
  glBegin(GL_POINTS);
  glColor3f(1,1,1);
  glVertex2f(x,y);
  glEnd();
}

float echelle(float x, float y,int size){
  return x*size/y;
}

void drawWay(Map* map,Way * way){
  ListNode * l = way->listNd;
  refListNode * current =l->firstRef;
  while(current!=l->lastRef){
    Node * currentNode =searchNode(map->avl,current->nd);
    float wi=echelle(currentNode->c->x,map->bounds->max->x,widthR);
    float he=echelle(currentNode->c->y,map->bounds->max->y,heigthR);
    printLine(wi,he);
    current = current->next;
  }
}

void parcoursListWay(Map* map,int width,int heigth){
  heigthR=heigth;
  widthR=width;
  ListWay * l = map->listWay;
  refListWay * current =l->firstRef;
  while(current!=l->lastRef){

    Way * currentWay =searchWay(map->avlWay,current->way);
    printf("%s\n",currentWay->visible);
//    if(strcmp(currentWay->visible,"true")==0){
      drawWay(map,currentWay);
//    }
//    else if(strcmp(currentWay->visible,"false")!=0){
      printf("Le champs visible du way %ld ne vaut ni true ni false mais %s\n",currentWay->id,currentWay->visible );
//    }
    current = current->next;
  }
}
