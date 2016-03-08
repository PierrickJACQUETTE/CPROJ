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
	// a faire pour Isa
	return NULL;
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

ListNode* addRefListNode(unsigned long n, ListNode *l){
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
	return l;
}

Tag* initTag(char* key, char* value){
	Tag* t=malloc(sizeof(Tag));
	t->tagKey=key;
	t->tagValue=value;
	//t->c voir si l'on le met en arguments ou si on le recherche dans les reference de tag;
	return t;
}

Way* initWay(unsigned long id, char* visible, ListNode* ln, Tag* tag){
	Way* w= malloc(sizeof(Way));
	w->id=id;
	w->listNd=ln;
	w->visible=visible;
	w->tag=tag;
	return w;
}
