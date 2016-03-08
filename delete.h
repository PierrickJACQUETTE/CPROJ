/**
 * \file init.h
 * \brief Initialisation of the principal structure
 * \author Isabelle MARINO Pierrick JACQUETTE Hafça TIRICHINE
 * \date 25 february 2016
 *
 *
 */

#ifndef __DELETE_H__
#define __DELETE_H__

#include "Avl.h"

/**
 * Frees the memory tree
 * @param avl Self-balancing binary search tree
 */
void delete(Avl** avl);

/**
 * Frees the memory of a Map
 * @param Map which is deleted
 */
void deleteMap(Map *map);




#endif
