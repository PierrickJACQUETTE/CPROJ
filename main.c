#include "parseur.h"
#include "graphic.h"

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


int main(int argc, char **argv) {
	char *filename;
	if(argc != 2){
		printf("SYNTAX ERROR: you have to give your xml document to parse\nUsage: %s filename\n", argv[0]);
		exit(0);
	}

	else{
		filename = argv[1];
		Map* map= malloc(sizeof(Map));
		map =parseDoc(filename);
		//print(&(map->avl),0);		
		printMap(map);
		xmlCleanupParser();
		exit(1);
	}

}
