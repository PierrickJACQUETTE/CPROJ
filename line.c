#include "line.h"

Map * map;

float rightCoordValue(float coord, int max){
	if(coord<0){
		return 0;
	}
	if(coord>max){
		return max;
	}
	else return coord;
}

void highway(Way *way, short coord_y[way->size],short coord_x[way->size],int thick){
	Sint16 coord_xNode[4] = {0.0,0.0,0.0,0.0};
	Sint16 coord_yNode[4] = {0.0,0.0,0.0,0.0};
	int i;
	for(i=1;i<way->size;i++){

		if(i==1){
			float length = distanceXY(coord_x[i-1],coord_y[i-1],coord_x[i],coord_y[i]);
			float fx = normalize(coord_y[i-1],coord_y[i],length);
			float gx = fx;
			float fy = 0.0-normalize(coord_x[i-1],coord_x[i],length);
			float gy = fy;
			coord_xNode[0] = fx;
			coord_xNode[1] = gx;
			coord_yNode[0] = fy;
			coord_yNode[1] = gy;
			float coeff = (coord_y[i-1]-coord_y[i])/(coord_x[i-1]-coord_x[i]);
			if(coeff>0){
				extremite(coord_x[i-1],fx*thick/2,gx*thick/2,coord_xNode,1,1);
				extremite(coord_y[i-1],fy*thick/2,gy*thick/2,coord_yNode,1,1);
			}
			else{
				extremite(coord_x[i-1],fx*thick/2,gx*thick/2,coord_xNode,0,1);
				extremite(coord_y[i-1],fy*thick/2,gy*thick/2,coord_yNode,0,1);
			}
		}
		if(i==way->size-1){
			int j;
			for(j=0;j<4;j++){
				printf("Fin X : %d, Y %d\n",coord_xNode[j],coord_yNode[j] );
			}
			printf("\n");
			float length = distanceXY(coord_x[i-1],coord_y[i-1],coord_x[i],coord_y[i]);
			float fx = normalize(coord_y[i-1],coord_y[i],length);
			float gx = fx;
			float fy = 0.0-normalize(coord_x[i-1],coord_x[i],length);
			float gy = fy;
			coord_xNode[2] = fx;
			coord_xNode[3] = gx;
			coord_yNode[2] = fy;
			coord_yNode[3] = gy;
			float coeff = (coord_y[i-1]-coord_y[i])/(coord_x[i-1]-coord_x[i]);
			if(coeff>0){
				extremite(coord_x[i],fx*thick/2,gx*thick/2,coord_xNode,1,2);
				extremite(coord_y[i],fy*thick/2,gy*thick/2,coord_yNode,1,2);
			}
			else{
				extremite(coord_x[i],fx*thick/2,gx*thick/2,coord_xNode,0,2);
				extremite(coord_y[i],fy*thick/2,gy*thick/2,coord_yNode,0,2);
			}
			for(j=0;j<4;j++){
				printf("Fin XX : %d, Y %d\n",coord_xNode[j],coord_yNode[j] );
			}
			printf("\n");

			filledPolygonRGBA(renderer,coord_xNode,coord_yNode,4,255,0,0,255);
		}
		else{
			float lengthAB = distanceXY(coord_x[i-2],coord_y[i-2],coord_x[i-1],coord_y[i-1]);
			float resABy = normalize(coord_y[i-2],coord_y[i-1],lengthAB);
			float resABx = normalize(coord_x[i-2],coord_x[i-1],lengthAB);

			float lengthBC = distanceXY(coord_x[i-1],coord_y[i-1],coord_x[i],coord_y[i]);
			float resBCx = normalize(coord_x[i-1],coord_x[i],lengthBC);
			float resBCy = normalize(coord_y[i-1],coord_y[i],lengthBC);

			float X = (resABx - resBCx)*thick/2;
			float Y = (resABy - resBCy)*thick/2;

			double angleCal = angle(coord_x[i-2],coord_y[i-2],coord_x[i-1],coord_y[i-1],coord_x[i],coord_y[i]);
			if(angleCal >0){
				midle(coord_x[i-1],X,0,coord_xNode);
				midle(coord_y[i-1],Y,0,coord_yNode);
			}
			else{
				midle(coord_x[i-1],X,1,coord_xNode);
				midle(coord_y[i-1],Y,1,coord_yNode);
			}
			int j;
			for(j=0;j<4;j++){

				printf("Inter X : %d, Y %d\n",coord_xNode[j],coord_yNode[j] );
			}
			printf("\n");
			filledPolygonRGBA(renderer,coord_xNode,coord_yNode,4,255,0,0,255);
			//thickLineRGBA(renderer,coord_xNode[0],coord_yNode[0],coord_xNode[3],coord_yNode[3],1,0,255,0,255);
			if(i !=way->size-1){
				swap(coord_yNode);
				swap(coord_xNode);
			}
		}
		thickLineRGBA(renderer,coord_x[i-1],coord_y[i-1],coord_x[i],coord_y[i],thick,way->tag->c->red,way->tag->c->green,way->tag->c->blue,105);
	}
}

