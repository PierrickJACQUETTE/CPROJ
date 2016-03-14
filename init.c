#include "init.h"


Node* initNode(unsigned long id, float lat, float lon, char* visible, Bounds *b){
	Node * n= malloc(sizeof(Node));
	n->id=id;
	n->c= malloc(sizeof(Coordinate));
	n->c= conversionLatLon(lat, lon);
	n->c->x= n->c->x - b->min->x;
	n->c->y= n->c->y - b->min->y;
	//n->c->x= distanceLatLon(lat, lon, lat, b->min->x);
	//n->c->y= distanceLatLon(lat, lon, b->min->y, lon);
	n->visible= visible;
	return n;
}

Bounds* initBounds(float lat_min,float lat_max, float lon_min, float lon_max){
	Bounds *b=malloc(sizeof(Bounds));
	b->min =malloc(sizeof(Coordinate));
	b->max = malloc(sizeof(Coordinate));
	b->min= conversionLatLon(lat_min, lon_min);
	b->max= conversionLatLon(lat_max, lon_max);
	return b;
}


Tag** initReferenceTag(){
	Tag **t=malloc(9*sizeof(Tag*));
	int i=1;
	for(i=0; i<9; i++){
		t[i]=malloc(sizeof(Tag));
		t[i]->c=malloc(sizeof(Color));
	}
	t[1]->tagKey ="building"; t[1]->tagValue ="yes"; t[1]->c->red=60; t[1]->c->green=60; t[1]->c->blue=60;
	t[2]->tagKey ="highway"; t[2]->tagValue ="residential"; t[2]->c->red=255; t[2]->c->green=255; t[2]->c->blue=204;
	t[3]->tagKey ="waterway"; t[3]->tagValue ="canal"; t[3]->c->red=51; t[3]->c->green=102; t[3]->c->blue=204;
	t[4]->tagKey ="waterway"; t[4]->tagValue ="river"; t[4]->c->red=0; t[4]->c->green=153; t[4]->c->blue=255;
	t[5]->tagKey ="waterway"; t[5]->tagValue ="water"; t[5]->c->red=51; t[5]->c->green=204; t[5]->c->blue=255;
	t[6]->tagKey ="waterway"; t[6]->tagValue ="coastline"; t[6]->c->red=0; t[6]->c->green=204; t[6]->c->blue=255;
	t[7]->tagKey ="landuse"; t[7]->tagValue ="grass"; t[7]->c->red=102; t[7]->c->green=204; t[7]->c->blue=51;
	t[8]->tagKey ="leisure"; t[8]->tagValue ="park"; t[8]->c->red=51; t[8]->c->green=153; t[8]->c->blue=0;
	t[0]->tagKey ="landuse"; t[0]->tagValue ="forest"; t[0]->c->red=51; t[0]->c->green=102; t[0]->c->blue=0;
	return t;
}



refListNode* initRefListNode(unsigned long  n, refListNode* next){
	refListNode* r=malloc(sizeof(refListNode));
	r->nd=n;
	r->next=next;
	return r;
}

ListNode* initListNode(unsigned long first){
	ListNode* l=malloc(sizeof(ListNode));
	refListNode* f=initRefListNode(first,NULL);
	l->firstRef=f;
	l->lastRef=f;
	return l;
}

ListNode* addRefListNode(unsigned long n, ListNode* l){
	refListNode* r=initRefListNode(n, NULL);
	if(l!=NULL){
		if((l->firstRef!=NULL) && (l->firstRef->nd!=0)){
			l->lastRef->next=r;
			l->lastRef=r;
			return l;
		}
		else{
			l->firstRef=r;
			l->lastRef=r;
			return l;
		}
	}
	else{
		l=initListNode(n);
	}
	return l;
}

Tag* initTag(char* key, char* value, Color* c){
	Tag* t=malloc(sizeof(Tag));
	t->tagKey=key;
	t->tagValue=value;
	// rechercher la couleur ici
	t->c=c;// voir si l'on le met en arguments ou si on le recherche dans les reference de tag;
	return t;
}

Way* initWay(unsigned long id, char* visible, ListNode* ln, Tag* tag){
	Way* w= malloc(sizeof(Way));
	w->id=id;
	w->listNd=ln;
	if(strcmp(visible, "true")==0){	w->visible="true";}
	else{ w->visible="false";}
	w->tag=malloc(sizeof(Tag));
	w->tag=tag;
	return w;
}
Tag* goodTag(char * k, char *v, Tag**  ref){
	int i=0;
	if(ref!=NULL){
		for(i=0; i<9; i++){
			if(ref[i]!=NULL){
				if(strcmp(k, ref[i]->tagKey)==0){
					if(strcmp(v, ref[i]->tagValue)==0){
						return initTag(k, v, ref[i]->c);
					}
				}
			}
		}
	}
	return NULL;
}



refListWay* initRefListWay(unsigned long  w, refListWay* next){
	refListWay* r=malloc(sizeof(refListWay));
	r->way=w;
	r->next=next;
	return r;
}

ListWay* initListWay(unsigned long first){
	ListWay* l=malloc(sizeof(ListWay));
	refListWay* f=initRefListWay(first,NULL);
	l->firstRef=f;
	l->lastRef=f;
	return l;
}


ListWay* addRefListWay(Way* w, ListWay* lw){
	refListWay* r=initRefListWay(w->id, NULL);
	if(lw!=NULL){
		if((lw->firstRef!=NULL) && (lw->firstRef->way!=0)){
			lw->lastRef->next=r;
			lw->lastRef=r;
			return lw;
		}
		else{
			lw->firstRef=r;
			lw->lastRef=r;
			return lw;
		}
	}
	else{
		lw=initListWay(w->id);
	}
	return lw;
}

Map* initMap(){
	Map * map = malloc(sizeof(Map));
	//map->referenceTag=malloc(9*sizeof(Tag*));
	map->referenceTag=initReferenceTag();
	return map;
}
