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
	deleteAvl(&avlWay,10);
}

START_TEST(initAvlNode){
	Avl *aNode = NULL;
	Node *n = initNode(1,1.0,2.0,"true",NULL);
	init(&aNode ,n, NULL);
	ck_assert_ptr_eq(aNode->node,n);
	ck_assert_ptr_eq(aNode->left,NULL);
	ck_assert_ptr_eq(aNode->right,NULL);
	ck_assert_ptr_eq(aNode->way,NULL);
	ck_assert_int_eq(aNode->height,1);
	deleteAvl(&aNode,1);
}END_TEST

START_TEST(initAvlWay){
	Avl* avlWay =NULL;
	Way *w = initWay(1,"true",NULL,NULL,1,"test");
	init(&avlWay ,NULL, w);
	ck_assert_ptr_eq(avlWay->node,NULL);
	ck_assert_ptr_eq(avlWay->left,NULL);
	ck_assert_ptr_eq(avlWay->right,NULL);
	ck_assert_ptr_eq(avlWay->way,w);
	ck_assert_int_eq(avlWay->height,1);
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
	TCase *tc= tcase_create("avl");
	tcase_add_checked_fixture(tc, setup,teardown);
	tcase_add_test(tc, initAvlNode);
	tcase_add_test(tc, initAvlWay);
	tcase_add_test(tc, insertAvl);
	tcase_add_test(tc, searchNodeAvl);
	tcase_add_test(tc, searchWayAvl);
	suite_add_tcase(s , tc) ;

	//t c _ l i m i t s = tcase_create (" Limits " ) ;
	//tcase_add_test ( t c _ l i m i t s , test_money_create_neg ) ;
	//tcase_add_test ( t c _ l i m i t s , test_money_create_zero ) ;
	//suite_add_tcase ( s , t c _ l i m i t s ) ;
	return s;
}
