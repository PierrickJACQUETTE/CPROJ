/**
* \file line.h
* \brief This file displays polygons on the map depending on what is stored in the different structures
* \author Isabelle MARINO Pierrick JACQUETTE Hafça TIRICHINE
* \date 27 mars 2016
*/

#ifndef __LINE_H__
#define __LINE_H__

#include "conversionGraphic.h"
#include "Avl.h"

/**
* \fn  parcoursListWay(Map *map);
* \brief Courses way the list
*
* \param map This represents all of our data
* \param renderer That's where we draw

*/
void parcoursListWay(Map *map);

#endif /* __LINE_H__ */
