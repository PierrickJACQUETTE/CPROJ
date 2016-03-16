/**
 * \file init.h
 * \brief Initialisation of the principal structure
 * \author Isabelle MARINO Pierrick JACQUETTE Hafça TIRICHINE
 * \date 25 february 2016
 *
 *
 */

#ifndef __INIT_H__
#define __INIT_H__

#include <string.h>
#include "conversionElements.h"
#include "Core.h"

/**
 * \fn initNode(unsigned long id, float lat, float lon, char visible, Bounds* b)
 * \brief initalise a Node for a point in a map
 *
 * \param id represente the name of this point
 * \param lat float that represente the latitude of this point
 * \param lon float that represente the longitude of this point
 * \param visible char that represente if the node is visibl or not
 * \param b Bounds that represente the bounds of the map
 * \return Node*
 */
Node* initNode(unsigned long id, float lat, float lon, char* visible, Bounds *b);


/**
 * \fn initBounds(float lat_min,float lat_max, float lon_min, float lon_max)
 * \brief initialise the bounds of a map
 *
 * \param lat_max float that represente the maximal latitude on the map
 * \param lon_max float that represente the maximal longitude on the map
 * \param lat_min float that represente the minium latitude on the map
 * \param lon_min float that represente the minimum longitude on the map
 * \return Bounds*
 */
Bounds* initBounds(float lat_min,float lat_max, float lon_min, float lon_max);


/**
 * \fn Tag** initReferenceTag();
 * \brief initialise the table of prinicpal tag (color, keyx and value)
 *
 * \return Tag**
 */
Tag** initReferenceTag();


refListNode* initRefListNode(unsigned long n, refListNode* next);

ListNode* initListNode(unsigned long first);

ListNode* addRefListNode(unsigned long n, ListNode *l);

Tag* initTag(char* key, char* value,Color *c);

Way* initWay(unsigned long id, char* visible, ListNode* ln, Tag* tag);

Tag* goodTag(char * k, char *v,Tag **ref);
Relation* initRelation(unsigned long id, char* visible, ListWay* lw, Tag* tag);
refListWay* initRefListWay(unsigned long  w, refListWay* next);
ListWay* initListWay(unsigned long first);
ListWay* addRefListWay(unsigned long way, ListWay* lw);
Map* initMap();
#endif
