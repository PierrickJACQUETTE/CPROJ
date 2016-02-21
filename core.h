/**
* \file core.h
* \brief Declaration of structure for the project
* \author Isabelle MARINO Pierrick JACQUETTE Hafca TIRICHINE
* \version 0.2
* \date 18 february 2016
*
* Declaratioin of structure for the project open stree map
*
*/
#include <stdio.h>

/**
 * \struct coordinate
 * \brief Objet that represente the coordinate of a point
 *
 * x is the abscissa's coordinate
 * y is the ordely's coordinate
 */

typedef struct{
	float x;
	float y;
}coordinate;

/**
 * \struct bounds
 * \brief Objet that represente bounds for an open street map
 *
 * min is the coordinates of the minimum's point that it can have
 * max is the coordinates of the maximum's point that it can have
 */
typedef struct{
	coordinate min;
	coordinate max;
}Bounds;

/**
 * \struct node
 * \brief Objet that represente a point in openstreetmap
 *
 * id represente the name of this object
 * c represente where is this point on the map
 * visible represente if this point is visible or not
 */
typedef struct{
 	int id;
	coordinate c;
	char visible; // T = true, F= false;
}Node;

/**
 * \struct way
 * \brief Objet that represente a construction like a building or a garden in openstreetmap
 *
 * id represente the name of this object
 * nd is the list of the differents node that it compose this object
 * visible represente if this point is visible or not
 * tag est the type of this object
 * k is the value of this object
 */
typedef struct{
	int id;
	//liste de Node nd à definir
	char visible; // T = true, F= false;
	char* tag;
	char* k;
}Way;

/**
* \struct Avl Avl.h
* \brief This is the structure for representing an AVL .
*
* This structure consists of:
* - the label : an int
* - the son left : tree pointer
* - the son right : tree pointer
* - the height of the tree : an int
*/
typedef struct sAvl{
  Node* node;
  int height;
  struct sAvl* left,* right;
}Avl;
