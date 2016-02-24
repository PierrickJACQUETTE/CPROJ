#include "parseur.h"

void 
parseWay (xmlDocPtr doc, xmlNodePtr cur) {
	xmlChar *nd, *tag;
	xmlAttr *node_attr = cur->properties; 

	//we browse the element's properties list and we only print the attributs we need to
	while(node_attr != NULL){ 
		if( xmlStrcmp(node_attr->name,(const xmlChar *)"id")==0 
		|| xmlStrcmp(node_attr->name,(const xmlChar *)"visible")==0 )
		{
			printf("%s = %s\n", node_attr->name, (node_attr->children)->content);			
		}
		node_attr = node_attr->next;
	}
}

void 
parseNode (xmlDocPtr doc, xmlNodePtr cur) {
	xmlChar *tag;
	xmlNodePtr child_node;
	xmlAttr *node_attr = cur->properties; 

	//we browse the element's properties list and we only print the attributs we need to
	while(node_attr != NULL){ 
		if( xmlStrcmp(node_attr->name,(const xmlChar *)"id")==0 
		|| xmlStrcmp(node_attr->name,(const xmlChar *)"visible")==0 
		|| xmlStrcmp(node_attr->name,(const xmlChar *)"lat")==0 
		|| xmlStrcmp(node_attr->name,(const xmlChar *)"lon")==0 )
		{
			printf("%s = %s\n", node_attr->name, (node_attr->children)->content);			
		}
		node_attr = node_attr->next;
	}
	
	/*cur = cur->next;
	if (cur->type == XML_ELEMENT_NODE && (xmlStrcmp(cur->name,(const xmlChar *)"tag")==0) ) {
            printf("name: %s\n", cur->name);
        }*/

	while((cur->children)!=NULL){
	if(xmlStrcmp((cur->xmlChildrenNode)->name,(const xmlChar *)"text")==0){
		printf("has child\n");
	}
	cur = cur->children;
	}


	/*if ((!xmlStrcmp(cur->name, (const xmlChar *)"tag"))) {
  		tag = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
       		printf("tag: %s\n", tag);		
        	xmlFree(tag);
       	}*/
}
		
/*Fonction that prints the elements needed and the attributs with their content*/
static void 
print_elements(xmlDocPtr doc, xmlNodePtr cur){
	//xmlChar *bounds;
	cur = cur->xmlChildrenNode; 

	while (cur != NULL) {

		if ((!xmlStrcmp(cur->name, (const xmlChar *)"bounds"))){
			printf("Element %s\n", cur->name);
			xmlAttr *node_attr = cur->properties;
			while(node_attr != NULL) {
				printf("%s = %s\n", node_attr->name, (node_attr->children)->content);
				node_attr = node_attr->next;

			}
			/*bounds = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1);
       			printf("bounds: %s\n", bounds);
        		xmlFree(bounds);*/
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

		cur = cur->next;
	}
}

/*Fonction that parses the file*/
static void 
parseDoc(char* filename){
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

