#include "conversionElements.h"

int windows_Height;
int windows_Width;
SDL_Renderer* renderer;
SDL_Window *window;
int quit;

int deplacX;
int deplacY;
float zoom;
int pasSourisX;
int pasSourisY;
int deplacZX;
int deplacZY;
int clicker;

Coordinate* conversionLatLon(float lat, float lon){
	Coordinate *c= malloc(sizeof(Coordinate));
	c->x=lon;
	c->y=lat;
	return c;
}

Bounds* convertBounds(Bounds *b ){
	b->max->x = distanceLatLon(b->min->y, b->min->x, b->min->y, b->max->x);
	b->max->y = distanceLatLon(b->min->y, b->min->x, b->max->y, b->min->x);
	b->min->x = 0;
	b->min->y = 0;
	return b;
}

float distanceXY(float x1, float y1, float x2, float y2){
	return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}

float distanceY(float y1, float y2){
	return distanceXY(0, y1, 0, y2);
}

float distanceX(float x1, float x2){
	return distanceXY(x1, 0, x2, 0);
}

float normalize(float a, float b,float length){
	return (b - a) / length;
}

float distanceLatLon(float lat1, float lon1, float lat2, float lon2){
	int EarthRayon = 6371;
	lon1 = lon1*M_PI / 180;
	lon2 = lon2*M_PI / 180;
	lat1 = lat1*M_PI / 180;
	lat2 = lat2*M_PI / 180;
	float dlon = (lon2 - lon1) / 2;
	float dlat = (lat2 - lat1) / 2;
	float a = sinf(dlat) * sinf(dlat) + cosf(lat1) * cosf(lat2) * sinf(dlon) * sinf(dlon);
	return EarthRayon * 2 * atan2(sqrt(a), sqrt(1 - a));
}

float angle(float ax, float ay, float bx,float by,float cx,float cy){
	float longeurAB = distanceXY(ax,ay,bx,by);
	float longeurBC = distanceXY(bx,by,cx,cy);
	float quotientSin = ((ax-bx)*(cx-bx))-((ay-by)*(cy-by));
	float quotient = ((ax-bx)*(cx-bx))+((ay-by)*(cy-by));
	float cos = acosf(quotient/(2*longeurAB*longeurBC));
	if(quotientSin>0){
		return cos*180/M_PI;
	}
	else{
		return 0-(cos*180/M_PI);
	}
}

Sint16 * extremite(float a, float d, float e, Sint16 tab[4], int signe,int extremite){
	if(extremite == 2){
		if(signe == 1){
			tab[3] = a + d;
			tab[2] = a - e;
		}
		else{
			tab[3] = a - d;
			tab[2] = a + e;
		}
	}
	else{
		if(signe ==1){
			tab[0] = a + d;
			tab[1] = a - e;
		}
		else{
			tab[0] = a - d;
			tab[1] = a + e;
		}
	}
	return tab;
}

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

Sint16* swap(Sint16 tab[4]){
	tab[0] = tab[2];
	tab[1] = tab[3];
	tab[2] = 0;
	tab[3] = 0;
	return tab;
}

float miseAEchelleX(float x, float y,int size){
	return ((x * size / y) * zoom) + deplacX + deplacZX;
}

float miseAEchelleY(float x, float y,int size){
	return ((size - (x * size / y)) * zoom) + deplacY + deplacZY;
}

float calculateZoom(int refX, int refY,float decalage,int flag){
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
	return decalage;
}

int colorBackground(int red, int blue, int green,int oppacity){
	if(SDL_SetRenderDrawColor(renderer,red,blue,green,oppacity) < 0) {
		fprintf(stderr,"Renderer color could not be set! SDL Error: %s\n",SDL_GetError());
		return 0;
	}
	return 1;
}

int colorBackgroundDefault(){
	return colorBackground(0xFF,0xFF,0xFF,0xFF);
}
