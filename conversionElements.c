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

#ifndef __CORE_H__
#define __CORE_H__
#include <stdio.h>
#include <math.h>
#include "Core.h"
#include <stdlib.h>


/**
 * \fn Coordinate* conversionLatLon(float lat, float lon)
 * \brief calculate the Coordinate for a point in openstreetmap
 *
 * \param lat float that represente the latitude of this point
 * \param lon float that represente the longitude of this point
 * \return Coordinate *
 */

Coordinate* conversionLatLon(float lat, float lon){
	int error; 
	// JE DOIS AJOUTER LES ERREUR EN FONCTION DE L'OU L'ON SE TROUVE POUR LA LONGITUDES CAR CIRCONFERENCE DIFFERENTES AU POLE (MIN =0) ET A L'ÉQUATEUR (MAX)
	double rayon = 111.11;
	printf(" %f \n", cosf((lat*180)/M_PI)); // pour passer de radian en degre 
	lon= rayon*cosf((lat*180)/M_PI)*(lon*180)/M_PI; // 1° = RAYON*COS(LAT)
	printf("LONG :%f ->    ", lon);
	lat=(((lat*180)/M_PI)*40000)/360;  //1°= LAT*RAYON
	printf("LAT : %f   \n ", lat);
	Coordinate *c= malloc(sizeof(Coordinate));
	c->x=lat;
	c->y=lon;
	return c;
}

/**
 * \fn initBounds(float lat_min,float lat_max, float lon_min, float lon_max)
 * \brief initialise the bounds of a map
 *
 * \param lat_max float that represente the maximal latitude on the map
 * \param lon_max float that represente the maximal longitude on the map
 * \param lat_min float that represente the minium latitude on the map
 * \param lon_min float that represente the minimum longitude on the map
 * \return Bounds*
 */
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

/**
 * \fn Coordinate* CoordinatesNode(Coordinate *min, float lat, float lon)
 * \brief calculate the Coordinate for a point in a map
 *
 * \param min represente the minimum point that we have on the map
 * \param lat float that represente the latitude of this point
 * \param lon float that represente the longitude of this point
 * \return Coordinate *
 */
Coordinate* CoordinatesNode(Coordinate *min, float lat, float lon){
	Coordinate *c= malloc(sizeof(Coordinate));
	c=conversionLatLon(lat, lon);
	c->x = c->x- min->x;
	c->y = c->y - min->y;
	return c;

}

/**
 * \fn void distance(float lat1, float lon1, float lat2, float lon2)
 * \brief calculate the distance beetween 2 points
 *
 * \param lat1 float that represente the latitude of point 1 
 * \param lon1 float that represente the longitude of point1 
 * \param lat2 float that represente the latitude of point 2
 * \param lon2 float that represente the longitude of point2 
 * \return void
 */
void distance(float lat1, float lon1, float lat2, float lon2){
	Coordinate *c1 = conversionLatLon(lat1, lon1);
	Coordinate *c2= conversionLatLon(lat2, lon2);
	float distx= sqrt(pow(c2->x -c1->x, 2));
	float disty= sqrt(pow(c2->y - c1->y, 2));
}


/**
 * \fn int main (void)
 * \brief main function of this programme
 *
 * \return 0
 */
int main(){
	Coordinate *c = conversionLatLon(48.8289403,2.3798326);
	conversionLatLon(48.8310657,2.3810055);
	conversionLatLon(50,1);
	return 0;
}

#endif /* __CORE_H__ */


// pour faire des simulations voilà un site plutot pas mal


 // http://www.lexilogos.com/calcul_distances.htm // 
