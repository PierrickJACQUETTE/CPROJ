#include "parseur.h"

Way* parseWay (xmlDocPtr doc, xmlNodePtr cur){
	Way* w;
	unsigned long id;
	char *visible;
	ListNode* ln=initListNode(0);
	Tag* tag=NULL;

	
	xmlAttr *node_attr = cur->properties;
	xmlNodePtr tmpcur=NULL;

	//we browse the element's properties list and we only print the attributs we need to
	while(node_attr != NULL){
		if( xmlStrcmp(node_attr->name,(const xmlChar *)"id")==0 ){
			id = strtoul((const char *)((node_attr->children)->content),NULL,0);
			printf("%s = %s\n", node_attr->name, (node_attr->children)->content);
		}
		else if( xmlStrcmp(node_attr->name,(const xmlChar *)"visible")==0  ){
			visible = (char *)((node_attr->children)->content);
			printf("%s = %s\n", node_attr->name, (node_attr->children)->content);
		}
		/*if( xmlStrcmp(node_attr->name,(const xmlChar *)"id")==0
		|| xmlStrcmp(node_attr->name,(const xmlChar *)"visible")==0 )
		{
			printf("%s = %s\n", node_attr->name, (node_attr->children)->content);
		}*/
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
				ln=addRefListNode( strtoul((const char *)((node_attr->children)->content),NULL,0), ln);
				printf("< %s : ref = %s >\n", tmpcur->name, xmlGetProp(tmpcur, (const xmlChar *)"ref"));
			}
		}
		tmpcur = tmpcur->next;
	}
	w= initWay(id,visible, ln,tag);
	return w;
}

Node* parseNode (xmlDocPtr doc, xmlNodePtr cur, Bounds *bounds) {
	Node* node;
	unsigned long id;
	float lat, lon;
	char *visible;

	xmlAttr *node_attr = cur->properties;

	//we browse the element's properties list and we only print the attributs we need to
	while(node_attr != NULL)
	{
		if( xmlStrcmp(node_attr->name,(const xmlChar *)"id")==0 ){
			id = strtoul((const char *)((node_attr->children)->content),NULL,0);
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

	node = initNode(id,lat,lon,visible, bounds);

	return node;
}

Bounds* parseBounds (xmlNodePtr cur) {
	Bounds *b;
	float minlat, minlon, maxlat, maxlon;

	minlat = strtof((const char *)(xmlGetProp(cur, (const xmlChar *)"minlat")),NULL);
	minlon = strtof((const char *)(xmlGetProp(cur, (const xmlChar *)"minlon")),NULL);
	maxlat = strtof((const char *)(xmlGetProp(cur, (const xmlChar *)"maxlat")),NULL);
	maxlon = strtof((const char *)(xmlGetProp(cur, (const xmlChar *)"maxlon")),NULL);
	b = initBounds(minlat,maxlat,minlon,maxlon);
	return b;
}

/*Fonction that parses the elements needed*/
Map* parseElements(xmlDocPtr doc, xmlNodePtr cur){
	Node *node;
	Map * map = malloc(sizeof(Map));
	Avl *a = NULL;
	int flag = 1;

	cur = cur->xmlChildrenNode;

	while (cur != NULL) {
		if (cur->type == XML_ELEMENT_NODE) {
			if (!xmlStrcmp(cur->name, (const xmlChar *)"bounds")){
				map->bounds = parseBounds(cur);
			}

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"node"))){
				node = parseNode (doc, cur, map->bounds);
				if(flag==1){
					init(&a,node);
					flag=0;
				}
				insert(&a,node);
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
	map->bounds=convertBounds(map->bounds);
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
