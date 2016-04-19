/**
* \file point.h
* \brief Declaration of fonctions that draws the map by using points
* \author Isabelle MARINO Pierrick JACQUETTE Hafça TIRICHINE
* \date 6 April 2016
*
*/

#ifndef __POINT_H__
#define __POINT_H__

#include "conversionElements.h"

/**
* Fonction that draws a point in the window
*
* @param  float x the coordinate of the abscisse of the point
* @param  float y the coordinate of the ordonate of the point
* @return  nothing it just draws the point
*/
void affichage(float x, float y);

/**
* Fonction that browse the avl tree and displays the nodes in the window by calling the affichage fonction
*
* @param  Avl **a is the pointer to the avl of node we need to browse
* @param  Bounds* bounds the window's bounds
* @return  value of the abscisse put to scale
*/
void parcoursAvl(Avl **a, Bounds* bounds);

#endif /* __POINT_H__ */
