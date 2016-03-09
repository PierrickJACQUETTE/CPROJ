#include "Avl.h"

int heightAVL(Avl **a){
	return (*a==NULL)? 0 : (*a)->height;
}

int height(int hL, int hD){
	return (hL>hD)? hL+1 : hD+1;
}

void rotationRight(Avl **a){
	Avl *aux = (*a)->left;
	int heightleft,heightright;

	(*a)->left = aux->right;
	aux->right = *a;
	*a = aux;

	heightleft = heightAVL(&(*a)->right->left);
	heightright = heightAVL(&(*a)->right->right);
	(*a)->right->height = height(heightleft, heightright) ;

	heightleft = heightAVL(&(*a)->left);
	heightright = heightAVL(&(*a)->right);
	(*a)->height = height(heightleft, heightright) ;
}

void rotationLeft(Avl **a){
	Avl *aux = (*a)->right;
	int heightleft,heightright;

	(*a)->right = aux->left;
	aux->left = *a;
	*a = aux;

	heightleft = heightAVL(&(*a)->left->left);
	heightright = heightAVL(&(*a)->left->right);
	(*a)->left->height = height(heightleft, heightright) ;

	heightleft = heightAVL(&(*a)->left);
	heightright = heightAVL(&(*a)->right);
	(*a)->height = height(heightleft, heightright) ;
}

void rotationRightLeft(Avl **a){
	rotationRight(&(*a)->right);
	rotationLeft(&(*a));
}

void rotationLeftRight(Avl **a){
	rotationLeft(&(*a)->left);
	rotationRight(&(*a));
}

void equilibrateAVL(Avl **a){
	int heightleft,heightright;
	if(*a!=NULL){
		heightleft = heightAVL(&(*a)->left);
		heightright = heightAVL(&(*a)->right);
		if(heightleft - heightright == 2){
			heightleft = heightAVL(&(*a)->left->left);
			heightright = heightAVL(&(*a)->left->right);
			if(heightleft>heightright){
				rotationRight(&(*a));
			}
			else{
				rotationLeftRight(&(*a));
			}
		}
		else if(heightleft - heightright==-2){
			heightleft = heightAVL(&(*a)->right->left);
			heightright = heightAVL(&(*a)->right->right);
			if(heightright>heightleft){
				rotationLeft(&(*a));
			}
			else{
				rotationRightLeft(&(*a)) ;
			}
		}
		else {
			heightleft = heightAVL(&(*a)->left);
			heightright = heightAVL(&(*a)->right);
			(*a)->height = height(heightleft, heightright) ;
		}
	}
}

Avl* insert(Avl **a,Node *n, Way * w){
	Avl *aux =NULL;

	if(*a){
		if(w==NULL){
			if((*a)->node->id == n->id){
				aux = *a;
			}
			else if(n->id < (*a)->node->id){
				(*a)->left = insert(&((*a)->left),n,NULL);
				equilibrateAVL(&(*a));
				aux= *a;
			}
			else if(n->id > (*a)->node->id){
				(*a)->right = insert(&((*a)->right),n,NULL);
				equilibrateAVL(&(*a));
				aux = *a;
			}
		}
		if(n==NULL){
			////////////////////////////////////////////////////////////////////

		}
	}
	else{
		aux = (Avl*) malloc(sizeof(Avl));
		if ( aux == NULL )
		{
			fprintf(stderr,"Allocation impossible : %s\n","fonction insert feuille");
			exit(EXIT_FAILURE);
		}
		aux->left = aux->right = NULL;
		aux->height = 1;
		if(w==NULL){aux->node = n;}
		if(n==NULL){aux->way = w;}
	}
	
	return aux;
}

Node* search(Avl *a, unsigned long key){
	if(a!=NULL){
		if(key == a->node->id){
			return a->node;
		}
		else if(key > a->node->id ){
			return search(a->right,key);
		}
		else{
			return search(a->left,key);
		}
	}
	return NULL;
}

void init(Avl **a,Node* n, Way *w){
	Avl *aux = (Avl*)malloc(sizeof(Avl));
	if(aux!=NULL){
		if(n==NULL && w==NULL){
			fprintf(stderr,"Allocation impossible : %s\n","fonction initAVL");
			exit(EXIT_FAILURE);
		}
		aux->left = aux->right = NULL;
		aux->height = 1;
		if(w==NULL){aux->node =n;}
		if(n==NULL){aux->way =w;}
		*a = aux;
	}
	else {
		fprintf(stderr,"Allocation impossible : %s\n","fonction init");
		exit(EXIT_FAILURE);
	}
}

void print(Avl **a,unsigned long nombre){
	if(*a == NULL){
		return;
	}
	print(&((*a)->right),nombre+1);
	if(nombre!=0){
		int i;
		for(i=0;i<nombre-1;i++){
			printf("|\t");
		}
		printf("|-------%f\n",(*a)->node->c->x);
	}
	else{
		printf("%ld\n",(*a)->node->id);
	}
	print(&((*a)->left),nombre+1);
}
