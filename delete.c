#include "delete.h"

void deleteCoordinate(Coordinate *c){
	free(c);
}

void deleteBounds(Bounds *b){
	deleteCoordinate(b->min);
	deleteCoordinate(b->max);
	free(b);
}

void deleteColor(Color *c){
	free(c);
}

void deleteTag(Tag *t){
	free(t->tagKey);
	free(t->tagValue);
	deleteColor(t->c);
	free(t);
}

void deleteTagDraw(TagDraw *t){
	deleteTag(t->tag);
	deleteColor(t->contour);
	deleteColor(t->background);
	free(t);
}

void deleteTabTag(Tag **t){
	int i;
	for(i=0;i<19;i++){
		deleteTag(t[i]);
	}
}

void deleteRefListNode(refListNode *r){
	while(r!=NULL){
		deleteRefListNode(r->next);
	}
	free(r);
}

void deleteListNode(ListNode *l){
	deleteRefListNode(l->firstRef);
	deleteRefListNode(l->lastRef);
	free(l);
}

void deleteRefListWay(refListWay *r){
	while(r!=NULL){
		deleteRefListWay(r->next);
	}
	free(r);
}

void deleteListWay(ListWay *l){
	deleteRefListWay(l->firstRef);
	deleteRefListWay(l->lastRef);
	free(l);
}

void deleteRefListRel(refListRel *r){
	while(r!=NULL){
		deleteRefListRel(r->next);
	}
	free(r);
}

void deleteListRelation(ListRelation *l){
	deleteRefListRel(l->firstRef);
	deleteRefListRel(l->lastRef);
	free(l);
}

void deleteNode(Node *n){
	deleteCoordinate(n->c);
	free(n->visible);
	free(n);
}

void deleteWay(Way *w){
	deleteListNode(w->listNd);
	free(w->visible);
	deleteTag(w->tag);
	free(w);
}

void deleteRelation(Relation *r){
	deleteListWay(r->listW);
	free(r->visible);
	//deleteTag(r->tag);
	free(r);
}

void deleteAvl(Avl** avl){
	if((*avl)->left!=NULL){
		deleteAvl(&((*avl)->left));
	}
	if((*avl)->right!=NULL){
		deleteAvl(&((*avl)->right));
	}
	if((*avl)->node !=NULL){
		deleteNode((*avl)->node);
	}
	if((*avl)->way != NULL){
		deleteWay((*avl)->way);
	}
	free(avl);
}

void deleteMap(Map *map){
	if(map!=NULL){
		deleteBounds(map->bounds);
		if(map->avl !=NULL){
			deleteAvl(&(map->avl));
		}
		if(map->avlWay !=NULL){
			deleteAvl(&(map->avlWay));
		}
		deleteListWay(map->listWay);
		//		deleteListRelation(map->listRelation);
		//		deleteTabTag(map->referenceTag);
	}
}
