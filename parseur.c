#include "parseur.h"

Way* parseWay (xmlDocPtr doc, xmlNodePtr cur, Tag** refTag){
	Way* w = NULL;
	unsigned long id = -1;
	char *visible = "T";
	ListNode* ln = initListNode(0);
	Tag* tag = NULL;
	Tag* t = NULL;
	int size = 0;
	char* name = NULL;

	xmlAttr *node_attr = cur->properties;
	xmlNodePtr tmpcur = NULL;

	while(node_attr != NULL){
		if( xmlStrcmp(node_attr->name,(const xmlChar *)"id")==0 ){
			id = strtoul((const char *)((node_attr->children)->content),NULL,0);
		}
		else if( xmlStrcmp(node_attr->name,(const xmlChar *)"visible")==0  ){
			visible = (char *)((node_attr->children)->content);
		}
		node_attr = node_attr->next;
	}
	tmpcur = cur->xmlChildrenNode;

	while(tmpcur != NULL){
		if (tmpcur->type == XML_ELEMENT_NODE) {
			if( xmlStrcmp(tmpcur->name,(const xmlChar *)"tag")==0){
				t=goodTag((char *)xmlGetProp(tmpcur, (const xmlChar *)"k"),(char *) xmlGetProp(tmpcur, (const xmlChar *)"v"), refTag);
				if( xmlStrcmp( (const xmlChar *) xmlGetProp( tmpcur, (const xmlChar *)"k" ), (const xmlChar *)"name" ) ==0){
					name = (char *) xmlGetProp(tmpcur, (const xmlChar *)"v");
				}
				if((t != NULL && tag == NULL) ||  ( t != NULL && tag != NULL && (t->priority>tag->priority))){
					tag = t;
				}
			}
			if( xmlStrcmp(tmpcur->name,(const xmlChar *)"nd")==0 ){
				ln=addRefListNode(strtoul((const char *)(xmlGetProp(tmpcur, (const xmlChar *)"ref")),NULL,0), ln);
				size++;
			}
		}
		tmpcur = tmpcur->next;
	}
	if(tag != NULL){
		w = initWay(id,visible,ln,tag,size,name);
		return w;
	}
	else{
		return NULL;
	}
}
Relation* parseRelation(xmlDocPtr doc, xmlNodePtr cur){
	Relation* r = NULL;
	unsigned long id = -1;
	char *visible = "T";
	ListWay* lw = initListWay(0);
	ListNode* ln = initListNode(0);
	Tag* tag = NULL;
	Tag* t = NULL;

	xmlAttr *node_attr = cur->properties;
	xmlNodePtr tmpcur = NULL;

	while(node_attr != NULL){
		if( xmlStrcmp(node_attr->name,(const xmlChar *)"id") ==0 ){
			id = strtoul((const char *)((node_attr->children)->content),NULL,0);
		}
		else if( xmlStrcmp(node_attr->name,(const xmlChar *)"visible") ==0  ){
			visible = (char *)((node_attr->children)->content);
		}
		node_attr = node_attr->next;
	}
	tmpcur = cur->xmlChildrenNode;

	while(tmpcur != NULL){
		if (tmpcur->type == XML_ELEMENT_NODE) {
			if( xmlStrcmp(tmpcur->name,(const xmlChar *)"tag") ==0 ){
				t = goodTagRelation((char *)xmlGetProp(tmpcur, (const xmlChar *)"k"),(char *) xmlGetProp(tmpcur, (const xmlChar *)"v"));
				if(t != NULL){
					tag = t;
				}
			}
			if( xmlStrcmp(tmpcur->name,(const xmlChar *)"member") ==0 ){
				if((strcmp((char *)xmlGetProp(tmpcur, (const xmlChar *)"type"),"way") ==0)){
					lw = addRefListWay(strtoul((const char *)(xmlGetProp(tmpcur, (const xmlChar *)"ref")),NULL,0),(char *)xmlGetProp(tmpcur, (const xmlChar *)"role"), lw);
				}
				if((strcmp((char *)xmlGetProp(tmpcur, (const xmlChar *)"type"),"node") ==0)){
					ln = addRefListNode(strtoul((const char *)(xmlGetProp(tmpcur, (const xmlChar *)"ref")),NULL,0), ln);
				}
			}
		}
		tmpcur = tmpcur->next;
	}
	r = initRelation(id,visible, tag,lw, ln);
	return r;
}

Node* parseNode (xmlDocPtr doc, xmlNodePtr cur, Bounds *bounds) {
	Node* node = NULL;
	unsigned long id = -1;
	float lat = 100;
	float lon = 100;
	char *visible = "T";
	char* name = NULL;

	xmlAttr *node_attr = cur->properties;
	xmlNodePtr tmpcur = NULL;

	while(node_attr != NULL)
	{
		if( xmlStrcmp(node_attr->name,(const xmlChar *)"id")==0 ){
			id = strtoul((const char *)((node_attr->children)->content),NULL,0);
		}
		else if( xmlStrcmp(node_attr->name,(const xmlChar *)"visible") == 0  ){
			visible = (char *)((node_attr->children)->content);
		}
		else if( xmlStrcmp(node_attr->name,(const xmlChar *)"lat") ==0 ){
			lat = strtof((const char *)((node_attr->children)->content),NULL);
		}
		else if( xmlStrcmp(node_attr->name,(const xmlChar *)"lon") ==0 ){
			lon = strtof((const char *)((node_attr->children)->content),NULL);
		}
		node_attr = node_attr->next;
	}

	tmpcur = cur->xmlChildrenNode;

	while(tmpcur != NULL){
		if( xmlStrcmp(tmpcur->name,(const xmlChar *)"tag")==0){
			if( xmlStrcmp( (const xmlChar *) xmlGetProp( tmpcur, (const xmlChar *)"k" ), (const xmlChar *)"name" ) ==0){
				name = (char *) xmlGetProp(tmpcur, (const xmlChar *)"v");
			}
		}
		tmpcur = tmpcur->next;
	}
	node = initNode(id,lat,lon,visible,bounds,name);

	return node;
}

