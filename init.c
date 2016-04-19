#include "init.h"



Node* initNode(unsigned long id, float lat, float lon, char* visible, Bounds *b){
	Node * n = malloc(sizeof(Node));
	if(n == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initNode");
		exit(EXIT_FAILURE);
	}
	if(b == NULL ||  b->min == NULL || id<0 || lat==100 || lon==100 || id==-1){
		return NULL;
	}
	n->id=id;
	int negativex = 0;
	int negativey = 0;
	if(b != NULL && b->min != NULL){
		if(lat < (b->min->y)){
			negativey = 1;
		}
		if(lon < (b->min->x)){
			negativex = 1;
		}
	}
	n->c = malloc(sizeof(Coordinate));
	if(n->c == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initNode");
		exit(EXIT_FAILURE);
	}
		n->c->x = distanceLatLon(lat, lon, lat, b->min->x);
		n->c->y = distanceLatLon(lat, lon, b->min->y, lon);
	if(negativex == 1){
		n->c->x = -(n->c->x);
	}
	if(negativey == 1){
		n->c->y = -(n->c->y);
	}
	if(strcmp(visible, "false")==0){
		n->visible="F";
	}
	else{
		n->visible="T";
	}
	return n;
}

Bounds* initBounds(float lat_min,float lat_max, float lon_min, float lon_max){
	Bounds *b=malloc(sizeof(Bounds));
	if(b == NULL || lat_min==100 || lon_min==100|| lon_max==100|| lat_max==100){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initBounds");
		return NULL;
	}
	b->min =malloc(sizeof(Coordinate));
	if(b->min == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initBounds");
		exit(EXIT_FAILURE);
	}
	b->max = malloc(sizeof(Coordinate));
	if(b->max == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initBounds");
		exit(EXIT_FAILURE);
	}
	b->min = conversionLatLon(lat_min, lon_min);
	b->max = conversionLatLon(lat_max, lon_max);
	return b;
}


