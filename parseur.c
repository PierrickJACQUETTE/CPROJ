#include "parseur.h"

/*Fonction that prints the elements needed and the attributs with their content*/
static void print_elements(xmlNode * a_node){
	//Saves the current node's position
    	xmlNode *cur_node = NULL;
	
	//Loop that navigates the tree 
    	for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        	if (cur_node->type == XML_ELEMENT_NODE) {
			//if we find a "bounds" element, we print the element's name with it's attributs
			if(strcmp(cur_node->name,"bounds")==0){
            			printf("Element %s\n", cur_node->name);
			
				xmlAttr *node_attr = cur_node->properties;
				while(node_attr != NULL) {
					printf("%s = %s\n", node_attr->name, (node_attr->children)->content);
					node_attr = node_attr->next;
				}	
			}
			//if we find a "node" element, we print the element's name with it's id and visible attributs
			if(strcmp(cur_node->name,"node")==0){
            			printf("%s : ", cur_node->name);
				xmlAttr *node_attr = cur_node->properties;
				
				//we browse the element's properties list and we only print the attributs we need to
				while(node_attr != NULL && 
				( strcmp(node_attr->name,"id")==0 || strcmp(node_attr->name,"visible")==0 || strcmp(node_attr->name,"lat")==0 					|| strcmp(node_attr->name,"lon")==0 ))
				{
					printf("%s = %s ", node_attr->name, (node_attr->children)->content);
					node_attr = node_attr->next;
				}
				printf("\n");	
			}
        	}

        	print_elements(cur_node->children);
    	}
}

/*Fonction that parses the file*/
static void parseDoc(char* filename){
	xmlDocPtr doc;
	xmlNode *root_element;

    	doc = xmlReadFile(filename, NULL, 0);
    	
	if (doc == NULL) {
        	fprintf(stderr, "Failed to parse %s\n", filename);
		return;
    	}
	
	/*Get the root element node */
   	root_element = xmlDocGetRootElement(doc);

	print_elements(root_element);

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