Bounds* parseBounds (xmlNodePtr cur) {
	Bounds *b;
	float minlat = 100;
	float minlon = 100;
	float maxlat = 100;
	float maxlon = 100;

	minlat = strtof((const char *)(xmlGetProp(cur, (const xmlChar *)"minlat")),NULL);
	minlon = strtof((const char *)(xmlGetProp(cur, (const xmlChar *)"minlon")),NULL);
	maxlat = strtof((const char *)(xmlGetProp(cur, (const xmlChar *)"maxlat")),NULL);
	maxlon = strtof((const char *)(xmlGetProp(cur, (const xmlChar *)"maxlon")),NULL);
	b = initBounds(minlat,maxlat,minlon,maxlon);
	return b;
}

Map* parseElements(xmlDocPtr doc, xmlNodePtr cur){
	Map* map = initMap();
	Node *node;
	Way* way;
	Relation *r;
	Avl* aNode = NULL;
	Avl* avlWay = NULL;
	ListNode* ln = NULL;
	ListWay* wO = NULL;
	ListWay* wW = NULL;
	ListWay* wG = NULL;
	ListWay* wH = NULL;
	ListWay* wB = NULL;
	ListWay* wC = NULL;
	ListRelation* lr= NULL;
	int flagN = 1;
	int flagW = 1;

	cur = cur->xmlChildrenNode;

	while (cur != NULL) {
		if (cur->type == XML_ELEMENT_NODE) {
			if (!xmlStrcmp(cur->name, (const xmlChar *)"bounds")){
				map->bounds = parseBounds(cur);
			}

			if ((!xmlStrcmp(cur->name, (const xmlChar *)"node"))){
				node = parseNode (doc, cur, map->bounds);
				if(node->name!=NULL){
					ln = addRefListNode(node->id,ln);
				}
				if(flagN == 1){
					init(&aNode,node,NULL);
					flagN = 0;
				}
				else{
					insert(&aNode,node,NULL);
				}
			}
			if ((!xmlStrcmp(cur->name, (const xmlChar *)"way"))){
				way = parseWay (doc, cur, map->referenceTag);
				if(way != NULL){
					if((way->tag->type) == 0){
						wO = addRefListWay(way->id," ", wO);
					}
					else if(way->tag->type == 1){
						wW = addRefListWay(way->id," ", wW);
					}
					else if(way->tag->type == 2){
						wG = addRefListWay(way->id," ", wG);
					}
					else if(way->tag->type == 3){
						wH = addRefListWay(way->id," ", wH);
					}
					else if(way->tag->type == 4){
						wB = addRefListWay(way->id," ", wB);
					}
					else if(way->tag->type == 5){
						wC = addRefListWay(way->id," ", wC);
					}
					if(flagW == 1){
						init(&avlWay,NULL, way);
						flagW = 0;
					}
					else{
						insert(&avlWay,NULL,way);
					}
				}
			}
			if ((!xmlStrcmp(cur->name, (const xmlChar *)"relation"))){
				r = parseRelation(doc, cur);
				if(r != NULL){
					lr = addRefListRelation(r,lr);
				}
			}
		}
		cur = cur->next;
	}

	map->avl = aNode;
	map->avlWay = avlWay;
	map->nodeOther = ln;
	map->wayWater = wW;
	map->wayOther = wO;
	map->wayGreen = wG;
	map->wayBuilding = wB;
	map->wayHighway = wH;
	map->wayCadastre = wC;
	map->listRelation = lr;

	Node* n0 = initNode(0, map->bounds->min->y, map->bounds->min->x, "true", map->bounds, NULL);
	Node* n1 = initNode(1, map->bounds->max->y, map->bounds->min->x, "true", map->bounds, NULL);
	Node* n2 = initNode(2, map->bounds->max->y, map->bounds->max->x, "true", map->bounds, NULL);
	Node* n3 = initNode(3, map->bounds->min->y, map->bounds->max->x, "true", map->bounds, NULL);
	insert(&aNode,n0,NULL);
	insert(&aNode,n1,NULL);
	insert(&aNode,n2,NULL);
	insert(&aNode,n3,NULL);
	map->bounds = convertBounds(map->bounds);

	return map;
}

Map* parseDoc(char* filename){

	xmlDocPtr doc;
	xmlNodePtr root_element;
	doc = xmlParseFile(filename);

	if (doc == NULL) {
		fprintf(stderr, "Failed to parse %s\n", filename);
		return NULL;
	}

	root_element = xmlDocGetRootElement(doc);

	if (root_element == NULL){
		fprintf(stderr, "empty document\n");
		xmlFreeDoc(doc);
		return NULL;
	}

	Map* map = malloc(sizeof(Map));
	map = parseElements(doc, root_element);
	xmlFreeDoc(doc);
	return map;
}
