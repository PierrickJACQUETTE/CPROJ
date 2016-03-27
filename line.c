#include "line.h"

int heigthR =0;
int widthR =0;

void fillWay(Map* map, Way * way, SDL_Renderer* renderer){
  ListNode * l = way->listNd;
  refListNode * current =l->firstRef;
  int i=0;
  short coord_x [way->size];
  short coord_y [way->size];
  while(current!=NULL){
    Node * currentNode =searchNode(map->avl,current->nd);
    float wi=miseAEchelleX(currentNode->c->x,map->bounds->max->x,widthR);
    float he=miseAEchelleY(currentNode->c->y,map->bounds->max->y,heigthR);
    coord_x[i]=wi;
    coord_y[i]=he;
    i++;
    current = current->next;
  }
  int n = i-1;
  if(way->tag!=NULL){
  	 polygonRGBA(renderer,coord_x,coord_y,n,139,71,137,155);
    filledPolygonRGBA(renderer,coord_x,coord_y,n,way->tag->c->red,way->tag->c->green,way->tag->c->blue,155);
  }
  else{
    printf("test\n");
    filledPolygonRGBA(renderer,coord_x,coord_y,n,0,0,255,155);
  }
}

void parcoursListWay(Map* map,int width,int heigth, SDL_Renderer* renderer){
  heigthR=heigth;
  widthR=width;
  ListWay * l = map->listWay;
  refListWay * current =l->firstRef;
  while(current!=NULL){
    Way * currentWay =searchWay(map->avlWay,current->way);
    if(strcmp(currentWay->visible,"T")==0){
      fillWay(map,currentWay,renderer);
    }
    else if(strcmp(currentWay->visible,"F")!=0){
      printf("Le champs visible du way %ld ne vaut ni true ni false mais %s\n",currentWay->id,currentWay->visible );
    }
    current = current->next;
  }
}
