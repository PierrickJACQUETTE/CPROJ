#include "line.h"

int heigthR =0;
int widthR =0;

void fillWay(Map* map, Way * way, SDL_Renderer* renderer){
  ListNode * l = way->listNd;
  refListNode * current =l->firstRef;
  int nbre=0;
  short coord_x [way->size];
  short coord_y [way->size];
  while(current!=NULL){
    Node * currentNode =searchNode(map->avl,current->nd);
    float wi=miseAEchelleX(currentNode->c->x,map->bounds->max->x,widthR);
    float he=miseAEchelleY(currentNode->c->y,map->bounds->max->y,heigthR);
    coord_x[nbre]=wi;
    coord_y[nbre]=he;
    nbre++;
    current = current->next;
  }
  if(way->tag!=NULL){
    if(strcmp(way->tag->tagKey,"highway")==0){
      int i;
      int x = coord_x[0];
      int y = coord_y[0];
      for(i=0;i<nbre;i++){
        lineRGBA(renderer,x,y,coord_x[i],coord_y[i],255,0,0,155);
        x=coord_x[i];
        y=coord_y[i];
      }
    }
    else{
      polygonRGBA(renderer,coord_x,coord_y,nbre,139,71,137,155);
      filledPolygonRGBA(renderer,coord_x,coord_y,nbre,way->tag->c->red,way->tag->c->green,way->tag->c->blue,155);
    }
  }
  else{
    filledPolygonRGBA(renderer,coord_x,coord_y,nbre,0,0,255,155);
  }
}

void parcourList(ListWay *l,Map* map,int width,int heigth, SDL_Renderer* renderer){
  if(l!=NULL){
    refListWay * current =l->firstRef;
    while(current!=NULL){
      Way * currentWay =searchWay(map->avlWay,current->way);
      if((currentWay->draw== 0)&&(strcmp(currentWay->visible,"T")==0)){
        if(strcmp(currentWay->tag->tagValue, "coastline")==0){
          printf("coastline\n");
          if(SDL_SetRenderDrawColor(renderer,0,0,0xFF,0xFF) < 0) { // problème ne set pas en blue
            printf("Renderer color could not be set! SDL Error: %s\n",SDL_GetError());
          }
          SDL_RenderClear(renderer);
          currentWay->tag->c->red=0;
          currentWay->tag->c->blue=0;
          currentWay->tag->c->green=0;
          fillWay(map,currentWay,renderer);
          return;
        }
        fillWay(map,currentWay,renderer);
        currentWay->draw=1;
      }
      else if(strcmp(currentWay->visible,"F")!=0){
        printf("Le champs visible du way %ld ne vaut ni true ni false mais %s\n",currentWay->id,currentWay->visible );
      }
      current = current->next;
    }
  }
}

void parcourRelation(ListRelation *lr, Map* map,int width,int heigth, SDL_Renderer* renderer){
  if(lr!=NULL){
    refListRel * current =lr->firstRef;
    while(current!=NULL){
      Relation * currentRel =current->relation;
      if((strcmp(currentRel->visible,"T")==0) && currentRel->listW!=NULL){
        refListWay * cW =currentRel->listW->firstRef;
        while(cW!=NULL){
          if(strcmp(cW->role,"outer")==0){
            Way * currentWay =searchWay(map->avlWay,cW->way);
            if((currentWay!=NULL) && (currentWay->draw== 0) && (strcmp(currentWay->visible,"T")==0)){
              fillWay(map,currentWay,renderer);
              currentWay->draw=1;
            }
          }
          cW = cW->next;
        }
        cW =currentRel->listW->firstRef;
        while(cW!=NULL){
          if(strcmp(cW->role,"inner")==0){
            Way * currentWay =searchWay(map->avlWay,cW->way);
            if((currentWay!=NULL) && (currentWay->draw== 0)&&(strcmp(currentWay->visible,"T")==0)){
              fillWay(map,currentWay,renderer);
              currentWay->draw=1;
            }
          }
          cW = cW->next;
        }
      }
      else if(strcmp(currentRel->visible,"F")!=0){
        printf("Le champs visible de la relation  %ld ne vaut ni true ni false mais %s\n",currentRel->id,currentRel->visible );
      }
      current = current->next;
    }

  }
}

void parcoursListWay(Map* map,int width,int heigth, SDL_Renderer* renderer){
  heigthR=heigth;
  widthR=width;
  parcourRelation(map->listRelation, map,width,heigth,renderer);

  //parcourList(map->wayHighway,map,width,heigth,renderer);
  parcourList(map->wayWater,map,width,heigth,renderer);
  parcourList(map->wayGreen,map,width,heigth,renderer);
  parcourList(map->wayBuilding,map,width,heigth,renderer);
  parcourList(map->wayOther,map,width,heigth,renderer);
  parcourList(map->wayHighway,map,width,heigth,renderer);
}
