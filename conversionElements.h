/**
* \file conversionElements.h
* \brief Declare fonctions to convert elements
* \author Isabelle MARINO Pierrick JACQUETTE Hafça TIRICHINE
* \date 6 April 2016
*
* Declare fonctions to convert elements: nodes, bounds
* Calculate distances between points
* Declare fonctions that put coordinates values to the window scale
*
*
*/

#ifndef __CONVERSIONELEMENTS_H__
#define __CONVERSIONELEMENTS_H__


#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "Core.h"

extern const int WINDOW_HEIGHT;
extern const int WINDOW_WIDTH;
extern SDL_Renderer* renderer;


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
* \fn Bounds* convertBounds(Bounds *b )
* \brief convert the bounds of the map to the min is (0,0)
*
* \param b Bounds that represente the bounds of the map before the changement
* \return Bounds*
*/
Bounds* convertBounds(Bounds *b );

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
* \return float
*/
float distanceLatLon(float lat1, float lon1, float lat2, float lon2);

/**
* Fonction that puts the ordonate's X value to the window scale
*
* \param  float x the ordonate value of the point
* \param  float y Coordinate bounds the window's bounds
* \param  int size Size window's
* \return  value of the ordonate put to scale
*/
float miseAEchelleX(float x, float y,int size);

/**
* Fonction that puts the ordonate's X value to the window scale
*
* \param  float x the ordonate value of the point
* \param  float y Coordinate bounds the window's bounds
* \param  int size Size window's
* \return  value of the ordonate put to scale
*/
float miseAEchelleY(float x, float y,int size);


#endif /* __CONVERSIONELEMENTS_H__ */
