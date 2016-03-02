/**
 * \file graphic.h
 * \brief Display the Node and the way from a map
 * \author Isabelle MARINO Pierrick JACQUETTE Hafça TIRICHINE
 * \date 2 march 2016
 *
 */

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdlib.h>
#include <GL/glu.h>
#include "Core.h"

/**
* Fonction that draws a point in the window
*
* @param  int xClick the coordinate of the abscisse of the point
* @param  int yClick the coordinate of the ordonate of the point
* @return  nothing it just draws the point
*/
void affichage(int xClick,int yClick);

/**
* Fonction that puts the abscisse's value to the window scale
* 
* @param  float x the abscisse value of the point
* @param  Bounds* bounds the window's bounds
* @return  value of the abscisse put to scale
*/
int miseAEchelleAbs(float x, Bounds* bounds);

/**
* Fonction that puts the ordonate's value to the window scale 
*
* @param  float x the ordonate value of the point
* @param  Bounds* bounds the window's bounds
* @return  value of the ordonate put to scale
*/
int miseAEchelleOrd(float x, Bounds* bounds);

/**
* Fonction that browse the avl tree and displays the nodes in the window by calling the affichage fonction
*
* @param  Avl **a is the pointer to the avl of node we need to browse
* @param  Bounds* bounds the window's bounds
* @return  value of the abscisse put to scale
*/
void parcoursAvl(Avl **a, Bounds* bounds);

/**
* Fonction that permit the display
* While we haven't closed the window it is still on the screen
* When we do close it, it displays a message saying we closed it
* This event is handeled by a loop : while the statut is "CONTINUE" we keep the window to the screen
* Otherwise, we close it and change the statut to "QUIT"
*
* @param  Avl **a is the pointer to the avl of node we need to browse
* @param  Bounds* bounds the window's bounds
* @return  value of the abscisse put to scale
*/
void evenement();

/**
* Fonction that creates a window with the right scales, browse the avl tree by calling the "parcoursAvl" fonction 
* and displays it to the screen by calling the "evenement" fonction
*
* @param  Avl **a is the pointer to the avl of node we need to browse
* @param  Bounds* bounds the window's bounds
* @return  value of the abscisse put to scale
*/
void printMap(Map* map);

#endif /* __GRAPHIC_H__ */



