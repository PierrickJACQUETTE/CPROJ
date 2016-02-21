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

Avl* insert(Avl **a,int content){
	Avl *aux =NULL;
	if(*a){
		if((*a)->node->id == content){
			aux = *a;
		}
		else if(content < (*a)->node->id){
			(*a)->left = insert(&((*a)->left),content);
			equilibrateAVL(&(*a));
			aux= *a;
		}
		else if(content > (*a)->node->id){
			(*a)->right = insert(&((*a)->right),content);
			equilibrateAVL(&(*a));
			aux = *a;
		}
	}
	else{
		aux = (Avl*) malloc(sizeof(Avl));
		Node *n = (Node*)malloc(sizeof(Node));
		aux->left = aux->right = NULL;
		n->id = content;
		aux->node = n;
		aux->height = 1;
	}
	return aux;
}

Node* search(Avl *a, int key){
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

void init(Avl **a,int content){
	Avl *aux = (Avl*)malloc(sizeof(Avl));
	if(aux!=NULL){
		Node *n = (Node*)malloc(sizeof(Node));
		n->id=content;
		aux->left = aux->right = NULL;
		aux->height = 1;
		aux->node =n;
		*a = aux;
	}
}

void print(Avl **a,int nombre){
	if(*a == NULL){
		return;
	}
	print(&((*a)->right),nombre+1);
	if(nombre!=0){
		int i;
		for(i=0;i<nombre-1;i++){
			printf("|\t");
		}
		printf("|-------%d\n",(*a)->node->id);
	}
	else{
		printf("%d\n",(*a)->node->id);
	}
	print(&((*a)->left),nombre+1);
}

int main(){
	Avl *a = NULL;
	init(&a, 4);
	int tab[10] = {0,6,9,10,14,1,8,7,15,16};
	int i;
	for(i=0;i<10;i++){
		printf("%d ",tab[i]);
	}
	printf("\n");
	for(i=0;i<10;i++){
		insert(&a, tab[i]);
		print(&a,0);
		puts("\n-----------------------\n");
	}
	int key = 2;
	Node * n = search(a,key);
	if(n!=NULL){
		printf("Node id : %d is find \n",n->id);
	}
	else{
		printf("Node id : %d is not find \n",key);
	}

	return 0;
}
