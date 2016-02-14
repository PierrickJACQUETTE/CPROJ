#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

typedef struct Noeud Noeud;
struct Noeud{
	const xmlChar *name; //the name of the node
	int id; //the node's id
	int lat; //the node's latitude
	int lon; //the node's longitude	
};

/*Fonction that parses a file*/
static void parseDoc(char* filename);

/*Fonction that prints the elements needed and the attributs with their content*/
static void print_elements(xmlNode * a_node);

