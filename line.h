#ifndef __LINE_H__
#define __LINE_H__

#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <GL/glu.h>
#include "Core.h"
#include "Avl.h"

void printPoint(float x,float y);
float echelle(float x, float y,int size);
void startLine();
void endLine();
void sizeColor(Color * c);
void drawWay(Map* map,Way * way);
void parcoursListWay(Map *map,int width,int heigth, SDL_Renderer* renderer);

#endif /* __LINE_H__ */
