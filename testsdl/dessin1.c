#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>

int windows_Height;
int windows_Width;

/*
gcc -Wall dessin1.c -lSDL2_gfx `sdl2-config --cflags --libs` -lm

Zoom 
	avant fois 2
	arriere jusqua 1

Bouge dans la limite de la moitie de la carte en dehors de la zone de vue
	au clavier 4 directions de 10 en 10
	a la souris, suivant la souris

Fenetre cree en fonction de la taille du dessin

*/

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
enum status {QUIT, CONTINUE};
enum status status;

//new 3
float zoom;
int deplacX;
int deplacY;
const int PASCLAVIER = 10;
int pasSourisX;
int pasSourisY;
int deplacZX;
int deplacZY;
int clicker =0;//1 on deplace

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
void dessine(){
		colorBackground();
		SDL_RenderClear(renderer);
		dessin();
	    SDL_RenderPresent(renderer);
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
void windowEvent(SDL_Event e){
	switch (e.window.event) {
		case SDL_WINDOWEVENT_RESIZED:
			windows_Width = e.window.data1;
             windows_Height = e.window.data2;
			dessine();
			break;
			default:
				break;
	}
}

//new 3
int calculateZoom(int refX, int refY,int decalage,int flag){ //flag vaut 0 qd + 1 qd -
	if(flag == 0){
		zoom *= 2;
		decalage=(decalage*2)+0.5;
	}
	else if(flag == 1){
		zoom /= 2;
		decalage=(decalage-0.5)/2;
	}
	deplacZX = -decalage*2*refX;
	deplacZY = -decalage*2*refY;
	if(flag == 0){
		deplacX*=2;
		deplacY*=2;
	}
	else{
		deplacX/=2;
		deplacY/=2;
	}
	dessine();
	return decalage;
}

//new 3
int clavier(SDL_Event e,int i){
	switch(e.key.keysym.sym){   
		case SDLK_p:
			i = calculateZoom(windows_Width/2,windows_Height/2,i,0);
	        break;
		case SDLK_m:
			if(zoom >= 2){
				i = calculateZoom(windows_Width/2,windows_Height/2,i,1);
			}
			break;
		case SDLK_UP:	
			deplacY += PASCLAVIER;
			dessine();
			break;
		case SDLK_DOWN:	
			deplacY -= PASCLAVIER;
			dessine();
			break;
		case SDLK_RIGHT:	
			deplacX -= PASCLAVIER;
			dessine();
			break;
		case SDLK_LEFT:	
			deplacX += PASCLAVIER;
			dessine();
			break;
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
	int sourisX = 0;
	int sourisY = 0;
	float i = 0;
  do {
    SDL_Event e;
    if (SDL_PollEvent(&e)) { // detecte si il y a un even
      switch (e.type) {
		case SDL_WINDOWEVENT :
			windowEvent(e);
			break;
		case SDL_MOUSEBUTTONDOWN:
			pasSourisX = e.motion.x;
			pasSourisY = e.motion.y;
			clicker = 1;
			break;
		case SDL_MOUSEBUTTONUP:
			clicker = 0;
			break;
		case SDL_MOUSEMOTION :
			sourisX = e.motion.x;
			sourisY = e.motion.y;
			if(clicker == 1){
				deplacX += -(pasSourisX - sourisX);
				deplacY += -(pasSourisY - sourisY);
				pasSourisX = sourisX;
				pasSourisY = sourisY;
				dessine();
			}
			break;
		case SDL_MOUSEWHEEL :
			if(e.motion.x>0){
				i = calculateZoom(sourisX,sourisY,i,0);
			}
			else if (zoom >= 2){
				i = calculateZoom(sourisX,sourisY,i,1);
			}
			break;
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
	float quotient = ((bx-ax)*(cx-bx))-((by-ay)*(cy-by));
	float sin = asinf(quotient/(longeurAB*longeurBC));
	quotient = pow(longeurAB,2)+pow(longeurBC,2)-pow((longeurPoint(ax,ay,cx,cy)),2);
	float cos = acosf(quotient/(2*longeurAB*longeurBC));
	if(sin>0){
		return cos*180/M_PI;
	}
	else{
		return 0-(cos*180/M_PI);
	}
}

// new 2
Sint16* extremite(float a, float d, float e, Sint16 tab[4]){
	tab[0] = a + d;
	tab[1] = a - e;
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
	a->x = 50;
	a->y = 300;
	b->x = 100;
	b->y = 30;
	c->x = 400;
	c->y = 200;
	int epaisseur = 24;

	float length = longeurPoint(a->x,a->y,b->x,b->y);
	float fx = normalize(a->y,b->y,length);
	float gx = fx;
	float fy = 0.0-normalize(a->x,b->x,length);
	float gy = fy;
	Sint16 t[4]= {fx,gx,0.0,0.0};
	Sint16 s[4]= {fy,gy,0.0,0.0};
	extremite(a->x,fx*epaisseur/2,gx*epaisseur/2,t);
	extremite(a->y,fy*epaisseur/2,gy*epaisseur/2,s);

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
	extremite(c->x,fx*epaisseur/2,gx*epaisseur/2,t);
	extremite(c->y,fy*epaisseur/2,gy*epaisseur/2,s);
	filledPolygonRGBA(renderer,t,s,4,255,0,0,255);


/*	thickLineRGBA(renderer,a->x,a->y+150,b->x,b->y+150,epaisseur,0,0,255,255);
	thickLineRGBA(renderer,b->x,b->y+150,c->x,c->y+150,epaisseur,0,0,255,255);

	filledCircleRGBA(renderer,b->x,b->y+300,epaisseur/2,0,255,0,255);
	thickLineRGBA(renderer,a->x,a->y+300,b->x,b->y+300,epaisseur,0,255,0,255);
	thickLineRGBA(renderer,b->x,b->y+300,c->x,c->y+300,epaisseur,0,255,0,255);
*/
}

void dessin(){
	Uint8 a =15;
//	lineRGBA(renderer,(50 * zoom) + deplacX, (50 * zoom) + deplacY,(300 * zoom) + deplacX, (301*zoom) + deplacY,255,0,0,255);
//	printf("X : %f, Y : %f\n",50*zoom+deplacX+deplacZX,50*zoom+deplacY+deplacZY);
//	pixelRGBA(renderer, 50*zoom+deplacX+deplacZX,50*zoom+deplacY+deplacZY,255,0,0,255);
	lineRGBA(renderer,(30 * zoom) + deplacX+ deplacZX, (80 * zoom) + deplacY+ deplacZY,(50 * zoom)+ deplacX+ deplacZX, (80 * zoom) + deplacY+ deplacZY,255,0,0,255);
	lineRGBA(renderer,(50 * zoom) + deplacX+ deplacZX, (80 * zoom) + deplacY+ deplacZY,(50 * zoom)+ deplacX+ deplacZX, (120 * zoom) + deplacY+ deplacZY,255,0,0,255);
	lineRGBA(renderer,(50 * zoom) + deplacX+ deplacZX, (120 * zoom) + deplacY+ deplacZY,(30 * zoom)+ deplacX+ deplacZX, (120 * zoom) + deplacY+ deplacZY,255,0,0,255);
	lineRGBA(renderer,(30 * zoom) + deplacX+ deplacZX, (120 * zoom) + deplacY+ deplacZY,(30 * zoom)+ deplacX+ deplacZX, (80 * zoom) + deplacY+ deplacZY,255,0,0,255);

	lineRGBA(renderer,(260 * zoom) + deplacX+ deplacZX, (260 * zoom) + deplacY+ deplacZY,(280 * zoom)+ deplacX+ deplacZX, (260 * zoom) + deplacY+ deplacZY,255,0,0,255);
	lineRGBA(renderer,(280 * zoom) + deplacX+ deplacZX, (260 * zoom) + deplacY+ deplacZY,(280 * zoom)+ deplacX+ deplacZX, (280 * zoom) + deplacY+ deplacZY,255,0,0,255);
	lineRGBA(renderer,(280 * zoom) + deplacX+ deplacZX, (280 * zoom) + deplacY+ deplacZY,(260 * zoom)+ deplacX+ deplacZX, (280 * zoom) + deplacY+ deplacZY,255,0,0,255);
	lineRGBA(renderer,(260 * zoom) + deplacX+ deplacZX, (280 * zoom) + deplacY+ deplacZY,(260 * zoom)+ deplacX+ deplacZX, (260 * zoom) + deplacY+ deplacZY,255,0,0,255);
	thickLineRGBA(renderer,(50 * zoom) + deplacX+ deplacZX, (60 * zoom) + deplacY+ deplacZY,(300 * zoom) + deplacX+ deplacZX, (311 * zoom) + deplacY+ deplacZY,a,255,0,0,255);
	thickLineRGBA(renderer,(30 * zoom) + deplacX+ deplacZX, (30 * zoom) + deplacY+ deplacZY,(40 * zoom) + deplacX+ deplacZX, (20 * zoom) + deplacY+ deplacZY,a,255,0,0,255);
	thickLineRGBA(renderer,(40 * zoom) + deplacX+ deplacZX, (20 * zoom) + deplacY+ deplacZY,(50 * zoom) + deplacX+ deplacZX, (50 * zoom) + deplacY+ deplacZY,a,255,0,0,255);
//	lineRGBA(renderer,(50 * zoom) + deplacX, (50 * zoom) + deplacY,(windows_Width-10 * zoom) + deplacX, (windows_Height-10*zoom) + deplacY,0,0,255,255);
//	lineRGBA(renderer,(XX * zoom) + deplacX + deplacZX, ((YY-10) * zoom) + deplacY + deplacZY,(XX * zoom) + deplacX + deplacZX, ((YY+10)*zoom) + deplacY + deplacZY,0,0,255,255);
//	lineRGBA(renderer,((XX-10) * zoom) + deplacX + deplacZX, (YY * zoom) + deplacY + deplacZY,((XX+10) * zoom) + deplacX + deplacZX, (YY*zoom) + deplacY + deplacZY,0,0,255,255);
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

/*	new 3

	zoom = 1;
	deplacX = 0;
	deplacY = 0;
	deplacZX = 0;
	deplacZY = 0;
	pasSourisX = 0;
	pasSourisY = 0;

	dessine();
*/ 	evenement();
   close_SDL();
    exit(EXIT_SUCCESS);

}