Tag** initReferenceTag(){
	Tag **t = malloc(SIZETABTAG*sizeof(Tag*));
	if(t == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initReferenceTag");
		exit(EXIT_FAILURE);
	}
	int i = 1;
	for(i = 0; i < SIZETABTAG; i++){
		t[i] = malloc(sizeof(Tag));
		if(t[i] == NULL){
			fprintf(stderr,"Allocation impossible : %s\n","fonction initReferenceTag");
			exit(EXIT_FAILURE);
		}
		t[i]->c = malloc(sizeof(Color));
		if(t[i]->c == NULL){
			fprintf(stderr,"Allocation impossible : %s\n","fonction initReferenceTag");
			exit(EXIT_FAILURE);
		}
		t[i]->priority = 1;
		t[i]->thick = 0;
	}

	t[0]->tagKey ="highway"; t[0]->tagValue ="primary_link"; t[0]->c->red=255; t[0]->c->green=102; t[0]->c->blue=51; //orange
	t[1]->tagKey ="highway"; t[1]->tagValue ="footway"; t[1]->c->red=255; t[1]->c->green=102; t[1]->c->blue=51;//orange
	t[2]->tagKey ="highway"; t[2]->tagValue ="residential"; t[2]->c->red=135; t[2]->c->green=135; t[2]->c->blue=135; //gris clair	
	t[3]->tagKey ="highway"; t[3]->tagValue ="secondary_link"; t[3]->c->red=255; t[3]->c->green=204; t[3]->c->blue=51; //jaune
	t[4]->tagKey ="highway"; t[4]->tagValue ="tertiary_link"; t[4]->c->red=80; t[4]->c->green=80; t[4]->c->blue=80; //gris fonce
	t[5]->tagKey ="highway"; t[5]->tagValue ="trunk"; t[5]->c->red=255; t[5]->c->green=51; t[5]->c->blue=0; //orange fonce
	t[6]->tagKey ="highway"; t[6]->tagValue ="trunk_link"; t[6]->c->red=255; t[6]->c->green=51; t[6]->c->blue=0; //orange fonce
	t[7]->tagKey ="highway"; t[7]->tagValue ="road"; t[7]->c->red=155; t[7]->c->green=155; t[7]->c->blue=155; //gris moyen
	t[8]->tagKey ="highway"; t[8]->tagValue ="pedestrian"; t[8]->c->red=190; t[8]->c->green=190; t[8]->c->blue=190; //gris tres tres
	t[9]->tagKey ="highway"; t[9]->tagValue ="service"; t[9]->c->red=170; t[9]->c->green=170; t[9]->c->blue=170; //gris tres clair	
	t[10]->tagKey ="highway"; t[10]->tagValue ="secondary"; t[10]->c->red=255; t[10]->c->green=204; t[10]->c->blue=51; //jaune
	t[11]->tagKey ="highway"; t[11]->tagValue ="unclassified"; t[11]->c->red=115; t[11]->c->green=115; t[11]->c->blue=115; //gris moyen
	t[12]->tagKey ="highway"; t[12]->tagValue ="motorway"; t[12]->c->red=255; t[12]->c->green=0; t[12]->c->blue=0; //rouge
	t[13]->tagKey ="highway"; t[13]->tagValue ="motorway_link"; t[13]->c->red=255; t[13]->c->green=0; t[13]->c->blue=0; // rouge
	t[14]->tagKey ="highway"; t[14]->tagValue ="tertiary"; t[14]->c->red=80; t[14]->c->green=80; t[14]->c->blue=80; //gris fonce
	t[15]->tagKey ="highway"; t[15]->tagValue ="primary"; t[15]->c->red=255; t[15]->c->green=102; t[15]->c->blue=51; //orange
	t[16]->tagKey ="service"; t[16]->tagValue ="alley"; t[16]->c->red=255; t[16]->c->green=255; t[16]->c->blue=204; //jaune pale
	

	t[17]->tagKey ="waterway"; t[17]->tagValue ="canal"; t[17]->c->red=51; t[17]->c->green=102; t[17]->c->blue=204; //bleu fonce
	t[18]->tagKey ="waterway"; t[18]->tagValue ="water"; t[18]->c->red=51; t[18]->c->green=204; t[18]->c->blue=255;
	t[19]->tagKey ="natural"; t[19]->tagValue ="coastline"; t[19]->c->red=255; t[19]->c->green=255; t[19]->c->blue=255; //blanc
	t[20]->tagKey ="natural"; t[20]->tagValue ="water"; t[20]->c->red=0; t[20]->c->green=55; t[20]->c->blue=204;
	t[21]->tagKey ="waterway"; t[21]->tagValue ="riverbank"; t[21]->c->red=0; t[21]->c->green=153; t[21]->c->blue=204;

	t[22]->tagKey ="leisure"; t[22]->tagValue ="playground"; t[22]->c->red=51; t[22]->c->green=153; t[22]->c->blue=0;	
	t[23]->tagKey ="landuse"; t[23]->tagValue ="forest"; t[23]->c->red=51; t[23]->c->green=102; t[23]->c->blue=0; //vert
	t[24]->tagKey ="landuse"; t[24]->tagValue ="grass"; t[24]->c->red=102; t[24]->c->green=204; t[24]->c->blue=51;
	t[25]->tagKey ="leisure"; t[25]->tagValue ="park"; t[25]->c->red=51; t[25]->c->green=153; t[25]->c->blue=0;
	t[26]->tagKey ="leisure"; t[26]->tagValue ="garden"; t[26]->c->red=0; t[26]->c->green=200; t[26]->c->blue=0;
	t[27]->tagKey ="barrier"; t[27]->tagValue ="fence"; t[27]->c->red=51; t[27]->c->green=153; t[27]->c->blue=0;	
	
	t[28]->tagKey ="building"; t[28]->tagValue ="church"; t[28]->c->red=133; t[28]->c->green=109; t[28]->c->blue=77; //marron
	t[29]->tagKey ="leisure"; t[29]->tagValue ="marina"; t[29]->c->red=255; t[29]->c->green=255; t[29]->c->blue=204; // jaune pale clair
	t[30]->tagKey ="building"; t[30]->tagValue ="yes"; t[30]->c->red=205; t[30]->c->green=183; t[30]->c->blue=158;	//beige
	
	t[31]->tagKey ="surface"; t[31]->tagValue ="ground"; t[31]->c->red=255; t[31]->c->green=255; t[31]->c->blue=255; //blanc
	t[32]->tagKey ="surface"; t[32]->tagValue ="gravel"; t[32]->c->red=255; t[32]->c->green=0; t[32]->c->blue=0; //blanc
	t[33]->tagKey ="barrier"; t[33]->tagValue ="wall"; t[33]->c->red=0; t[33]->c->green=50; t[33]->c->blue=0;
	t[34]->tagKey ="amenity"; t[34]->tagValue ="hospital"; t[34]->c->red=255; t[34]->c->green=150; t[34]->c->blue=102; // saumon
	t[35]->tagKey ="bridge"; t[35]->tagValue ="yes"; t[35]->c->red=255; t[35]->c->green=255; t[35]->c->blue=204; //jaune pale
	
	t[36]->tagKey ="source"; t[36]->tagValue ="cadastre-dgi-fr source : Direction Générale des Impôts - Cadastre. Mise à jour : 2010"; t[36]->c->red=255; t[36]->c->green=255; t[36]->c->blue=255; //blanc

	t[0]->type= 3; 	t[0]->thick=9;   // 1=water, 2=green, 3=highway, 4= building, 0=other; 5= cadastre;
	t[1]->type= 3; 	t[1]->thick=1;
	t[2]->type= 3; 	t[2]->thick=6;
	t[3]->type= 3; 	t[3]->thick=9;
	t[4]->type= 3; 	t[4]->thick=9;
	t[5]->type= 3; 	t[5]->thick=9;
	t[6]->type= 3; 	t[6]->thick=9;
	t[7]->type= 3; 	t[7]->thick=4;
	t[8]->type= 3;	t[8]->thick=3;
	t[9]->type= 3; 	t[9]->thick=5;
	t[10]->type=3; 	t[10]->thick=9;
	t[11]->type= 3; t[11]->thick=7;
	t[12]->type= 3; t[12]->thick=9;
	t[13]->type= 3; t[13]->thick=9;
	t[14]->type= 3; t[14]->thick=9;
	t[15]->type= 3; t[15]->thick=9;
	t[16]->type= 3; t[16]->thick=1;                 	

	t[17]->type= 1;
	t[18]->type= 1;
	t[19]->type= 1; 
	t[20]->type= 1;
	t[21]->type= 1;

	t[22]->type= 2;
	t[23]->type= 2;
	t[24]->type= 2;
	t[25]->type= 2;
	t[26]->type= 2;
	t[27]->type= 5;

	t[28]->type= 4;
	t[29]->type= 4; 
	t[30]->type= 4;

	t[31]->type= 0;
	t[32]->type= 0; 
	t[33]->type= 0; 
	t[34]->type= 0; 
	t[35]->type= 0;				t[35]->priority=0;
	 
	t[36]->type= 5; 			t[36]->priority=0;
	return t;

}


