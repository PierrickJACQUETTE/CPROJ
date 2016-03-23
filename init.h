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


//refListNode* initRefListNode(unsigned long n, refListNode* next);

/**
 * \fn ListNode* initListNode();
 * \brief initialise a list of Node
 * 
 * \param first represente the id of first Node in the list 
 * \return ListNode*
 */
ListNode* initListNode(unsigned long first);

/**
 * \fn ListNode* addRefListNode();
 * \brief add a Node in a list of Node
 *
 * \param n represente the id of the Node 
 * \param l is the list where the Node will be add
 * \return ListNode*
 */
ListNode* addRefListNode(unsigned long n, ListNode *l);

/**
 * \fn Tag* initTag(char* key, char* value,Color *c);
 * \brief initialise a Tag
 * 
 * \param key represente the key of the tag
 * \param value represente the value of the tag
 * \param c represente the color for the tag  
 * \return ListNode*
 */
Tag* initTag(char* key, char* value,Color *c);

/**
 * \fn Way* initWay(unsigned long id, char* visible, ListNode* ln, Tag* tag,int size);
 * \brief initialise a Way
 * \param id represente the id of the way
 * \param visible represente if the way is visible or not
 * \param ln represente the ListNode of the way
 * \param tag represente the tag of the way
 * \param size represente the size of the way 
 * \return Way*
 */
Way* initWay(unsigned long id, char* visible, ListNode* ln, Tag* tag,int size);

/**
 * \fn Tag* goodTag(char * k, char *v,Tag **ref);
 * \brief analyse if a tag could be stock 
 * \param key represente the key of the tag
 * \param value represente the value of the tag
 * \param ref is a table with all the tag which it should be stock
 * \return Tag*
 */
Tag* goodTag(char * k, char *v,Tag **ref);

/**
 * \fn Relation* initRelation(unsigned long id, char* visible, ListWay* lw, Tag* tag);
 * \brief initialise a Relation
 * \param id represente the id of the Relation
 * \param visible represente if the relation is visible or not
 * \param lw represente the ListWay of the relation
 * \return Realtion*
 */
Relation* initRelation(unsigned long id, char* visible, ListWay* lw);

/**
 * \fn ListWay* initListWay();
 * \brief initialise a list of Way
 * 
 * \param first represente the id of the first Way in the list 
 * \return ListWay*
 */
ListWay* initListWay(unsigned long first);
/**
 * \fn ListWay* addRefListWay();
 * \brief add a Way in a list of Way
 *
 * \param way represente the id of the way
 * \param role is the role that this way represente in a relation 
 * \param lw is the list where the way will be add
 * \return ListWay*
 */
ListWay* addRefListWay(unsigned long way,char* role, ListWay* lw);


/**
 * \fn ListRelation* initListRelation();
 * \brief initialise a list of Relation
 * 
 * \param first represente the id of the first Relation in the list 
 * \return ListRelation*
 */
ListRelation* initListRelation(Relation* first);

/**
 * \fn ListRelation* addRefListRelation();
 * \brief add a Relation in a list of Realtion
 *
 * \param id represente the relation to add 
 * \param lr is the list where the Relation will be add
 * \return ListRelation*
 */
ListRelation* addRefListRelation(Relation *id ,ListRelation* lr);

/**
 * \fn Map* initMap()
 * \brief initalise a Map from OpenStreetMap
 *
 * \return Map*
 */
Map* initMap();
#endif
