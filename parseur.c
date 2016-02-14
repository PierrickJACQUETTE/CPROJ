#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

static void print_element_names(xmlNode * a_node){
    	xmlNode *cur_node = NULL;
	
    	for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        	if (cur_node->type == XML_ELEMENT_NODE) {
			if(strcmp(cur_node->name,"bounds")==0){
            			printf("Element %s\n", cur_node->name);
			
				xmlAttr *node_attr = cur_node->properties;
				while(node_attr != NULL) {
					printf("%s = %s\n", node_attr->name, (node_attr->children)->content);
					node_attr = node_attr->next;
				}	
			}
        	}

        	print_element_names(cur_node->children);
    	}
}


static void parseDoc(char* filename){
	xmlDocPtr doc;
	xmlNode *root_element = NULL;

    	doc = xmlReadFile(filename, NULL, 0);
    	
	if (doc == NULL) {
        	fprintf(stderr, "Failed to parse %s\n", filename);
		return;
    	}
	
	/*Get the root element node */
   	root_element = xmlDocGetRootElement(doc);

	print_element_names(root_element);

	xmlFreeDoc(doc);
}

int main(int argc, char **argv) {
	char *filename;

	if(argc != 2){
		printf("SYNTAX ERROR: you have to give your xml document to parse\nUsage: %s filename\n", argv[0]);	
		exit(1);
	}
	
	else{
		filename = argv[1];

		parseDoc (filename);
	
		/* Free the global variables that may have been allocated by the parser */
    		xmlCleanupParser();

		exit(0);
	}
	
}

