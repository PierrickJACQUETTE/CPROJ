/**
 * \file conversionElements.h
 * \brief Daclare fonction to calculate the transformation for a node by open street map
 * \author Isabelle MARINO Pierrick JACQUETTE Hafca TIRICHINE
 * \version 0.1
 * \date 25 february 2016
 *   
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

Coordinate* conversionLatLon(float lat, float lon);


/**
 * \fn initNode(int id, float lat, float lon, char visible)
 * \brief initalise a Node for a point in a map
 *
 * \param id represente the name of this point 
 * \param lat float that represente the latitude of this point
 * \param lon float that represente the longitude of this point
 * \param visible char that represente if the node is visibl or not
 * \return Node*
 */
Node* initNode(int id, float lat, float lon, char visible);


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
Bounds* initBounds(float lat_min,float lat_max, float lon_min, float lon_max);


/**
 * \fn void distanceXY(float x1, float y1, float x2, float y2)
 * \brief calculate the distance beetween 2 points in a carthesien repere
 *
 * \param x1 float that represente the abcisse of point 1 
 * \param y1 float that represente the ordinate of point1 
 * \param x2 float that represente the abcisse of point 2
 * \param y2 float that represente the ordinate of point2 
 * \return float
 */
float distanceXY(float x1, float y1, float x2, float y2);

/**
 * \fn void distanceY(float y1, float y2)
 * \brief calculate the ordinate's distance beetween 2 points in a carthesien repere
 *
 * \param y1 float that represente the ordinate of point1 
 * \param y2 float that represente the ordinate of point2 
 * \return float
 */
float distanceY(float y1, float y2);

/**
 * \fn void distanceX(float x1, float x2)
 * \brief calculate the abscisse's distance beetween 2 points in a carthesien repere
 *
 * \param x1 float that represente the abcisse of point 1 
 * \param x2 float that represente the abcisse of point 2
 * \return float
 */
float distanceX(float x1, float x2);

/**
 * \fn distanceToBounds(Bounds *b, Node* n)
 * \brief calcule the distance between a Node and the Bounds's map
 *
 * \param n represente the point on the map 
 * \param b represente the bounds of the map
 * \return Node*
 */
Node* distanceToBounds(Bounds *b, Node* n);

/**
 * \fn void distanceLatLon(float lat1, float lon1, float lat2, float lon2)
 * \brief calculate the distance beetween 2 points in a map
 *
 * \param lat1 float that represente the latitude of point 1 
 * \param lon1 float that represente the longitude of point1 
 * \param lat2 float that represente the latitude of point 2
 * \param lon2 float that represente the longitude of point2 
 * \return void
 */
void distanceLatLon(float lat1, float lon1, float lat2, float lon2);


#endif /* __CORE_H__ */
