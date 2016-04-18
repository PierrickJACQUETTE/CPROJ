#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>

int windows_Height;
int windows_Width;

/*
gcc -Wall dessin1.c -lSDL2_gfx `sdl2-config --cflags --libs` -lm

*/

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
enum status {QUIT, CONTINUE};
enum status status;


typedef struct{
	float x;
	float y;
}Coordinate;


void dessin();

int colorBackground();

//new 1
void sizeWindows(){
	int minX = 0; // Bounds
	int maxX = 100;
	int minY = 0;
	int maxY = 100;
	int diffX = maxX - minX;
	int diffY = maxY - minY;
	int QX = windows_Width/diffX;
	int QY = windows_Height/diffY;
	if(QX > QY){
		windows_Width = diffX*QY;
		windows_Height = diffY*QY;
	}
	else{
		windows_Width = diffX*QX;
		windows_Height = diffY*QX;
	}

}

int init_SDL() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n",SDL_GetError());
        return 0;
    }
    window = SDL_CreateWindow("CPROJ",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,windows_Width,windows_Height,SDL_WINDOW_SHOWN);
    if(window == NULL) {
        printf("Window could not be created! SDL Error: %s\n",SDL_GetError());
        return 0;
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n",SDL_GetError());
        return 0;
    }
	//new 1
    return colorBackground();
}

//new 1
void close_SDL() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

//new 1
int colorBackground(){
	if(SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF) < 0) {
        printf("Renderer color could not be set! SDL Error: %s\n",SDL_GetError());
        return 0;
    }
	return 1;
}


//new 3
int clavier(SDL_Event e,int i){
	switch(e.key.keysym.sym){
		case SDLK_q :
    		printf("fermeture de la fenetre.\n");
    		status = QUIT;
    		break;
		default:
           	break;
	}
	return i;
}

//new 3
void evenement(){
	float i = 0;
  do {
    SDL_Event e;
    if (SDL_PollEvent(&e)) { // detecte si il y a un even
      switch (e.type) {
		case SDL_KEYDOWN:
			i =	clavier(e,i);
			break;
        case SDL_QUIT :
       		printf("fermeture de la fenetre.\n");
        	status = QUIT;
        	break;
		default:
	       break;
      }
    }
  }
  while (status != QUIT);
}

// new 2
float longeurPoint(float ax, float ay, float bx,float by ){
	return sqrt(pow(bx-ax,2)+pow(by-ay,2));
}

// new 2
float normalize(float a, float b,float length){
	return (b-a)/length;
}

// new 2
float angle(float ax, float ay, float bx,float by,float cx,float cy){
	float longeurAB = longeurPoint(ax,ay,bx,by);
	float longeurBC = longeurPoint(bx,by,cx,cy);
	float quotientSin = ((ax-bx)*(cx-bx))-((ay-by)*(cy-by));
//	float sin = asinf(quotientSin/(longeurAB*longeurBC));
	float quotient = ((ax-bx)*(cx-bx))+((ay-by)*(cy-by));
	//quotient = pow(longeurAB,2)+pow(longeurBC,2)-pow((longeurPoint(ax,ay,cx,cy)),2);
	float cos = acosf(quotient/(longeurAB*longeurBC));
	printf("angle : %f\n",quotientSin);
	if(quotientSin>0){
		return cos*180/M_PI;
	}
	else{
		return 0-(cos*180/M_PI);
	}

}

// new 2
Sint16 * extremite(float a, float d, float e, Sint16 tab[4], int signe){
	if(signe ==1){
		tab[0] = a + d;
		tab[1] = a - e;
	}
	else{
		tab[0] = a - d;
		tab[1] = a + e;
	}
	return tab;
}

// new 2
Sint16* midle(float b, float e, int signe, Sint16 tab[4]){
	if(signe==1){
		tab[3]= b - e;
		tab[2]= b + e;
	}
	else{
		tab[3]= b + e;
		tab[2]= b - e;
	}
	return tab;
}

