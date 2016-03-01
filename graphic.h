#ifndef __CORE_H__
#define __CORE_H__

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdlib.h>
#include <GL/glu.h>
#include "Core.h"

#endif

void affichage(int xClick,int yClick);
int miseAEchelleAbs(float x, Bounds* bounds);
int miseAEchelleOrd(float x, Bounds* bounds);
void parcoursAvl(Avl *a, Bounds* bounds);
void evenement();
void printMap(Map* map);



