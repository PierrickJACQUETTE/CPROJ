#include "parseur.h"

void parseWay (xmlDocPtr doc, xmlNodePtr cur){
	xmlAttr *node_attr = cur->properties;
	xmlNodePtr tmpcur=NULL; 

	//we browse the element's properties list and we only print the attributs we need to
	while(node_attr != NULL){ 
		if( xmlStrcmp(node_attr->name,(const xmlChar *)"id")==0 
		|| xmlStrcmp(node_attr->name,(const xmlChar *)"visible")==0 )
		{
			printf("%s = %s\n", node_attr->name, (node_attr->children)->content);			
		}
		node_attr = node_attr->next;
	}
	tmpcur = cur->xmlChildrenNode;
	
	//while "way" has childs
	while(tmpcur != NULL){ 
		if (tmpcur->type == XML_ELEMENT_NODE) {
			if( xmlStrcmp(tmpcur->name,(const xmlChar *)"tag")==0 ){
				printf("< %s : k = %s, v = %s >\n", tmpcur->name, xmlGetProp(tmpcur, (const xmlChar *)"k"), xmlGetProp(tmpcur, (const xmlChar *)"v"));
			}
      	if( xmlStrcmp(tmpcur->name,(const xmlChar *)"nd")==0 ){
				printf("< %s : ref = %s >\n", tmpcur->name, xmlGetProp(tmpcur, (const xmlChar *)"ref"));
			}
      }
		tmpcur = tmpcur->next;
	}
}

void parseNode (xmlDocPtr doc, xmlNodePtr cur) {
	xmlAttr *node_attr = cur->properties; 
	
	//we browse the element's properties list and we only print the attributs we need to
	while(node_attr != NULL)
	{ 
		if( xmlStrcmp(node_attr->name,(const xmlChar *)"id")==0 
		|| xmlStrcmp(node_attr->name,(const xmlChar *)"visible")==0 
		|| xmlStrcmp(node_attr->name,(const xmlChar *)"lat")==0 
		|| xmlStrcmp(node_attr->name,(const xmlChar *)"lon")==0 )
		{
			printf("%s = %s\n", node_attr->name, (node_attr->children)->content);			
		}
		node_attr = node_attr->next;
	}
}

Bounds* parseBounds (xmlNodePtr cur) {
	Bounds *b;
	float minlat, minlon, maxlat, maxlon;
	
	minlat = strtof((const char *)(xmlGetProp(cur, (const xmlChar *)"minlat")),NULL);
	minlon = strtof((const char *)(xmlGetProp(cur, (const xmlChar *)"minlon")),NULL);
	maxlat = strtof((const char *)(xmlGetProp(cur, (const xmlChar *)"maxlat")),NULL);
	maxlon = strtof((const char *)(xmlGetProp(cur, (const xmlChar *)"maxlon")),NULL);
	printf("minlat: %f, minlon: %f, maxlat: %f, maxlon: %f \n",minlat,minlon,maxlat,maxlon);
	b = initBounds(minlat,maxlat,minlon,maxlon);
	return b;
}
		
/*Fonction that prints the elements needed and the attributs with their content*/
static void parseElements(xmlDocPtr doc, xmlNodePtr cur){
	//Bounds *b;
	cur = cur->xmlChildrenNode; 

	while (cur != NULL) {
		if (cur->type == XML_ELEMENT_NODE) {
			if (!xmlStrcmp(cur->name, (const xmlChar *)"bounds")){
				printf("Element %s\n", cur->name);
				//as we are not using it yet, we let it on comment
				//b = parseBounds(cur);
				parseBounds(cur);
				printf("\n");
			}

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"node"))){
				printf("Element %s\n", cur->name);
		     	parseNode (doc, cur);
				printf("\n");
			}

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"way"))){
				printf("Element %s\n", cur->name);
				parseWay (doc, cur);
				printf("\n");
			}
		}
		cur = cur->next;
	}
}

/*Fonction that parses the file*/
static void parseDoc(char* filename){
	xmlDocPtr doc;
	xmlNodePtr root_element;

   doc = xmlParseFile(filename);
    	
	if (doc == NULL) {
        	fprintf(stderr, "Failed to parse %s\n", filename);
		return;
    	}
	
	/*Get the root element node */
   root_element = xmlDocGetRootElement(doc);

	if (root_element == NULL){
		fprintf(stderr, "empty document\n");
		xmlFreeDoc(doc);
		return;
	}

	parseElements(doc, root_element);
	xmlFreeDoc(doc);
	return;
}

int main(int argc, char **argv) {
	char *filename;
	if(argc != 2){
		printf("SYNTAX ERROR: you have to give your xml document to parse\nUsage: %s filename\n", argv[0]);	
		exit(0);
	}
	
	else{
		filename = argv[1];
		parseDoc (filename);	
		/* Free the global variables that may have been allocated by the parser */
    	xmlCleanupParser();
		exit(1);
	}
	
}

