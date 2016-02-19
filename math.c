/**
 * \file math.c
 * \brief Calculate the transformation for a node by open street map
 * \author Isabelle MARINO Pierrick JACQUETTE Hafca TIRICHINE
 * \version 0.1
 * \date 19 february 2016
 *
 * Calculate node's coordinates: transform an openstreetmap coordinates to an standar coordinates
 * Caculate the bounds proportion   
 *
 */

#ifndef __CORE_H__
#define __CORE_H__
#include <stdio.h>
#include <math.h>
#include "core.h"
#include <stdlib.h>


/**
 * \fn coordinate* conversionLatLon(float lat, float lon)
 * \brief calculate the coordinate for a point in openstreetmap
 *
 * \param lat float that represente the latitude of this point
 * \param lon float that represente the longitude of this point
 * \return coordinate *
 */

coordinate* conversionLatLon(float lat, float lon){
	lat=(lat*40030)/360;
	printf("LAT : %f   -> ", lat);
	int error; 
	// JE DOIS AJOUTER LES ERREUR EN FONCTION DE L'OU L'ON SE TROUVE POUR LA LONGITUDES CAR CIRCONFERENCE DIFFERENTES AU POLE (MIN =0) ET A L'ÉQUATEUR (MAX)
	lon= (lon*40030)/360;
	printf("LONG :%f \n", lon);
	coordinate *c= malloc(sizeof(coordinate));
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
 * \return bounds*
 */
bounds* initBounds(float lat_min,float lat_max, float lon_min, float lon_max){
	bounds *b=malloc(sizeof(bounds));
	b->min =malloc(sizeof(coordinate)); 
	b->max = malloc(sizeof(coordinate));
	b->min= conversionLatLon(lat_min, lon_min);
	b->max= conversionLatLon(lat_max, lon_max);
	b->max->x = b->max->x - b->min->x;
	b->max->y = b->max->y - b->min->y;
	b->min->x=0;
	b->min->y=0;
	return b;
}

/**
 * \fn coordinate* coordinatesNode(coordinate *min, float lat, float lon)
 * \brief calculate the coordinate for a point in a map
 *
 * \param min represente the minimum point that we have on the map
 * \param lat float that represente the latitude of this point
 * \param lon float that represente the longitude of this point
 * \return coordinate *
 */
coordinate* coordinatesNode(coordinate *min, float lat, float lon){
	coordinate *c= malloc(sizeof(coordinate));
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
	coordinate *c1 = conversionLatLon(lat1, lon1);
	coordinate *c2= conversionLatLon(lat2, lon2);
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
	coordinate *c = conversionLatLon(48.8289403,2.3798326);
	printf("LONG :%f \n", c->y);
	conversionLatLon(48.8310657,2.3810055);
	return 0;
}

#endif /* __CORE_H__ */


// pour faire des simulations voilà un site plutot pas mal


 // http://www.lexilogos.com/calcul_distances.htm // 
