#include "line.h"


Map * map = NULL;

float rightCoordValue(float coord, int max){
	if(coord<0){
		return 0;
	}
	if(coord>max){
		return max;
	}
	else return coord;
}

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
          coord_x[nbre] = miseAEchelleX(currentNode->c->x,map->bounds->max->x,WINDOW_WIDTH);
          coord_y[nbre] = miseAEchelleY(currentNode->c->y,map->bounds->max->y,WINDOW_HEIGHT);
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
        
        if(way->name!=NULL){
        	Node * firstNode = searchNode(map->avl,l->firstRef->nd);
        	Node * lastNode = searchNode(map->avl,l->lastRef->nd); 
        	
        	float coordxf= miseAEchelleX(firstNode->c->x ,map->bounds->max->x,WINDOW_WIDTH);
        	float coordyf= miseAEchelleY(firstNode->c->y ,map->bounds->max->y,WINDOW_HEIGHT);
        	float coordxl= miseAEchelleX(lastNode->c->x,map->bounds->max->x,WINDOW_WIDTH);
        	float coordyl= miseAEchelleY(lastNode->c->y,map->bounds->max->y,WINDOW_HEIGHT);
         
        	coordxf = rightCoordValue(coordxf,WINDOW_WIDTH);
        	coordxl = rightCoordValue(coordxl,WINDOW_WIDTH);
        	coordyf = rightCoordValue(coordyf,WINDOW_HEIGHT);
        	coordyl = rightCoordValue(coordyl,WINDOW_HEIGHT);
        	
        	//float coordx= miseAEchelleX((firstNode->c->x + lastNode->c->x) /2,map->bounds->max->x,WINDOW_WIDTH);
        	//float coordy= miseAEchelleY((firstNode->c->y + lastNode->c->y) /2,map->bounds->max->y,WINDOW_HEIGHT);

			float cx = (coordxf+coordxl)/2;
			float cy = (coordyf+coordyl)/2;

        	printf("Way id: %ld, Name: %s,coord noeud : %f, %f\n",way->id,way->name,fabs(cx),fabs(cy));
        
        	//if(cx>cy){
        		stringRGBA(renderer,fabs(cx),fabs(cy),way->name,0,0,0,255);
        	//}
        	//else{
        		//stringRGBA(renderer,coordx,coordy,way->name,0,0,0,255);
        	//}
        	}
        
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
  // parcourRelation(map->listRelation, map,WINDOW_WIDTH,WINDOW_HEIGHT,renderer);

  //parcourList(map->wayHighway,map,WINDOW_WIDTH,WINDOW_HEIGHT,renderer);
  parcourList(map->wayWater);
  parcourRelation(map->listRelation);
  parcourList(map->wayOther);
  parcourList(map->wayGreen);
  parcourList(map->wayBuilding);
  parcourList(map->wayHighway);


}
