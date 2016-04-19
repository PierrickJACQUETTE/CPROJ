int main(int argc, char **argv) {
	char *filename;
	if(argc < 2){
		fprintf(stderr,"SYNTAX ERROR: you have to give your xml document to parse\nUsage: %s filename\n", argv[0]);
		exit(0);
	}

	else{
		filename = argv[1];
		Map* map = malloc(sizeof(Map));
		if(map == NULL){
			fprintf(stderr,"Le pointer vers la map est NULL dans fonction main \n");
		}
		map = parseDoc(filename);
		if(argc == 3){
			if(strcmp(argv[2],"line")==0){
				printMap(map,"line",NULL);
			}
			else if(strcmp(argv[2],"point")==0){
				printMap(map,"point",NULL);
			}
			else{
				char* signal = argv[2];
				if(strcmp(signal,"-s")!=0){
					fprintf(stderr,"SIGNAL ERROR: Wrong signal \nUsage: %s filename -s\n", argv[0]);
					exit(0);
				}
				else{
					printMap(map,"line",signal);
				}
			}
		}
		else{
			printMap(map,"line",NULL);
		}
		deleteMap(map);
		xmlCleanupParser();
		exit(1);
	}
}
