#include "init.h"


Node* initNode(unsigned long id, float lat, float lon, char* visible, Bounds *b){
	Node * n= malloc(sizeof(Node));
	n->id=id;
	int negativex=0;
	int negativey=0;
	if(lat<(b->min->y)){negativey=1;}
	if(lon<(b->min->x)){negativex=1;}
	n->c= malloc(sizeof(Coordinate));
	//n->c= conversionLatLon(lat, lon);
	//n->c->x= n->c->x - b->min->x;
	//n->c->y= n->c->y - b->min->y;
	n->c->x= distanceLatLon(lat, lon, lat, b->min->x);
	if(negativex==1){ n->c->x = -(n->c->x);}
	n->c->y= distanceLatLon(lat, lon, b->min->y, lon);
	if(negativey==1){ n->c->y = -(n->c->y);}
	if(strcmp(visible, "true")==0){
		n->visible="T";
	}
	else{
		n->visible="F";
	}
	return n;
}

Bounds* initBounds(float lat_min,float lat_max, float lon_min, float lon_max){
	Bounds *b=malloc(sizeof(Bounds));
	b->min =malloc(sizeof(Coordinate));
	b->max = malloc(sizeof(Coordinate));
	b->min= conversionLatLon(lat_min, lon_min);
	b->max= conversionLatLon(lat_max, lon_max);
	return b;
}


