#include "parseur.h"

void 
parseWay (xmlDocPtr doc, xmlNodePtr cur) {
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
	while(tmpcur != NULL){// tant qu'il y a des enfants dans la way
		if (tmpcur->type == XML_ELEMENT_NODE) {
      	printf("<%s : k=, v=>\n", tmpcur->name);
      }
		tmpcur = tmpcur->next;
	}
	
	/*cur = cur->next;
	if (cur->type == XML_ELEMENT_NODE && (xmlStrcmp(cur->name,(const xmlChar *)"tag")==0) ) {
            printf("name: %s\n", cur->name);
        }*/
	/*if ((!xmlStrcmp(cur->name, (const xmlChar *)"tag"))) {
  		tag = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
       		printf("tag: %s\n", tag);		
        	xmlFree(tag);
       	}*/
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
		
/*Fonction that prints the elements needed and the attributs with their content*/
static void print_elements(xmlDocPtr doc, xmlNodePtr cur){
	cur = cur->xmlChildrenNode; 

	while (cur != NULL) {
		if (cur->type == XML_ELEMENT_NODE) {
			if (!xmlStrcmp(cur->name, (const xmlChar *)"bounds")){
				printf("Element %s\n", cur->name);
				xmlAttr *node_attr = cur->properties;
				while(node_attr != NULL) {
					printf("%s = %s\n", node_attr->name, (node_attr->children)->content);
					node_attr = node_attr->next;
				}
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

	print_elements(doc, root_element);
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

