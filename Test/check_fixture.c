#include "check_fixture.h"

Node* n;
Way* w;
Relation *r;
Bounds *b;
Tag* t;
Color *c;
Avl *avlNode;
Avl *avlWay;
ListNode * ln;
ListWay *lw;
ListRelation *lr;

void setup(void){
	n = initNode(1,1.0,2.0,"true",NULL, "name");
	w = initWay(1,"true",NULL,NULL,1,"test");
	b = initBounds(0,1,0,1);
	t= initTag("key", "value", NULL, 1, 1, 1);
	r=initRelation(1,"true",NULL, NULL, NULL);
	c=malloc(sizeof(Color));
	c->red= 255; 	c->green= 255; 	c->blue= 255;
	init(&avlNode,n, NULL);
	init(&avlWay ,NULL, w);
	initListNode(1);
	initListWay(1);
	initListRelation(initRelation(1,"true",NULL, NULL, NULL));
}

void teardown(void){
	deleteNode(n);
	deleteWay(w);
	deleteBounds(b);
	deleteTag(t);
	deleteRelation(r);
	deleteColor(c);
	deleteAvl(&avlNode,1);
	deleteAvl(&avlWay,0);
	deleteListNode(ln);
	deleteListWay(lw);
	deleteListRelation(lr);	
}

Suite* fix_suite(void){
	Suite* s= suite_create("fix");
	TCase *tc= tcase_create("fix");
	tcase_add_checked_fixture(tc, setup,teardown);
	suite_add_tcase( s , tc ) ;
	return s;
}
