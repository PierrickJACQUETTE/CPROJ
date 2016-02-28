/**
* \file parseur.h
* \brief Declare fonctions needed to parse the xml document
* \author Hafça TIRICHINE Isabelle MARINO Pierrick JACQUETTE 
* \version 0.1
* \date 28 february 2016
*
* Declaration of fonctions needed to parse the xml document
*
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include "conversionElements.h"

/*Fonction that parses a file*/
static void parseDoc(char* filename);

/*Fonction that parses the elements needed*/
static void parseElements(xmlDocPtr doc, xmlNodePtr cur);

Bounds* parseBounds (xmlNodePtr cur); 
void parseNode (xmlDocPtr doc, xmlNodePtr cur);
void parseWay (xmlDocPtr doc, xmlNodePtr cur);

