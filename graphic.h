/**
* \file graphic.h
* \brief Display the Node and the way from a map
* \author Isabelle MARINO Pierrick JACQUETTE Hafça TIRICHINE
* \date 19 april 2016
*
*/

#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "evenement.h"

/**
* Fonction that creates a window with the right scales
* @param  Map* is the pointer to the information of map
* @param  char* typeOfDessin is the line or ponct
* @param  char* signal is the optional signal to know when the map is all printed
*/
void printMap(Map* map, char* typeOfDessin, char* signal);

#endif /* __GRAPHIC_H__ */
