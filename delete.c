#include "delete.h"

void deleteCoordinate(Coordinate *c){
	free(c);
}

void deleteBounds(Bounds *b){
	if(b != NULL){
		deleteCoordinate(b->min);
		deleteCoordinate(b->max);
	}
	free(b);
}

void deleteColor(Color *c){
	free(c);
}

void deleteTag(Tag *t){
	if(t != NULL){
		deleteColor(t->c);
	}
	free(t);
}

void deleteTabTag(Tag **t){
	int i;
	for(i=0;i<37;i++){
		deleteTag(t[i]);
	}
	free(t);
}

void deleteRefListNode(refListNode *r){
	while(r != NULL){
		refListNode *tmp = r->next;
		free(r);
		r = tmp;
	}
}

void deleteListNode(ListNode *l){
	if(l != NULL){
		deleteRefListNode(l->firstRef);
	}
	free(l);
}

void deleteRefListWay(refListWay *r){
	while(r!=NULL){
		refListWay *tmp = r->next;
		free(r);
		r = tmp;
	}
	free(r);
}

void deleteListWay(ListWay *l){
	if(l != NULL){
		deleteRefListWay(l->firstRef);
	}
	free(l);
}
void deleteRelation(Relation *r){
	if(r != NULL){
		deleteListWay(r->listW);
		deleteListNode(r->listN);
		deleteTag(r->tag);
	}
	free(r);
}

void deleteRefListRel(refListRel *r){
	while(r!=NULL){
		refListRel *tmp = r->next;
		deleteRelation(r->relation);
		r = tmp;
		free(tmp);
	}
	free(r);
}

void deleteListRelation(ListRelation *l){
	if(l != NULL){
		deleteRefListRel(l->firstRef);
	}
	free(l);
}

void deleteNode(Node *n){
	if(n != NULL){
		deleteCoordinate(n->c);
		free(n->name);
	}
	free(n);
}

void deleteWay(Way *w){
	if(w != NULL){
		deleteListNode(w->listNd);
		deleteTag(w->tag);
		free(w->name);
	}
	free(w);
}

/*void deleteRelation(Relation *r){
	if(r != NULL){
		deleteListWay(r->listW);
		deleteListNode(r->listN);
		deleteTag(r->tag);
	}
	free(r);
}*/

void deleteAvl(Avl** avl,int isNode){
	if(*avl == NULL){
		return ;
	}
	deleteAvl(&((*avl)->left),isNode);
	deleteAvl(&((*avl)->right),isNode);
	if(isNode == 1){
		deleteNode((*avl)->node);
	}
	if(isNode == 0){
		deleteWay((*avl)->way);
	}
	free(*avl);
}

void deleteMap(Map *map){
	if(map!=NULL){
		deleteBounds(map->bounds);
		if(map->avl !=NULL){
			deleteAvl(&(map->avl),1);
		}
		if(map->avlWay !=NULL){
			deleteAvl(&(map->avlWay),0);
		}
		deleteListWay(map->wayOther);
		deleteListWay(map->wayGreen);
		deleteListWay(map->wayWater);
		deleteListWay(map->wayBuilding);
		deleteListWay(map->wayHighway);
		deleteListWay(map->wayCadastre);
		deleteListRelation(map->listRelation);
		deleteTabTag(map->referenceTag);
	}
}
