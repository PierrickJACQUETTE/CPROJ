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
#include "evenement.h"
#include "point.h"
#include "line.h"

/**
* Fonction that creates a window with the right scales, browse the avl tree by calling the "parcoursAvl" fonction
* and displays it to the screen by calling the "evenement" fonction
* @param  Map* is the pointer to the information of map
* @param  *typeOfDessin is the line or ponct
*/
void printMap(Map* map,char* typeOfDessin);

#endif /* __GRAPHIC_H__ */
