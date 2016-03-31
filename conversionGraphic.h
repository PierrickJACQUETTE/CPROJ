#ifndef __CONVERSIONGRAPHIC_H__
#define __CONVERSIONGRAPHIC_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include "Core.h"


extern int heigth;
extern int width;
extern SDL_Renderer* renderer;

/**
* Fonction that puts the ordonate's X value to the window scale
*
* @param  float x the ordonate value of the point
* @param  float y Coordinate bounds the window's bounds
* @param  int size Size window's
* @return  value of the ordonate put to scale
*/
float miseAEchelleX(float x, float y,int size);

/**
* Fonction that puts the ordonate's X value to the window scale
*
* @param  float x the ordonate value of the point
* @param  float y Coordinate bounds the window's bounds
* @param  int size Size window's
* @return  value of the ordonate put to scale
*/
float miseAEchelleY(float x, float y,int size);


#endif
