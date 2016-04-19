#include "graphic.h"

void modifThinck(float ref){
	if(ref < 2 && ref > 1){
		modifThink = -1;
	}
	else if(ref < 3 && ref >=2){
		modifThink = -5;
	}
	else if(ref < 4 && ref >=3){
		modifThink = -6;
	}
}

void sizeWindows(Map* map){
	float diffX = (map->bounds->max->x) - (map->bounds->min->x);
	float diffY = (map->bounds->max->y) - (map->bounds->min->y);
	if(diffX > diffY){
		modifThinck(fabs(diffX));
	}
	else {
		modifThinck(fabs(diffY));
	}
	float QX = windows_Width / diffX;
	float QY = windows_Height / diffY;

	if(QX > QY){
		windows_Width = diffX * QY;
		windows_Height = diffY * QY;
	}
	else{
		windows_Width = diffX * QX;
		windows_Height = diffY * QX;
	}
	if(windows_Width < WINDOWS_WIDTHMIN){
		windows_Width = WINDOWS_WIDTHMIN;
	}
	if(windows_Width > WINDOWS_WIDTHMAX){
		windows_Width = WINDOWS_WIDTHMAX;
	}
	if(windows_Height < WINDOWS_HEIGHTMIN){
		windows_Height = WINDOWS_HEIGHTMIN;
	}
	else if(windows_Height > WINDOWS_HEIGHTMAX){
		windows_Height = WINDOWS_HEIGHTMAX;
	}
}

int init_SDL() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr,"SDL could not initialize! SDL Error: %s\n",SDL_GetError());
		return 0;
	}
	window = SDL_CreateWindow("CPROJ",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,windows_Width,windows_Height,SDL_WINDOW_SHOWN);
	if(window == NULL) {
		fprintf(stderr,"Window could not be created! SDL Error: %s\n",SDL_GetError());
		return 0;
	}
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
	if(renderer == NULL) {
		printf("Renderer could not be created! SDL Error: %s\n",SDL_GetError());
		return 0;
	}
	return colorBackgroundDefault();
}

void close_SDL() {
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

void printMap(Map* map, char* typeOfDessin, char* signal){
	if(map == NULL){
		fprintf(stderr,"La map vaut null : %s\n","fonction printMap");
		exit(EXIT_FAILURE);
	}
	if(map->bounds == NULL){
		fprintf(stderr,"Les bounds de la map vaut null : %s\n","fonction printMap");
		exit(EXIT_FAILURE);
	}
	if(map->bounds->min == NULL){
		fprintf(stderr,"Le min de la bound de la map vaut null : %s\n","fonction printMap");
		exit(EXIT_FAILURE);
	}
	if(map->bounds->max == NULL){
		fprintf(stderr,"Le max de la bound de la map vaut null : %s\n","fonction printMap");
		exit(EXIT_FAILURE);
	}
	windows_Width = 800;
	windows_Height = 600;
	modifThink = 0;
	sizeWindows(map);
	quit = 1;
	if(init_SDL() ==0) {
		exit(EXIT_FAILURE);
	}
	drawMap(map, typeOfDessin);
	if(signal==NULL){
		evenement();
	}
	close_SDL();
	exit(EXIT_SUCCESS);
}
