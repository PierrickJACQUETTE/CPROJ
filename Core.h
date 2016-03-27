/**
* \file Core.h
* \brief Declaration of structure for the project
* \author Isabelle MARINO Pierrick JACQUETTE Hafça TIRICHINE
* \date 02 mars 2016
*
* Declaration of structure for the project open stree map
*
*/

#ifndef __CORE_H__
#define __CORE_H__

#include <stdio.h>

/**
* \struct Coordinate
* \brief Objet that represente the coordinate of a point
*
* x is the abscissa's coordinate
* y is the ordely's coordinate
*/

typedef struct{
	float x;
	float y;
}Coordinate;

/**
* \struct Bounds
* \brief Objet that represente bounds for an open street map
*
* min is the coordinates of the minimum's point that it can have
* max is the coordinates of the maximum's point that it can have
*/
typedef struct{
	Coordinate* min;
	Coordinate* max;
}Bounds;

/**
* \struct Color
* \brief Objet that represente color in rgb
*
* red is the proportion of red in the color
* green is the proportion of green in the color
* bleu is the proportion of bleu in the color
*/
typedef struct{
	int red;
	int green;
	int blue;
}Color;


/**
* \struct Tag
* \brief Objet that represente tags for an open street map
*
* tagKey is the key of the tags
* tagValue is the value of the tags
* Color is the color of this type of element
* thick represente the thickness of the way
*/
typedef struct{
	char* tagKey;
	char* tagValue;
	Color* c;
	int thick;
}Tag;



/**
* \struct Node
* \brief Objet that represente a point in openstreetmap
*
* id represente the name of this object
* c represente where is this point on the map
* visible represente if this point is visible or not
*/
typedef struct{
	unsigned long id;
	Coordinate* c;
	char* visible; // True,False;
}Node;

/**
* \struct refList
* \brief Objet that represente a Node and the next Node
*
* nd is the principal id Node
* next is the next Node
*/
typedef struct refListNode{
	unsigned long nd;
	struct refListNode* next;
}refListNode;

/**
* \struct ListNode
* \brief Objet that represente a List of Node
*
* firstRef is the first Node of the List
* lastRef is the last Node of the List
*/
typedef struct{
	refListNode * firstRef;
	refListNode * lastRef;
}ListNode;

/**
* \struct refListWay
* \brief Objet that represente a long and the next long (id)
*
* way is the principal way
* role is the role of the way
* next is the next way
*/
typedef struct refListWay{
	unsigned long way;
	char *role;
	struct refListWay * next;
}refListWay;

/**
* \struct List
* \brief Objet that represente a List of Way
*
* firstRef is the first Way of the List
* lastRef is the last Way of the List
*/
typedef struct{
	refListWay * firstRef;
	refListWay * lastRef;
}ListWay;

/**
* \struct Way
* \brief Objet that represente a construction like a building or a garden in openstreetmap
*
* id represente the name of this object
* listNd is the list of the differents node that it compose this object
* visible represente if this point is visible or not
* tag is the type of this object
* size is the number of Node
*/
typedef struct{
	unsigned long id;
	ListNode* listNd;
	char* visible; // T = true, F= false;
	Tag* tag;
	int size;
}Way;


/**
* \struct Relation
* \brief Objet that represente a construction like a building or a garden in openstreetmap
*
* id represente the name of this object
* listW is the list of the differents way that it compose this object
* listN is the list of the differents node that it compose this object
* visible represente if this point is visible or not
* tag is the type of this object
*/
typedef struct{
	unsigned long id;
	ListWay* listW;
	ListNode* listN;
	Tag* tag;
	char* visible; // T = true, F= false;
}Relation;

/**
* \struct refListRel
* \brief Objet that represente a long and the next long (id)
*
* Relation is the principal relation
* next is the next relation
*/
typedef struct refListRel{
	Relation* relation;
	struct refListRel * next;
}refListRel;


/**
* \struct List
* \brief Objet that represente a List of Relation
*
* firstRef is the first Relation of the List
* lastRef is the last Relation of the List
*/
typedef struct{
	refListRel * firstRef;
	refListRel * lastRef;
}ListRelation;


/**
* \struct Avl
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
	Way *way;
	int height;
	struct sAvl* left,* right;
}Avl;

/**
* \struct Map
* \brief This is the structure for representing a Map from OpenstreetMap .
* Bounds of a Map
* Avl of Node
* Avl of Way
* List Way
* List of relation
* Table of Tag that represente the principal tag and their particularities.
*/
typedef struct{
	Bounds* bounds;
	Avl* avl;
	Avl* avlWay;
	ListWay* listWay;
	ListRelation * listRelation;
	Tag** referenceTag;
}Map;

#endif  /* __CORE_H__ */