Sint16 checkColor(int color){
	if(color < 0){
		return 0;
	}
	return color;
}

void fillWay(Way * way){
	if(map == NULL){
		fprintf(stderr,"La map est NULL dans line fonction fillWay\n");
		return;
	}
	if(way == NULL){
		fprintf(stderr,"Le way est NULL dans line fonction fillWay\n");
		return;
	}
	ListNode * l = way->listNd;
	if(l == NULL){
		fprintf(stderr,"Le way %ld a pas de noeud : line.c fonction fill way\n",way->id );
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
					coord_x[nbre] = miseAEchelleX(currentNode->c->x,map->bounds->max->x,windows_Width);
					coord_y[nbre] = miseAEchelleY(currentNode->c->y,map->bounds->max->y,windows_Height);
					nbre++;
				}
				else{
					fprintf(stderr,"le node %ld n'a pas de coordonnees\n",current->nd );
				}
				current = current->next;
			}
			else{
				fprintf(stderr,"Le node %ld n'est pas définis dans le fichier d'entree \n",current->nd );
			}
		}
		if(way->tag != NULL && way->tag->tagKey != NULL && way->tag->c != NULL){
			if(strcmp(way->tag->tagKey,"highway")==0){
				//generer le cas d'un node par un point
				int thick =0;
				if(way->tag->thick != 0){
					thick = way->tag->thick;
				}
				int i;
				int x = coord_x[0];
				int y = coord_y[0];
				for(i=0;i<way->size;i++){
					thickLineRGBA(renderer,x,y,coord_x[i],coord_y[i],thick,way->tag->c->red,way->tag->c->green,way->tag->c->blue,255);
					if(drawContour ==1){
						int diff = 100;
						thickLineRGBA(renderer,x+thick/2,y+thick/2,coord_x[i]+thick/2,coord_y[i]+thick/2,1,checkColor(way->tag->c->red-diff),checkColor(way->tag->c->green-diff),checkColor(way->tag->c->blue-diff),255);
						thickLineRGBA(renderer,x-thick/2,y-thick/2,coord_x[i]-thick/2,coord_y[i]-thick/2,1,checkColor(way->tag->c->red-diff),checkColor(way->tag->c->green-diff),checkColor(way->tag->c->blue-diff),255);
					}
					x = coord_x[i];
					y = coord_y[i];
				}

				//int kk=0;
				//for(kk=0;kk<way->size;kk++){
				//	printf("Coor X : %d, Y %d\n",coord_x[kk],coord_y[kk] );
				//}
				//printf("\n");
				//highway(way,coord_y,coord_x,thick);

				if(way->name!=NULL){
					Node * firstNode = searchNode(map->avl,l->firstRef->nd);
					Node * lastNode = searchNode(map->avl,l->lastRef->nd);

					float coordxf= miseAEchelleX(firstNode->c->x ,map->bounds->max->x,windows_Width);
					float coordyf= miseAEchelleY(firstNode->c->y ,map->bounds->max->y,windows_Height);
					float coordxl= miseAEchelleX(lastNode->c->x,map->bounds->max->x,windows_Width);
					float coordyl= miseAEchelleY(lastNode->c->y,map->bounds->max->y,windows_Height);

					coordxf = rightCoordValue(coordxf,windows_Width);
					coordxl = rightCoordValue(coordxl,windows_Width);
					coordyf = rightCoordValue(coordyf,windows_Height);
					coordyl = rightCoordValue(coordyl,windows_Height);

					//float coordx= miseAEchelleX((firstNode->c->x + lastNode->c->x) /2,map->bounds->max->x,WINDOW_WIDTH);
					//float coordy= miseAEchelleY((firstNode->c->y + lastNode->c->y) /2,map->bounds->max->y,WINDOW_HEIGHT);

					float cx = (coordxf+coordxl)/2;
					float cy = (coordyf+coordyl)/2;

					//					printf("Way id: %ld, Name: %s,coord noeud : %f, %f\n",way->id,way->name,fabs(cx),fabs(cy));

					//if(cx>cy){
					stringRGBA(renderer,fabs(cx),fabs(cy),way->name,0,0,0,255);
					//}
					//else{
					//stringRGBA(renderer,coordx,coordy,way->name,0,0,0,255);
					//}
				}
			}
			else{
				if(drawContour ==1){
					polygonRGBA(renderer,coord_x,coord_y,way->size,139,71,137,255);
				}
				filledPolygonRGBA(renderer,coord_x,coord_y,way->size,way->tag->c->red,way->tag->c->green,way->tag->c->blue,255);
			}
		}
		else{
			filledPolygonRGBA(renderer,coord_x,coord_y,way->size,0,0,255,255);
		}
	}
}