Tag** initReferenceTag(){
	Tag **t=malloc(29*sizeof(Tag*));
	int i=1;
	for(i=0; i<29; i++){
		t[i]=malloc(sizeof(Tag));
		t[i]->c=malloc(sizeof(Color));
	}
	t[0]->tagKey ="landuse"; t[0]->tagValue ="forest"; t[0]->c->red=51; t[0]->c->green=102; t[0]->c->blue=0; //vert
	t[1]->tagKey ="building"; t[1]->tagValue ="yes"; t[1]->c->red=205; t[1]->c->green=183; t[1]->c->blue=158;	//beige
	t[2]->tagKey ="highway"; t[2]->tagValue ="residential"; t[2]->c->red=255; t[2]->c->green=255; t[2]->c->blue=204; //jaune pale
	t[3]->tagKey ="waterway"; t[3]->tagValue ="canal"; t[3]->c->red=51; t[3]->c->green=102; t[3]->c->blue=204; //bleu fonce
	t[4]->tagKey ="waterway"; t[4]->tagValue ="river"; t[4]->c->red=0; t[4]->c->green=153; t[4]->c->blue=255; //bleu clair
	t[5]->tagKey ="waterway"; t[5]->tagValue ="water"; t[5]->c->red=51; t[5]->c->green=204; t[5]->c->blue=255;
	t[6]->tagKey ="waterway"; t[6]->tagValue ="coastline"; t[6]->c->red=0; t[6]->c->green=204; t[6]->c->blue=255;
	t[7]->tagKey ="landuse"; t[7]->tagValue ="grass"; t[7]->c->red=102; t[7]->c->green=204; t[7]->c->blue=51;
	t[8]->tagKey ="leisure"; t[8]->tagValue ="park"; t[8]->c->red=51; t[8]->c->green=153; t[8]->c->blue=0;
	t[9]->tagKey ="highway"; t[9]->tagValue ="service"; t[9]->c->red=255; t[9]->c->green=255; t[9]->c->blue=204; //jaune pale
	t[10]->tagKey ="highway"; t[10]->tagValue ="secondary"; t[10]->c->red=255; t[10]->c->green=255; t[10]->c->blue=204; //jaune pale
/**/	t[11]->tagKey ="highway"; t[11]->tagValue ="unclassified"; t[11]->c->red=255; t[11]->c->green=255; t[11]->c->blue=204; //jaune pale
	t[12]->tagKey ="highway"; t[12]->tagValue ="motorway"; t[12]->c->red=255; t[12]->c->green=255; t[12]->c->blue=204; //jaune pale
	t[13]->tagKey ="highway"; t[13]->tagValue ="motorway_link"; t[13]->c->red=255; t[13]->c->green=255; t[13]->c->blue=204; //jaune pale
	t[14]->tagKey ="natural"; t[14]->tagValue ="water"; t[14]->c->red=0; t[14]->c->green=55; t[14]->c->blue=204;
	t[15]->tagKey ="highway"; t[15]->tagValue ="primary"; t[15]->c->red=255; t[15]->c->green=255; t[15]->c->blue=204; //jaune pale
	t[16]->tagKey ="bridge"; t[16]->tagValue ="yes"; t[16]->c->red=255; t[16]->c->green=255; t[16]->c->blue=204; //jaune pale
	t[18]->tagKey ="leisure"; t[18]->tagValue ="garden"; t[18]->c->red=0; t[18]->c->green=200; t[18]->c->blue=0;
	t[17]->tagKey ="natural"; t[17]->tagValue ="coastline"; t[17]->c->red=0; t[17]->c->green=0; t[17]->c->blue=0; //noir
	t[19]->tagKey ="highway"; t[19]->tagValue ="pedestrian"; t[19]->c->red=255; t[19]->c->green=255; t[19]->c->blue=204; //jaune pale
	t[20]->tagKey ="service"; t[20]->tagValue ="alley"; t[20]->c->red=255; t[20]->c->green=255; t[20]->c->blue=204; //jaune pale
	t[21]->tagKey ="layer"; t[21]->tagValue ="1"; t[21]->c->red=255; t[21]->c->green=255; t[21]->c->blue=204; //jaune pale
	t[22]->tagKey ="surface"; t[22]->tagValue ="ground"; t[22]->c->red=0; t[22]->c->green=0; t[22]->c->blue=0; //noir
	t[23]->tagKey ="surface"; t[23]->tagValue ="gravel"; t[23]->c->red=0; t[23]->c->green=0; t[23]->c->blue=0; //noir
	t[24]->tagKey ="source"; t[24]->tagValue ="cadastre-dgi-fr source : Direction Générale des Impôts - Cadastre. Mise à jour : 2010"; t[24]->c->red=0; t[24]->c->green=0; t[24]->c->blue=0; //noir
	t[25]->tagKey ="waterway"; t[25]->tagValue ="riverband"; t[25]->c->red=0; t[25]->c->green=50; t[25]->c->blue=200;
	t[26]->tagKey ="highway"; t[26]->tagValue ="footway"; t[26]->c->red=255; t[26]->c->green=255; t[26]->c->blue=204; //jaune pale
	t[27]->tagKey ="barrier"; t[27]->tagValue ="wall"; t[27]->c->red=0; t[27]->c->green=50; t[27]->c->blue=0;
	t[28]->tagKey ="leisure"; t[28]->tagValue ="playground"; t[28]->c->red=51; t[28]->c->green=153; t[28]->c->blue=0;
	t[0]->type= 2; t[0]->thick=0;  // 1=water, 2=green, 3=highway, 4= building, 0=other;
	t[1]->type= 4; t[1]->thick=0;
	t[2]->type= 3; t[2]->thick=0;
	t[3]->type= 1; t[3]->thick=0;
	t[4]->type= 1; t[4]->thick=0;
	t[5]->type= 1; t[5]->thick=0;
	t[6]->type= 1; t[6]->thick=0;
	t[7]->type= 2; t[7]->thick=0;
	t[8]->type= 2; t[8]->thick=0;
	t[9]->type= 3; t[9]->thick=0;
	t[10]->type=3; t[10]->thick=0;
	t[11]->type= 3; t[11]->thick=0;
	t[12]->type= 3; t[12]->thick=0;
	t[13]->type= 3; t[13]->thick=0;
	t[14]->type= 1; t[14]->thick=0;
	t[15]->type= 3; t[15]->thick=0;
	t[16]->type= 3; t[16]->thick=0;
	t[17]->type= 1; t[17]->thick=0;
	t[18]->type= 2; t[18]->thick=0;
	t[19]->type= 3; t[19]->thick=0;
	t[20]->type= 3; t[20]->thick=0;
	t[21]->type= 0; t[21]->thick=0;
	t[22]->type= 0; t[22]->thick=0;
	t[23]->type= 0; t[23]->thick=0;
	t[24]->type= 0; t[24]->thick=0;
	t[25]->type= 1; t[25]->thick=0;
	t[26]->type= 3; t[26]->thick=0;
	t[27]->type= 4; t[27]->thick=0;
	t[28]->type= 2; t[28]->thick=0;
	return t;

}


refListNode* initRefListNode(unsigned long  n, refListNode* next){
	refListNode* r=malloc(sizeof(refListNode));
	r->nd=n;
	r->next=next;
	return r;
}

ListNode* initListNode(unsigned long first){
	ListNode* l=malloc(sizeof(ListNode));
	refListNode* f=initRefListNode(first,NULL);
	l->firstRef=f;
	l->lastRef=f;
	return l;
}

