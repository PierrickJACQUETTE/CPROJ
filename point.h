#ifndef __POINT_H__
#define __POINT_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdlib.h>
#include <GL/glu.h>
#include "Core.h"


/**
* Fonction that draws a point in the window
*
* @param  float x the coordinate of the abscisse of the point
* @param  float y the coordinate of the ordonate of the point
* @return  nothing it just draws the point
*/
void affichage(float x,float y);

/**
* Fonction that puts the ordonate's value to the window scale
*
* @param  float x the ordonate value of the point
* @param  float y Coordinate bounds the window's bounds
* @param  int size Size window's
* @return  value of the ordonate put to scale
*/
float miseAEchelle(float x, float y,int size);

/**
* Fonction that browse the avl tree and displays the nodes in the window by calling the affichage fonction
*
* @param  Avl **a is the pointer to the avl of node we need to browse
* @param  Bounds* bounds the window's bounds
* @return  value of the abscisse put to scale
*/
void parcoursAvl(Avl **a, Bounds* bounds,int w,int h);

#endif /* __POINT_H__ */
