#ifndef __POINT_H__
#define __POINT_H__

#include "conversionGraphic.h"

/**
* Fonction that draws a point in the window
*
* @param  float x the coordinate of the abscisse of the point
* @param  float y the coordinate of the ordonate of the point
* @param  renderer r the renderer which draw
* @return  nothing it just draws the point
*/
void affichage(float x, float y, SDL_Renderer* renderer);

/**
* Fonction that browse the avl tree and displays the nodes in the window by calling the affichage fonction
*
* @param  Avl **a is the pointer to the avl of node we need to browse
* @param  Bounds* bounds the window's bounds
* @param  renderer r the renderer which draw
* @return  value of the abscisse put to scale
*/
void parcoursAvl(Avl **a, Bounds* bounds, int w, int h, SDL_Renderer* renderer);

#endif /* __POINT_H__ */
