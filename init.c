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

	return NULL;
}
