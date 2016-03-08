/**
* \file parseur.h
* \brief Declare fonctions needed to parse the xml document
* \author Hafça TIRICHINE Isabelle MARINO Pierrick JACQUETTE
* \date 02 mars 2016
*
* Declaration of fonctions needed to parse the xml document
*
*/

#ifndef __PARSEUR_H__
#define __PARSEUR_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "Avl.h"


/**
* Fonction that parses a file, get the root_element and, if there is no problem with the file, calls the parseElements fonction 
* @param  a char* filename which is the file name
* @return  a pointer to a map which is a structure where we put the avl and the bounds 
*/
Map* parseDoc(char* filename);

/**
* Fonction that parses the elements needed: the bounds, nodes and ways.
* It creates a map and inserts the bounds element
* it creates an AVL, initialise it and add's the nodes.
* at the end, it adds the avl to the map structure and returns the map
* @param  xmlDocPtr doc which is the file parsed
* @param  xmlNodePtr cur which is a pointer to the current node (at the beginning, it is called with the root node)
* @return  a pointer to a map which is a structure created where we put the avl and the bounds 
*/
Map* parseElements(xmlDocPtr doc, xmlNodePtr cur);

/**
* Fonction that parses the "bounds" element
* It initialise the bounds structure we need for the map with the coordinates 
* @param  xmlNodePtr cur which is a pointer to the current node (here,the bounds node)
* @return  pointer to a Bound structure where we put the coordinates we got from the bounds element
*/
Bounds* parseBounds (xmlNodePtr cur);

/**
* Fonction that parses a node
* @param  xmlDocPtr doc which is the file parsed
* @param  xmlNodePtr cur which is a pointer to the current node 
* @param  Bounds *bounds which is the structure of the bounds element we need to init the nodes
* @return  a pointer to a node structure created whith the attributes we got from the parsing
*/
Node* parseNode (xmlDocPtr doc, xmlNodePtr cur, Bounds *bounds);

/**
* Fonction that parses a way
* @param  xmlDocPtr doc which is the file parsed
* @param  xmlNodePtr cur which is a pointer to the current node 
* @return  a pointer to a way structure created whith the attributes we got from the parsing
*/
Way* parseWay (xmlDocPtr doc, xmlNodePtr cur);

#endif /* __PARSEUR_H__ */