// new 2
void highway(){
	Coordinate* a = malloc(sizeof(Coordinate));
	Coordinate* b = malloc(sizeof(Coordinate));
	Coordinate* c = malloc(sizeof(Coordinate));
	if(a == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","normalize");
		exit(EXIT_FAILURE);
	}
	if(b == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","normalize");
		exit(EXIT_FAILURE);
	}
	if(c == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","normalize");
		exit(EXIT_FAILURE);
	}
	c->x = 50;
	c->y = 300;
	b->x = 100;
	b->y = 500;
	a->x = 400;
	a->y = 200;
	int epaisseur = 24;

	float length = longeurPoint(a->x,a->y,b->x,b->y);
	float fx = normalize(a->y,b->y,length);
	float gx = fx;
	float fy = 0.0-normalize(a->x,b->x,length);
	float gy = fy;
	Sint16 t[4]= {fx,gx,0.0,0.0};
	Sint16 s[4]= {fy,gy,0.0,0.0};
	float coeff = (a->y-b->y)/(a->x-b->x);
	if( coeff> 0){
	extremite(a->x,fx*epaisseur/2,gx*epaisseur/2,t,1);
	extremite(a->y,fy*epaisseur/2,gy*epaisseur/2,s,1);
}
else{
	extremite(a->x,fx*epaisseur/2,gx*epaisseur/2,t,0);
	extremite(a->y,fy*epaisseur/2,gy*epaisseur/2,s,0);
}

	//permet de connaitre le debut on doit etre sur le deuxime point

	//on retiens deux points d'avant
	float lengthAB = longeurPoint(a->x,a->y,b->x,b->y);
	float resABy = normalize(a->y,b->y,lengthAB);
	float resABx = normalize(a->x,b->x,lengthAB);

	float lengthBC = longeurPoint(b->x,b->y,c->x,c->y);
	float resBCx = normalize(b->x,c->x,lengthBC);
	float resBCy = normalize(b->y,c->y,lengthBC);

	float X = (resABx - resBCx)*epaisseur/2;
	float Y = (resABy - resBCy)*epaisseur/2;

	double angleCal = angle(a->x,a->y,b->x,b->y,c->x,c->y);
	printf("angleCal %f \n",angleCal);
	if(angleCal >0){
		midle(b->x,X,0,t);
		midle(b->y,Y,0,s);
	}
	else{
		midle(b->x,X,1,t);
		midle(b->y,Y,1,s);
	}
	filledPolygonRGBA(renderer,t,s,4,255,0,0,255);
	//trace le premier polygon, il faut etre sur le trois points + mise a jour des deux points


	//jai fini donc extremite en retenant les points points precedent
	length = longeurPoint(b->x,b->y,c->x,c->y);
	fx = normalize(b->y,c->y,length);
	gx = fx;
	fy = 0.0-normalize(b->x,c->x,length);
	gy = fy;
	if( coeff> 0){
	extremite(c->x,fx*epaisseur/2,gx*epaisseur/2,t,1);
	extremite(c->y,fy*epaisseur/2,gy*epaisseur/2,s,1);
}
else{
	extremite(c->x,fx*epaisseur/2,gx*epaisseur/2,t,0);
	extremite(c->y,fy*epaisseur/2,gy*epaisseur/2,s,0);
}
	filledPolygonRGBA(renderer,t,s,4,255,0,0,255);


/*	thickLineRGBA(renderer,a->x,a->y+150,b->x,b->y+150,epaisseur,0,0,255,255);
	thickLineRGBA(renderer,b->x,b->y+150,c->x,c->y+150,epaisseur,0,0,255,255);

	filledCircleRGBA(renderer,b->x,b->y+300,epaisseur/2,0,255,0,255);
	thickLineRGBA(renderer,a->x,a->y+300,b->x,b->y+300,epaisseur,0,255,0,255);
	thickLineRGBA(renderer,b->x,b->y+300,c->x,c->y+300,epaisseur,0,255,0,255);
*/
}

int main(int argc,char *argv[]) {
	windows_Width = 540;
	windows_Height  = 540;

	status = CONTINUE;
	sizeWindows();

    if(init_SDL() == 0) {
        exit(EXIT_FAILURE);
    }

	colorBackground();
	SDL_RenderClear(renderer);
	highway();
    SDL_RenderPresent(renderer);

 	evenement();
   close_SDL();
    exit(EXIT_SUCCESS);

}
