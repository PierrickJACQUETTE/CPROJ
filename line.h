/**
* \file line.h
* \brief This file displays polygons on the map depending on what is stored in the different structures
* \author Isabelle MARINO Pierrick JACQUETTE Hafça TIRICHINE
* \date 18 April 2016
*
*/

#ifndef __LINE_H__
#define __LINE_H__

#include "conversionElements.h"
#include "Avl.h"

extern Map * map;
int drawContour; // par defaut 1 = true
int drawNumber; // nombre de fois que l'on a tracer les ways

/**
* \fn  parcoursListWay(Map *map);
* \brief Courses way the list
*
*/
void parcoursListWay();

#endif /* __LINE_H__ */
