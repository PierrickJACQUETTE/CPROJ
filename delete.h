/**
* \file delete.h
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
* Frees the memory of a Coordinate
* @param c Coordinate which is deleted
*/
void deleteCoordinate(Coordinate *c);

/**
* Frees the memory of a Bounds
* @param b  Bounds which is deleted
*/
void deleteBounds(Bounds *b);

/**
* Frees the memory of a Color
* @param c  Color which is deleted
*/
void deleteColor(Color *c);

/**
* Frees the memory of a Tag
* @param t Tag which is deleted
*/
void deleteTag(Tag *t);

/**
* Frees the memory of a TabTag
* @param t Tag which is deleted
*/
void deleteTabTag(Tag **t);

/**
* Frees the memory of a RefListNode
* @param r  RefListNode which is deleted
*/
void deleteRefListNode(refListNode *r);

/**
* Frees the memory of a ListNode
* @param l  ListNode which is deleted
*/
void deleteListNode(ListNode *l);

/**
* Frees the memory of a refListWay
* @param r  refListWay which is deleted
*/
void deleteRefListWay(refListWay *r);

/**
* Frees the memory of a ListWay
* @param l ListWay which is deleted
*/
void deleteListWay(ListWay *l);

/**
* Frees the memory of a refListRel
* @param r  refListRel which is deleted
*/
void deleteRefListRel(refListRel *r);

/**
* Frees the memory of a ListRelation
* @param l  ListRelation which is deleted
*/
void deleteListRelation(ListRelation *l);

/**
* Frees the memory of a Node
* @param n Node which is deleted
*/
void deleteNode(Node *n);

/**
* Frees the memory of a Way
* @param w Way which is deleted
*/
void deleteWay(Way *w);

/**
* Frees the memory of a Relation
* @param r Relation which is deleted
*/
void deleteRelation(Relation *r);

/**
* Frees the memory of a avl
* @param avl  Avl which is deleted
*/
void deleteAvl(Avl** avl,int isNode);

/**
* Frees the memory of a Map
* @param Map which is deleted
*/
void deleteMap(Map *map);

#endif