refListNode* initRefListNode(unsigned long  n, refListNode* next){
	refListNode* r= malloc(sizeof(refListNode));
	if(r == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initRefListNode");
		exit(EXIT_FAILURE);
	}
	r->nd = n;
	r->next = next;
	return r;
}

ListNode* initListNode(unsigned long first){
	ListNode* l = malloc(sizeof(ListNode));
	if(l == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initListNode");
		exit(EXIT_FAILURE);
	}
	refListNode* f = initRefListNode(first,NULL);
	l->firstRef = f;
	l->lastRef = f;
	return l;
}

ListNode* addRefListNode(unsigned long n, ListNode* l){
	refListNode* r = initRefListNode(n,NULL);
	if(l != NULL){
		if((l->firstRef != NULL) && (l->firstRef->nd != 0)){
			l->lastRef->next = r;
			l->lastRef = r;
			return l;
		}
		else{
			l->firstRef = r;
			l->lastRef = r;
			return l;
		}
	}
	else{
		l=initListNode(n);
	}
	return l;
}

Tag* initTag(char* key, char* value, Color* c, int type, int thick, int priority){
	Tag* t = malloc(sizeof(Tag));
	if(t == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initTag");
		exit(EXIT_FAILURE);
	}
	if(c==NULL){
		return NULL;
	}
	t->tagKey = key;
	t->tagValue = value;
	t->c = c;
	t->type = type;
	t->thick = thick;
	t->priority = priority;
	return t;
}

Way* initWay(unsigned long id, char* visible, ListNode* ln, Tag* tag,int size, char* nameway){
	Way* w = malloc(sizeof(Way));
	if(w == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initWay");
		exit(EXIT_FAILURE);
	}
	if(id==-1){
		return NULL;
	}
	w->id = id;
	w->listNd = ln;
	if(strcmp(visible, "false")==0){
		w->visible = "F";
	}
	else{
		w->visible = "T";
	}
	w->tag=malloc(sizeof(Tag));
	if(w->tag == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initWay");
		exit(EXIT_FAILURE);
	}
	w->tag = tag;
	w->size = size;
	w->draw = 0;
	if(nameway != NULL){
		w->name=malloc(sizeof(char*)*strlen(nameway));
		strcpy(w->name,nameway);
	}
	else{
		w->name = NULL;
	}
	return w;
}

