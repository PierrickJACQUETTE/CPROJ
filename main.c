#include "parseur.h"
#include "graphic.h"
#include "delete.h"

int main(int argc, char **argv) {
	char *filename;
	if(argc < 2){
		fprintf(stderr,"SYNTAX ERROR: you have to give your xml document to parse\nUsage: %s filename\n", argv[0]);
		exit(0);
	}

	else{
		filename = argv[1];
		Map* map= malloc(sizeof(Map));
		if(map ==NULL){
			fprintf(stderr,"Le pointer vers la map est NULL dans fonction main \n");
		}
		map =parseDoc(filename);
		//printWay(&(map->avlWay),0);
		if(argc==3){
			printMap(map,argv[2]);
		}
		else{
			printMap(map,"line");
		}
		deleteMap(map);
		xmlCleanupParser();
		exit(1);
	}

}
