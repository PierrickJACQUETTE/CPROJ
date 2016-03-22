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

void fillWay(Map* map, Way * way, SDL_Renderer* renderer){
  if(strcmp(way->tag->tagKey,"building")==0 && strcmp(way->tag->tagValue,"yes")==0){
  ListNode * l = way->listNd;
  refListNode * current =l->firstRef;
 
  int i=0; 
  short coord_x [way->size];
  short coord_y [way->size];
  
  /*glBegin(GL_POLYGON);
  if(way->tag!=NULL){
  	 sizeColor(way->tag->c);
  }
  else{
    //glEnd();
    return;
  } */
  while(current!=NULL){
    Node * currentNode =searchNode(map->avl,current->nd);
    float wi=echelle(currentNode->c->x,map->bounds->max->x,widthR);
    float he=echelle(currentNode->c->y,map->bounds->max->y,heigthR);
    coord_x[i]=wi; 
    coord_y[i]=he; 
    i++;
    //printPoint(wi,he);
    current = current->next;
  }
  
  int n = i-1;
  filledPolygonRGBA(renderer,coord_x,coord_y,n,way->tag->c->red,way->tag->c->green,way->tag->c->blue,155);
  //glEnd();
  }
}

void drawWay(Map* map,Way * way){
  ListNode * l = way->listNd;
  refListNode * current =l->firstRef;
  startLine();
  if(way->tag!=NULL){
  	Color *c = malloc(sizeof(Color));
    c->red=139;
    c->blue=71;
    c->green=137;
    sizeColor(c);
    //sizeColor(way->tag->c);
  }
  else{
    Color *c = malloc(sizeof(Color));
    c->red=139;
    c->blue=131;
    c->green=134;
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

void parcoursListWay(Map* map,int width,int heigth, SDL_Renderer* renderer){
  heigthR=heigth;
  widthR=width;
  ListWay * l = map->listWay;
  refListWay * current =l->firstRef;
  while(current!=NULL){
    Way * currentWay =searchWay(map->avlWay,current->way);
    	if(strcmp(currentWay->visible,"true")==0){
    		drawWay(map,currentWay);
    		fillWay(map,currentWay,renderer);
      }
      else if(strcmp(currentWay->visible,"false")!=0){
    		printf("Le champs visible du way %ld ne vaut ni true ni false mais %s\n",currentWay->id,currentWay->visible );
      }
    current = current->next;
  }
}
