#include "delete.h"

void delete(Avl** avl){
	free(avl);
	avl =NULL;
}

void deleteMap(Map *map){
	if(map!=NULL){
		//bounds
		free(map->bounds->min);
		free(map->bounds->max);
		free(map->bounds);
		//way

		// avl	
		delete(&(map->avl));
	}
}
