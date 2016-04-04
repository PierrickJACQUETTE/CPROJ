#include "line.h"

Map * map = NULL;

void fillWay(Map* map, Way * way){
  if(map == NULL){
    printf("La map est NULL dans line fonction fillWay\n");
    return;
  }
  if(way == NULL){
    printf("Le way est NULL dans line fonction fillWay\n");
    return;
  }
  ListNode * l = way->listNd;
  if(l == NULL){
    printf("Le way %ld a pas de noeud : line.c fonction fill way\n",way->id );
    return;
  }
  refListNode * current =l->firstRef;
  int nbre=0;
  if(way->size != 0){
    short coord_x [way->size];
    short coord_y [way->size];
    while(current!=NULL){
      Node * currentNode = searchNode(map->avl,current->nd);
      if(currentNode != NULL){
        if(currentNode->c !=NULL){
          coord_x[nbre] = miseAEchelleX(currentNode->c->x,map->bounds->max->x,width);
          coord_y[nbre] = miseAEchelleY(currentNode->c->y,map->bounds->max->y,heigth);
          nbre++;
        }
        else{
          printf("le node %ld n'a pas de coordonnees\n",current->nd );
        }
        current = current->next;
      }
      else{
        printf("Le node %ld n'est pas définis dans le fichier d'entree \n",current->nd );
      }
    }
    if(way->tag != NULL && way->tag->tagKey != NULL && way->tag->c != NULL){
      if(strcmp(way->tag->tagKey,"highway")==0){
        int i;
        int x = coord_x[0];
        int y = coord_y[0];
        for(i=0;i<way->size;i++){
          int thick =0;
          if(way->tag->thick == 0){
            thick = way->tag->thick+1; //pour l'instant : retirer le +1 quand valeur != 0 dans le tableau
          }
          thickLineRGBA(renderer,x,y,coord_x[i],coord_y[i],thick,255,0,0,155);
          x = coord_x[i];
          y = coord_y[i];
        }
        
        //Code pour ecrire le nom des rues
        
        /*Node * firstNode = searchNode(map->avl,l->firstRef->nd); 
        Sint16 coordx_firstNode = miseAEchelleX(firstNode->c->x,map->bounds->max->x,width);
        Sint16 coordy_firstNode = miseAEchelleY(firstNode->c->y,map->bounds->max->y,heigth);
        Node * lastNode = searchNode(map->avl,l->lastRef->nd); 
        Sint16 coordx_lastNode = miseAEchelleX(lastNode->c->x,map->bounds->max->x,width);
        Sint16 coordy_lastNode = miseAEchelleY(lastNode->c->y,map->bounds->max->y,heigth);
        printf("Name: %s,coord noeud : %d, %d\n",way->name,(coordx_firstNode+coordx_lastNode)/2,(coordy_firstNode+coordy_lastNode)/2);
        //if(coordx>coordy){
        	stringRGBA(renderer,(coordx_firstNode+coordx_lastNode)/2,(coordy_firstNode+coordy_lastNode)/2,way->name,0,0,0,255);
        //}
        //else{
        	//stringRGBA(renderer,coordx,coordy,way->name,0,0,0,255);
        //}*/
        
      }
      else{
        polygonRGBA(renderer,coord_x,coord_y,way->size,139,71,137,240);
        filledPolygonRGBA(renderer,coord_x,coord_y,way->size,way->tag->c->red,way->tag->c->green,way->tag->c->blue,240);
      }
    }
    else{
      filledPolygonRGBA(renderer,coord_x,coord_y,way->size,0,0,255,200);
    }
  }
}

void parcourList(ListWay *l){
  if(l!=NULL){
    int coastline=0;
    refListWay * current = l->firstRef;
    while(current != NULL){
      Way * currentWay = searchWay(map->avlWay,current->way);
      if(currentWay != NULL){
        if((currentWay->draw == 0)&&(strcmp(currentWay->visible,"T")==0)){
          if((strcmp(currentWay->tag->tagValue, "coastline") ==0) && (coastline ==0) ){
            if(SDL_SetRenderDrawColor(renderer,0,102,205,100) < 0) {
              printf("Renderer color could not be set! SDL Error: %s\n",SDL_GetError());
            }
            coastline = 1;
            SDL_RenderClear(renderer);
            fillWay(map,currentWay);
          }
          fillWay(map,currentWay);
          currentWay->draw = 1;
        }
        else if((strcmp(currentWay->visible,"F") !=0) && (currentWay->draw !=1) ){
          printf("Le champs visible du way %ld ne vaut ni true ni false mais %s draw: %d\n",currentWay->id,currentWay->visible, currentWay->draw );
        }
      }
      else{
        printf("Le way %ld n'est pas définis dans le fichier d'entree dans line parcourList\n",current->way );
      }
      current = current->next;
    }
  }
}

void parcourRelation(ListRelation *lr){
  if(lr != NULL){
    refListRel * current = lr->firstRef;
    while(current != NULL){
      Relation * currentRel = current->relation;
      if((strcmp(currentRel->visible,"T" )== 0) && currentRel->listW != NULL){
        refListWay * cW = currentRel->listW->firstRef;
        while(cW != NULL){
          if(strcmp(cW->role,"outer") == 0){
            Way * currentWay =searchWay(map->avlWay,cW->way);
            if((currentWay != NULL) && (currentWay->draw == 0) && (strcmp(currentWay->visible,"T") == 0)){
              fillWay(map,currentWay);
              currentWay->draw = 1;
            }
          }
          cW = cW->next;
        }
        cW = currentRel->listW->firstRef;
        while(cW!=NULL){
          if(strcmp(cW->role,"inner") ==0){
            Way * currentWay = searchWay(map->avlWay,cW->way);
            if((currentWay !=NULL) && (currentWay->draw == 0)&&(strcmp(currentWay->visible,"T") ==0)){
              fillWay(map,currentWay);
              currentWay->draw = 1;
            }
          }
          cW = cW->next;
        }
      }
      else if(strcmp(currentRel->visible,"F") != 0){
        printf("Le champs visible de la relation  %ld ne vaut ni true ni false mais %s\n",currentRel->id,currentRel->visible );
      }
      current = current->next;
    }
  }
}

void parcoursListWay(Map* mapG){
  map = mapG;
  // parcourRelation(map->listRelation, map,width,heigth,renderer);

  //parcourList(map->wayHighway,map,width,heigth,renderer);
  parcourList(map->wayWater);
  parcourRelation(map->listRelation);
  parcourList(map->wayOther);
  parcourList(map->wayGreen);
  parcourList(map->wayBuilding);
  parcourList(map->wayHighway);


}
