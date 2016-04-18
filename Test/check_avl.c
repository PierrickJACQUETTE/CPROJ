#include "check_avl.h"

Avl *avlNode;
Avl *avlWay;

void setup(void){
	Node *n = initNode(1,1.0,2.0,"true",NULL);
	init(&avlNode,n, NULL);
	Way *w = initWay(1,"true",NULL,NULL,1,"test");
	init(&avlWay ,NULL, w);
}

void teardown(void){
	deleteAvl(&avlNode,1);
	deleteAvl(&avlWay,0);
}

START_TEST(initAvlNode){
	Avl *aNode = NULL;
	Bounds *b = initBounds(1.0,2.0,2.0,2.0);
	Node *n = initNode(1,1.0,2.0,"true",b);
	init(&aNode ,n, NULL);
	ck_assert_ptr_eq(aNode->node,n);
	ck_assert_ptr_eq(aNode->left,NULL);
	ck_assert_ptr_eq(aNode->right,NULL);
	ck_assert_ptr_eq(aNode->way,NULL);
	ck_assert_int_eq(aNode->height,1);
	ck_assert_ptr_ne(aNode,NULL);
	deleteAvl(&aNode,1);
}END_TEST

START_TEST(initAvlNodeNULL){
	Avl *aNode = NULL;
	Node *n = initNode(1,1.0,2.0,"true",NULL);
	init(&aNode ,n, NULL);
	ck_assert_ptr_eq(aNode->node,n);
	ck_assert_ptr_eq(aNode->left,NULL);
	ck_assert_ptr_eq(aNode->right,NULL);
	ck_assert_ptr_eq(aNode->way,NULL);
	ck_assert_int_eq(aNode->height,1);
	ck_assert_ptr_ne(aNode,NULL);
	deleteAvl(&aNode,1);
}END_TEST

START_TEST(initAvlWay){
	Avl* avlWay =NULL;
	Color *c = malloc(sizeof(Color));
	c->red = c->blue = c->green = 0;
	Tag * t = initTag("key","value",c,1,1,2);
	ListNode * ln = initListNode(0);
	Way *w = initWay(1,"true",ln,t,1,"test");
	init(&avlWay ,NULL, w);
	ck_assert_ptr_eq(avlWay->node,NULL);
	ck_assert_ptr_eq(avlWay->left,NULL);
	ck_assert_ptr_eq(avlWay->right,NULL);
	ck_assert_ptr_eq(avlWay->way,w);
	ck_assert_int_eq(avlWay->height,1);
	ck_assert_ptr_ne(avlWay,NULL);
	deleteAvl(&avlWay,0);
}END_TEST

START_TEST(initAvlWayNULL){
	Avl* avlWay =NULL;
	Way *w = initWay(1,"true",NULL,NULL,1,"test");
	init(&avlWay ,NULL, w);
	ck_assert_ptr_eq(avlWay->node,NULL);
	ck_assert_ptr_eq(avlWay->left,NULL);
	ck_assert_ptr_eq(avlWay->right,NULL);
	ck_assert_ptr_eq(avlWay->way,w);
	ck_assert_int_eq(avlWay->height,1);
	ck_assert_ptr_ne(avlWay,NULL);
	deleteAvl(&avlWay,0);
}END_TEST

START_TEST(initAvlNodeNULLWayNULL){
	Avl* avlWay =NULL;
	ck_assert_msg(init(&avlWay ,NULL, NULL)==NULL, "Check Avl init Erreur type avl non reconnue");
	deleteAvl(&avlWay,0);
}END_TEST

START_TEST(insertAvl){
	//ck_assert_int_eq(egalite(5) , 1 );
}END_TEST

START_TEST(searchNodeAvl){
	//ck_assert_int_eq(egalite(5) , 1 );
}END_TEST

START_TEST(searchWayAvl){
	//ck_assert_int_eq(egalite(5) , 1 );
}END_TEST

Suite* init_suiteAvl(void){
	Suite* s= suite_create("avl");
	TCase *tc= tcase_create("StandardAvl");
	tcase_add_checked_fixture(tc, setup,teardown);
	tcase_add_test(tc, initAvlNode);
	tcase_add_test(tc, initAvlWay);
	tcase_add_test(tc, insertAvl);
	tcase_add_test(tc, searchNodeAvl);
	tcase_add_test(tc, searchWayAvl);
	suite_add_tcase(s , tc) ;

	TCase *tc_limits = tcase_create("LimitsAvl") ;
	tcase_add_test(tc_limits,initAvlNodeNULL);
	tcase_add_test(tc_limits,initAvlWayNULL);
	tcase_add_test (tc_limits,initAvlNodeNULLWayNULL) ;
	suite_add_tcase (s , tc_limits) ;
	return s;
}
