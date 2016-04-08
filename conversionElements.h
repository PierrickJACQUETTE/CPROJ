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

extern int windows_Height;
extern int windows_Width;
extern SDL_Renderer* renderer;
extern int quit;

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
 * \fn This method allows to normalize coordinates functions of the vector size
 * @param  a      float Coordinate x1
 * @param  b      float Coordinate x2
 * @param  length float size of vector
 * @return        the size of the normalize vector
 */
float normalize(float a, float b,float length);

/**
 * This method calculates the angle between two vectors.
 * The returned value is in degrees
 *
 * @param  ax float X coordinate of point a
 * @param  ay float Y coordinate of point a
 * @param  bx float X coordinate of point b
 * @param  by float Y coordinate of point b
 * @param  cx float X coordinate of point c
 * @param  cy float Y coordinate of point c
 * @return    float : The angle between the two vectors AB and BC (degree)
 */
float angle(float ax, float ay, float bx,float by,float cx,float cy);

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
* \return float the distance
*/
float distanceLatLon(float lat1, float lon1, float lat2, float lon2);

/**
 * \fn This method calculates the points to draw the full polygon between two lines when is not extremite
 * \param float b The known point center
 * \param float e The new point
 * \param int signe : This shows whether one is added or subtracted depending on the given angle
 * \param Sint16 tab : The table points to draw the polygon
 * \return Sint16 The table points to draw the polygon
*/
Sint16* midle(float b, float e, int signe, Sint16 tab[4]);

/**
 * \fn This method calculates the points to draw the full polygon between two lines for the extremites
 * \param float a The known point center
 * \param float d The new point
 * \param float e The new point 
 * \param Sint16 tab : The table points to draw the polygon
 * \return Sint16 The table points to draw the polygon
*/
Sint16* extremite(float a, float d, float e, Sint16 tab[4]);


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

/**
 * According initialising the bottom of the window
 * @param  red      int color R
 * @param  blue     int color G
 * @param  green    int color B
 * @param  oppacity int oppacity color
 * @return          int Lets see if everything went well
 */
int colorBackground(int red, int blue, int green,int oppacity);

/**
 * According initialising the bottom of the window by default
 * @return int Lets see if everything went well
 */
int colorBackgroundDefault();

#endif /* __CONVERSIONELEMENTS_H__ */
