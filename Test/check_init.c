#include "check_init.h"

Node* n;
Way* w;
Relation *r;
Bounds *b;
Tag* t;

void setupI(void){
	n = initNode(1,1.0,2.0,"true",NULL);
	w = initWay(1,"true",NULL,NULL,1,"test");
	b = initBounds(0,1,0,1);
	t= initTag("key", "value", NULL, 1, 1, 1);
	r=initRelation(1,"true",NULL, NULL, NULL);
	
}

void teardownI(void){
	deleteNode(n);
	deleteWay(w);
	deleteBounds(b);
	deleteTag(t);
	deleteRelation(r);
}


START_TEST(InitNode){
	//Bounds *bo = initBounds(1.0,2.0,2.0,2.0);
	Node *nd = initNode(1,1.0,2.0,"true",NULL);
	//ck_assert_uint_eq(nd->id,1);
	//ck_assert_uint_eq(nd->c->x, 0);
	//ck_assert_uint_eq(nd->c->y,0);
	deleteNode(nd);
}END_TEST


Suite* init_suite(void){
	Suite* s= suite_create("ini");
	TCase *tc= tcase_create("standar"); 
	tcase_add_checked_fixture(tc, setupI,teardownI);

	tcase_add_test(tc, nitNode);
	TCase* tc_limits = tcase_create ("Limits" ) ;
	//tcase_add_test ( t c _ l i m i t s , test_money_create_neg ) ;
	//tcase_add_test ( t c _ l i m i t s , test_money_create_zero ) ;
	suite_add_tcase ( s , tc ) ;
	suite_add_tcase ( s , tc_limits ) ;
	return s;
}


