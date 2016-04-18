#include "Avl.h"

int heightAVL(Avl **a){
	return (*a == NULL)? 0 : (*a)->height;
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
	if(*a != NULL){
		heightleft = heightAVL(&(*a)->left);
		heightright = heightAVL(&(*a)->right);
		if(heightleft - heightright == 2){
			heightleft = heightAVL(&(*a)->left->left);
			heightright = heightAVL(&(*a)->left->right);
			if(heightleft > heightright){
				rotationRight(&(*a));
			}
			else{
				rotationLeftRight(&(*a));
			}
		}
		else if(heightleft - heightright ==-2){
			heightleft = heightAVL(&(*a)->right->left);
			heightright = heightAVL(&(*a)->right->right);
			if(heightright > heightleft){
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

Avl* insert(Avl **a, Node *n, Way * w){
	Avl *aux = NULL;
	if(n == NULL && w == NULL){
		fprintf(stderr,"Insertion impossible car le type de l'avl n'est pas définie: %s\n","fonction insertAVL");
		return NULL;
	}
	if(n != NULL && w != NULL){
		fprintf(stderr,"Insertion impossible car le type de l'avl est trop definie: %s\n","fonction insertAVL");
		return NULL;
	}
	if(*a){
		if(w == NULL){
			if((*a)->node->id == n->id){
				fprintf(stderr,"Insertion impossible car il existe deja ce noeud dans l'avl: %s\n","fonction insertAVL");
				return NULL;
			}
			else if(n->id < (*a)->node->id){
				(*a)->left = insert(&((*a)->left),n,NULL);
				equilibrateAVL(&(*a));
				aux = *a;
			}
			else if(n->id > (*a)->node->id){
				(*a)->right = insert(&((*a)->right),n,NULL);
				equilibrateAVL(&(*a));
				aux = *a;
			}
		}
		if(n == NULL){
			if((*a)->way->id == w->id){
				aux = *a;
			}
			else if(w->id < (*a)->way->id){
				(*a)->left = insert(&((*a)->left),NULL,w);
				equilibrateAVL(&(*a));
				aux= *a;
			}
			else if(w->id > (*a)->way->id){
				(*a)->right = insert(&((*a)->right),NULL,w);
				equilibrateAVL(&(*a));
				aux = *a;
			}
		}
	}
	else{
		aux = (Avl*) malloc(sizeof(Avl));
		if ( aux == NULL ){
			fprintf(stderr,"Allocation impossible : %s\n","fonction insert feuille");
			exit(EXIT_FAILURE);
		}
		aux->left = aux->right = NULL;
		aux->height = 1;
		if(w == NULL){
			aux->node = n;
		}
		if(n == NULL){
			aux->way = w;
		}
	}
	return aux;
}

Node* searchNode(Avl *a, unsigned long key){
	if(a != NULL){
		if(key == a->node->id){
			return a->node;
		}
		else if(key > a->node->id ){
			return searchNode(a->right,key);
		}
		else{
			return searchNode(a->left,key);
		}
	}
	return NULL;
}

Way* searchWay(Avl *a, unsigned long key){
	if(a != NULL){
		if(key == a->way->id){
			return a->way;
		}
		else if(key > a->way->id ){
			return searchWay(a->right,key);
		}
		else{
			return searchWay(a->left,key);
		}
	}
	return NULL;
}

Avl * init(Avl **a, Node* n, Way *w){
	if(*a != NULL){
		fprintf(stderr,"Il y a deja des elements dans l'avl, appeler la methode insert: %s\n","fonction initAVL");
		return NULL;
	}
	else{
		Avl *aux = (Avl*)malloc(sizeof(Avl));
		if(aux != NULL){
			if(n == NULL && w == NULL){
				fprintf(stderr,"Allocation impossible car le type de l'avl n'est pas définie: %s\n","fonction initAVL");
				return NULL;
			}
			if(n != NULL && w != NULL){
				fprintf(stderr,"Allocation impossible car le type de l'avl est trop definie: %s\n","fonction initAVL");
				return NULL;
			}
			aux->left = aux->right = NULL;
			aux->height = 1;
			if(w == NULL){
				aux->node = n;
				aux->way = NULL;
			}
			if(n == NULL){
				aux->way = w;
				aux->node = NULL;
			}
			*a = aux;
		}
		else {
			fprintf(stderr,"Allocation impossible : %s\n","fonction init");
			exit(EXIT_FAILURE);
		}
		return aux;
	}
}

void printNode(Avl **a, unsigned long nombre){
	if(*a == NULL){
		return;
	}
	printNode(&((*a)->right),nombre+1);
	if(nombre != 0){
		int i;
		for(i = 0; i < nombre-1; i++){
			printf("|\t");
		}
		printf("|-----: %ld\n",(*a)->node->id);
	}
	else{
		printf("%ld\n",(*a)->node->id);
	}
	printNode(&((*a)->left),nombre+1);
}

void printWay(Avl **a, unsigned long nombre){
	if(*a == NULL){
		return;
	}
	printWay(&((*a)->right),nombre+1);
	if(nombre != 0){
		int i;
		for(i=0; i<nombre-1; i++){
			printf("|\t");
		}
		printf("|-----: %ld\n",(*a)->way->id);
	}
	else{
		printf("%ld\n",(*a)->way->id);
	}
	printWay(&((*a)->left),nombre+1);
}
