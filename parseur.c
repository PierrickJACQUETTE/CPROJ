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

Node* parseNode (xmlDocPtr doc, xmlNodePtr cur) {
	Node* node;
	int id;
	float lat, lon;
	char *visible;

	xmlAttr *node_attr = cur->properties;

	//we browse the element's properties list and we only print the attributs we need to
	while(node_attr != NULL)
	{
		if( xmlStrcmp(node_attr->name,(const xmlChar *)"id")==0 ){
			id = atoi((const char *)((node_attr->children)->content));
		}
		else if( xmlStrcmp(node_attr->name,(const xmlChar *)"visible")==0  ){
			visible = (char *)((node_attr->children)->content);
		}
		else if( xmlStrcmp(node_attr->name,(const xmlChar *)"lat")==0 ){
			lat = strtof((const char *)((node_attr->children)->content),NULL);
		}
		else if( xmlStrcmp(node_attr->name,(const xmlChar *)"lon")==0 ){
			lon = strtof((const char *)((node_attr->children)->content),NULL);
		}
		node_attr = node_attr->next;
	}

	printf("id = %d, lat = %f, lon = %f, visible=%s \n", id,lat,lon,visible);
	node = initNode(id,lat,lon,visible);

	return node;
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
Map* parseElements(xmlDocPtr doc, xmlNodePtr cur){
	//Bounds *b;
	Node *node;
	Map * map = malloc(sizeof(Map));
	Avl *a = NULL;
	int flag = 1;

	cur = cur->xmlChildrenNode;

	while (cur != NULL) {
		if (cur->type == XML_ELEMENT_NODE) {
			if (!xmlStrcmp(cur->name, (const xmlChar *)"bounds")){
				printf("Element %s\n", cur->name);
				//as we are not using it yet, we let it on comment
				//b = parseBounds(cur);
				map->bounds = parseBounds(cur);
				printf("\n");
			}

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"node"))){
				printf("Element %s\n", cur->name);
				node = parseNode (doc, cur);
				if(flag==1){
					init(&a,node->id);
					flag=0;
				}
				insert(&a,node->id);
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
	
	map->avl=a;
	return map;
}

/*Fonction that parses the file*/
Map* parseDoc(char* filename){

	xmlDocPtr doc;
	xmlNodePtr root_element;

	doc = xmlParseFile(filename);

	if (doc == NULL) {
		fprintf(stderr, "Failed to parse %s\n", filename);
		return NULL;
	}

	/*Get the root element node */
	root_element = xmlDocGetRootElement(doc);

	if (root_element == NULL){
		fprintf(stderr, "empty document\n");
		xmlFreeDoc(doc);
		return NULL;
	}

	Map* map = malloc(sizeof(Map));
	map =parseElements(doc, root_element);
	xmlFreeDoc(doc);
	return map;
}
