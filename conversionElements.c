#include "conversionElements.h"


Coordinate* conversionLatLon(float lat, float lon){
	Coordinate *c= malloc(sizeof(Coordinate));
	//int EarthCircumference= 40075;
	//int EarthPerimeter = 40000;
	//c->x= (EarthCircumference* /*cosf(lat)*/ lon)/360; // 1° = RAYON*COS(LAT)
	//c->y=(lat*EarthPerimeter)/360;  //1°= LAT*RAYON
	c->x=lon;
	c->y=lat;
	return c;
}


Bounds* convertBounds(Bounds *b ){
	//b->max->x = b->max->x - b->min->x; 
	b->max->x= distanceLatLon(b->min->y, b->min->x, b->min->y, b->max->x);
	//b->max->y = b->max->y - b->min->y;
	b->max->y= distanceLatLon(b->min->y, b->min->x, b->max->y, b->min->x); 
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
	int EarthRayon = 6371;
	lon1= lon1*M_PI/180;
	lon2= lon2*M_PI/180;
	lat1= lat1*M_PI/180;
	lat2= lat2*M_PI/180;
	float dlon= (lon2-lon1)/2;
	float dlat= (lat2-lat1)/2;
	float a = sinf(dlat)*sinf(dlat)+ cosf(lat1)*cosf(lat2) *sinf(dlon)*sinf(dlon);
	return EarthRayon *2 *atan2(sqrt(a), sqrt(1-a));
}