Relation* initRelation(unsigned long id, char* visible,Tag* t, ListWay* lw, ListNode* ln){
	Relation* r = malloc(sizeof(Relation));
	if(r == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initRelation");
		exit(EXIT_FAILURE);
	}
	if(id==-1){
		return NULL;
	}
	r->id = id;
	r->listW = lw;
	r->listN = ln;
	r->tag = t;
	if(strcmp(visible, "false")==0){
		r->visible = "F";
	}
	else{
		r->visible = "T";
	}
	return r;
}
Tag * goodTagRelation(char * k, char *v){
	if(strcmp(k, "type")==0 && (strcmp(v,"multipolygon")==0 || strcmp(v,"route")==0)){
		return initTag(k, v, NULL, -1, 0, 0);
	}
	return NULL;
}

Tag* goodTag(char * k, char *v, Tag**  ref){
	int i = 0;
	if(ref != NULL){
		for(i = 0; i < SIZETABTAG; i++){
			if(ref[i] != NULL){
				if(strcmp(k, ref[i]->tagKey)==0 && strcmp(v, ref[i]->tagValue) ==0){
					return initTag(k, v, ref[i]->c,ref[i]->type, ref[i]->thick, ref[i]->priority);
				}
			}
		}
	}
	return NULL;
}

refListWay* initRefListWay(unsigned long  w, char *role, refListWay* next){
	refListWay* r = malloc(sizeof(refListWay));
	if(r == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initRefListWay");
		exit(EXIT_FAILURE);
	}
	r->way = w;
	if(strcmp(role, "inner") ==0){
		r->role = "inner";
	}
	else{
		r->role = "outer";
	}
	r->next = next;
	return r;
}

ListWay* initListWay(unsigned long first){
	ListWay* l = malloc(sizeof(ListWay));
	if(l == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initListWay");
		exit(EXIT_FAILURE);
	}
	refListWay* f = initRefListWay(first, " ",NULL);
	l->firstRef = f;
	l->lastRef = f;
	return l;
}


ListWay* addRefListWay(unsigned long way,char *role, ListWay* lw){
	refListWay* r = initRefListWay(way,role, NULL);
	if(lw != NULL){
		if((lw->firstRef != NULL) && (lw->firstRef->way != 0)){
			lw->lastRef->next = r;
			lw->lastRef = r;
			return lw;
		}
		else{
			lw->firstRef = r;
			lw->lastRef = r;
			return lw;
		}
	}
	else{
		lw = initListWay(way);
	}
	return lw;
}


refListRel* initRefListRel(Relation* id, refListRel* next){
	refListRel* r = malloc(sizeof(refListRel));
	if(r == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initRefListRel");
		exit(EXIT_FAILURE);
	}
	r->relation = malloc(sizeof(Relation));
	if(r->relation == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initRefListRel");
		exit(EXIT_FAILURE);
	}
	r->relation = id;
	r->next = next;
	return r;
}

ListRelation* initListRelation(Relation* first){
	ListRelation* l = malloc(sizeof(ListRelation));
	if(l == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initListRelation");
		exit(EXIT_FAILURE);
	}
	refListRel* f = initRefListRel(first,NULL);
	l->firstRef = f;
	l->lastRef = f;
	return l;
}

ListRelation* addRefListRelation(Relation* id ,ListRelation* lr){
	refListRel* r = initRefListRel(id,NULL);
	if(lr != NULL){
		if((lr->firstRef != NULL) && (lr->firstRef->relation !=0 )){
			lr->lastRef->next = r;
			lr->lastRef = r;
			return lr;
		}
		else{
			lr->firstRef = r;
			lr->lastRef = r;
			return lr;
		}
	}
	else{
		lr = initListRelation(id);
	}
	return lr;
}
Map* initMap(){
	Map * map = malloc(sizeof(Map));
	if(map == NULL){
		fprintf(stderr,"Allocation impossible : %s\n","fonction initMap");
		exit(EXIT_FAILURE);
	}
	map->referenceTag = initReferenceTag();
	return map;
}