ListNode* addRefListNode(unsigned long n, ListNode* l){
	refListNode* r=initRefListNode(n, NULL);
	if(l!=NULL){
		if((l->firstRef!=NULL) && (l->firstRef->nd!=0)){
			l->lastRef->next=r;
			l->lastRef=r;
			return l;
		}
		else{
			l->firstRef=r;
			l->lastRef=r;
			return l;
		}
	}
	else{
		l=initListNode(n);
	}
	return l;
}

Tag* initTag(char* key, char* value, Color* c, int type, int thick){
	Tag* t=malloc(sizeof(Tag));
	t->tagKey=key;
	t->tagValue=value;
	t->c=c;
	t->type=type;
	t->thick=thick;
	return t;
}

Way* initWay(unsigned long id, char* visible, ListNode* ln, Tag* tag,int size){
	Way* w= malloc(sizeof(Way));
	w->id=id;
	w->listNd=ln;
	if(strcmp(visible, "true")==0){
		w->visible="T";
	}
	else{
		w->visible="F";
	}
	w->tag=malloc(sizeof(Tag));
	w->tag=tag;
	w->size=size;
	//printf("size way: %d\n",w->size);
	return w;
}

Relation* initRelation(unsigned long id, char* visible,Tag* t, ListWay* lw, ListNode* ln){
	Relation* r= malloc(sizeof(Relation));
	r->id=id;
	r->listW=lw;
	r->listN=ln;
	r->tag=t;
	if(strcmp(visible, "true")==0){
		r->visible="T";
	}
	else{
		r->visible="F";
	}
	return r;
}
Tag * goodTagRelation(char * k, char *v){
	if(strcmp(k, "type")==0 && (strcmp(v,"multipolygon")==0 ||strcmp(v,"route")==0) ){
		return initTag(k, v, NULL, -1, 0);
	}
	return NULL;
}

Tag* goodTag(char * k, char *v, Tag**  ref){
	int i=0;
	if(ref!=NULL){
		for(i=0; i<29; i++){
			if(ref[i]!=NULL){
				if(strcmp(k, ref[i]->tagKey)==0 && strcmp(v, ref[i]->tagValue)==0){
					return initTag(k, v, ref[i]->c,ref[i]->type, ref[i]->thick);
				}
			}
		}
	}
	return NULL;
}


refListWay* initRefListWay(unsigned long  w, char *role, refListWay* next){
	refListWay* r=malloc(sizeof(refListWay));
	r->way=w;
	if(strcmp(role, "inner")==0){
		r->role="inner";
	}
	else{
		r->role="outer";
	}
	r->next=next;
	return r;
}

ListWay* initListWay(unsigned long first){
	ListWay* l=malloc(sizeof(ListWay));
	refListWay* f=initRefListWay(first, " ",NULL);
	l->firstRef=f;
	l->lastRef=f;
	return l;
}


ListWay* addRefListWay(unsigned long way,char *role, ListWay* lw){
	refListWay* r=initRefListWay(way,role, NULL);
	if(lw!=NULL){
		if((lw->firstRef!=NULL) && (lw->firstRef->way!=0)){
			lw->lastRef->next=r;
			lw->lastRef=r;
			return lw;
		}
		else{
			lw->firstRef=r;
			lw->lastRef=r;
			return lw;
		}
	}
	else{
		lw=initListWay(way);
	}
	return lw;
}


refListRel* initRefListRel(Relation* id, refListRel* next){
	refListRel* r=malloc(sizeof(refListRel));
	r->relation=malloc(sizeof(Relation));
	r->relation=id;
	r->next=next;
	return r;
}

ListRelation* initListRelation(Relation* first){
	ListRelation* l=malloc(sizeof(ListRelation));
	refListRel* f=initRefListRel(first,NULL);
	l->firstRef=f;
	l->lastRef=f;
	return l;
}

ListRelation* addRefListRelation(Relation* id ,ListRelation* lr){
	refListRel* r=initRefListRel(id,NULL);
	if(lr!=NULL){
		if((lr->firstRef!=NULL) && (lr->firstRef->relation!=0)){
			lr->lastRef->next=r;
			lr->lastRef=r;
			return lr;
		}
		else{
			lr->firstRef=r;
			lr->lastRef=r;
			return lr;
		}
	}
	else{
		lr=initListRelation(id);
	}
	return lr;
}
Map* initMap(){
	Map * map = malloc(sizeof(Map));
	map->referenceTag=initReferenceTag();
	return map;
}
