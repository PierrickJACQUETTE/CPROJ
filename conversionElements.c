/**
 * \file conversionElements.c
 * \brief Calculate the transformation for a node by open street map
 * \author Isabelle MARINO Pierrick JACQUETTE Hafca TIRICHINE
 * \version 0.1
 * \date 19 february 2016
 *
 * Calculate node's Coordinates: transform an openstreetmap Coordinates to an standar Coordinates
 * Caculate the bounds proportion   
 *
 */

#include "conversionElements.h"


Coordinate* conversionLatLon(float lat, float lon){
	Coordinate *c= malloc(sizeof(Coordinate));
	int EarthCircumference= 40075;
	int EarthPerimeter = 40000;
	c->x= (EarthCircumference*cosf(lat)*lon)/360; // 1° = RAYON*COS(LAT)
	c->y=(lat*EarthPerimeter)/360;  //1°= LAT*RAYON
	printf("LONG :%f -> LAT: %f  \n", c->x, c->y);
	return c;
}


Node* initNoeud(int id, float lat, float lon, char visible){
	Node * n= malloc(sizeof(Node));
	n->id=id;
	n->c= malloc(sizeof(Coordinate));
	n->c= conversionLatLon(lat, lon);
	n->visible= visible;
	return n;
}

Bounds* initBounds(float lat_min,float lat_max, float lon_min, float lon_max){
	Bounds *b=malloc(sizeof(Bounds));
	b->min =malloc(sizeof(Coordinate)); 
	b->max = malloc(sizeof(Coordinate));
	b->min= conversionLatLon(lat_min, lon_min);
	b->max= conversionLatLon(lat_max, lon_max);
	b->max->x = b->max->x - b->min->x;
	b->max->y = b->max->y - b->min->y;
	b->min->x=0;
	b->min->y=0;
	return b;
}


float distanceXY(float x1, float y1, float x2, float y2){
	return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}


float distanceY(float y1, float y2){
	return distanceXY(0, y1, 0, y2);
}

float distanceX(float x1, float x2){
	return distanceXY(x1, 0, x2, 0);
}

Node* distanceToBounds(Bounds *b, Node* n){
	n->c->x = distanceX(b->min->x, n->c->x);
	n->c->y = distanceY(b->min->y, n->c->x);
	return n;
}


float distanceLatLon(float lat1, float lon1, float lat2, float lon2){
	int EarthRayon = 6378.137;
	lon1= lon1*M_PI/180;
	lon2= lon2*M_PI/180;
	lat1= lat1*M_PI/180;
	lat2= lat2*M_PI/180;
	float dlon= (lon2-lon1)/2;
	float dlat= (lat2-lat1)/2;
	float a = sinf(dlat)*sinf(dlat)+ cosf(lat1)*cosf(lat2) *sinf(dlon)*sinf(dlon);
	return EarthRayon *2 *atan2(sqrt(a), sqrt(1-a));	
}

int main(){
	Coordinate *c = conversionLatLon(48.9141080,2.2569605);
	Coordinate *c1= conversionLatLon(48.9141155,2.2570123);
	float d = distanceXY(c1->x, c1->y, c->x, c->y);
	float d1 = distanceLatLon(48.9141080, 2.2569605, 48.9141155, 2.2570123);
	printf("%f \n%f \n", d, d1);
	conversionLatLon(50,1);
	return 0;
}