void analyseCoastline(Way* w, Map* map){
	printf("analyse coastline\n");
	ListNode * ln =w->listNd;
	Node * first= searchNode(map->avl,w->listNd->firstRef->nd);
	Node* last = searchNode(map->avl,w->listNd->lastRef->nd);
	//while(current!=NULL){
	//Node * currentNode = searchNode(map->avl,current->nd);
	printf("lon= %f lat= %f \n", first->c->x,first->c->y);
	printf("lon= %f lat= %f \n", last->c->x,last->c->y);

	w->listNd=addRefListNode((unsigned long)3, ln);
	w->size++;

	//	current=current->next;
	//}
}

void parcourList(ListWay *l){
	if(l!=NULL){
		int coastline=0;
		refListWay * current = l->firstRef;
		while(current != NULL){
			Way * currentWay = searchWay(map->avlWay,current->way);
			if(currentWay != NULL){
				if((currentWay->draw == 0)&&(strcmp(currentWay->visible,"T")==0)){
					// case coastline
					if(strcmp(currentWay->tag->tagValue, "coastline") ==0){
						printf("coastline");
						if(coastline==0){
							colorBackground(0,102,205,100);
							coastline = 1;
							SDL_RenderClear(renderer);
							analyseCoastline(currentWay, map);
							printf("id= %ld \n", currentWay->listNd->lastRef->nd);
							fillWay(currentWay);
						}
						else{
							analyseCoastline(currentWay, map);
						}
					}
					fillWay(currentWay);
					currentWay->draw = 1;
				}
				else if((strcmp(currentWay->visible,"F") !=0) && (currentWay->draw !=1) ){
					fprintf(stderr,"Le champs visible du way %ld ne vaut ni true ni false mais %s draw: %d\n",currentWay->id,currentWay->visible, currentWay->draw );
				}
			}
			else{
				fprintf(stderr,"Le way %ld n'est pas définis dans le fichier d'entree dans line parcourList\n",current->way );
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
							fillWay(currentWay);
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
							fillWay(currentWay);
							currentWay->draw = 1;
						}
					}
					cW = cW->next;
				}
			}
			else if(strcmp(currentRel->visible,"F") != 0){
				fprintf(stderr,"Le champs visible de la relation  %ld ne vaut ni true ni false mais %s\n",currentRel->id,currentRel->visible );
			}
			current = current->next;
		}
	}
}

void parcoursListWay(){
	drawContour = 1;
	//parcourList(map->wayHighway,map,WINDOW_WIDTH,WINDOW_HEIGHT,renderer);
	parcourList(map->wayWater);
	parcourRelation(map->listRelation);
	parcourList(map->wayOther);
	parcourList(map->wayGreen);
	parcourList(map->wayBuilding);
	parcourList(map->wayHighway);
}
