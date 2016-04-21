#include "check_avl.h"

Avl *avlNode;
Avl *avlWay;

START_TEST(initAvlNode){
	Avl *aNode = NULL;
	Bounds *b = initBounds(1.0,2.0,2.0,2.0);
	Node *n = initNode(1,1.0,2.0,"true",b, "name");
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

START_TEST(initAvlNodeNULLWayNULL){
	Avl* avlWay =NULL;
	ck_assert_msg(init(&avlWay ,NULL, NULL)==NULL, "Check Avl init Erreur type avl non reconnue");
	deleteAvl(&avlWay,0);
}END_TEST

START_TEST(initAvlNodeNOTNULLWayNOTNULL){
	Avl* avl =NULL;
	Bounds *bo = initBounds(1.0,2.0,2.0,2.0);
	Way *w = initWay(1,"true",NULL,NULL,1,"test");
	Node *n = initNode(1,1.0,2.0,"true",bo, "name");
	ck_assert_msg(init(&avl,n, w)==NULL, "Check Avl init Erreur 2 types avl");
	deleteBounds(bo);
	deleteAvl(&avlWay,0);
}END_TEST

START_TEST(initAvlNOTNULL){
	Avl* avl =NULL;
	Bounds *bo = initBounds(1.0,2.0,2.0,2.0);
	Node *n = initNode(1,1.0,2.0,"true",bo, "name");
	init(&avl,n, NULL);
	Node *n2 = initNode(12,1.0,2.0,"true",bo, "name");
	ck_assert_msg(init(&avl,n2, NULL)==NULL,"Il y a deja des elements dans l'avl, appeler la methode insert");
	deleteBounds(bo);
	deleteAvl(&avlWay,0);
}END_TEST

START_TEST(insertAvlNode){
	Avl *aNode = NULL;
	Bounds *bo = initBounds(1.0,2.0,2.0,2.0);
	Node *n = initNode(2,1.0,2.0,"true",bo, "name");
	init(&aNode ,n, NULL);

	Node *n2 = initNode(3,1.0,2.0,"true",bo, "name");
	insert(&aNode,n2,NULL);
	ck_assert_ptr_eq(aNode->right->node,n2);
	n2 = initNode(1,1.0,2.0,"true",bo, "name");
	insert(&aNode,n2,NULL);
	ck_assert_ptr_eq(aNode->left->node,n2);
	n2 = initNode(4,1.0,2.0,"true",bo, "name");
	insert(&aNode,n2,NULL);
	ck_assert_ptr_eq(aNode->right->right->node,n2);
	deleteBounds(bo);
	deleteAvl(&aNode,1);
}END_TEST

START_TEST(insertAvlNodeReq){
	Avl *aNode = NULL;
	Bounds *bo = initBounds(1.0,2.0,2.0,2.0);
	Node *n = initNode(2,1.0,2.0,"true",bo, "name");
	init(&aNode ,n, NULL);
	Node *n2 = initNode(3,1.0,2.0,"true",bo, "name");
	insert(&aNode,n2,NULL);
	ck_assert_ptr_eq(aNode->right->node,n2);
	n2 = initNode(1,1.0,2.0,"true",bo, "name");
	insert(&aNode,n2,NULL);
	ck_assert_ptr_eq(aNode->left->node,n2);
	n2 = initNode(4,1.0,2.0,"true",bo, "name");
	insert(&aNode,n2,NULL);

	ck_assert_ptr_eq(aNode->right->right->node,n2);
	n2 = initNode(5,1.0,2.0,"true",bo, "name");
	insert(&aNode,n2,NULL);

	ck_assert_ptr_eq(aNode->right->right->node,n2);
	ck_assert_uint_eq(aNode->right->node->id,4);
	ck_assert_uint_eq(aNode->right->left->node->id,3);
	n2 = initNode(6,1.0,2.0,"true",bo, "name");
	insert(&aNode,n2,NULL);
	ck_assert_ptr_eq(aNode->right->right->node,n2);
	ck_assert_uint_eq(aNode->left->left->node->id,1);
	ck_assert_uint_eq(aNode->left->node->id,2);
	ck_assert_uint_eq(aNode->left->right->node->id,3);
	ck_assert_uint_eq(aNode->node->id,4);
	ck_assert_uint_eq(aNode->right->node->id,5);
	deleteBounds(bo);
	deleteAvl(&aNode,1);
}END_TEST

START_TEST(insertAvlNodeIdYes){
	Bounds *bo = initBounds(1.0,2.0,2.0,2.0);
	Avl *aNode = NULL;
	Node *n = initNode(2,1.0,2.0,"true",bo, "name");
	init(&aNode ,n, NULL);

	Node *n2 = initNode(3,1.0,2.0,"true",bo, "name");
	insert(&aNode,n2,NULL);
	ck_assert_ptr_eq(aNode->right->node,n2);
	n2 = initNode(3,1.0,2.0,"true",bo, "name");
	if(insert(&aNode,n2,NULL) == NULL){
		ck_assert_uint_eq(aNode->right->node->id,n2->id);
		ck_abort_msg("Insertion impossible car il existe deja ce noeud dans l'avl");
	}
	deleteBounds(bo);
	deleteAvl(&aNode,1);
}END_TEST

START_TEST(insertAvlWay){
	Avl *aWay = NULL;
	Way *w = initWay(2,"true",NULL,NULL,1,"test");
	init(&aWay, NULL, w);

	Way *w2 = initWay(3,"true",NULL,NULL,1,"test");
	insert(&aWay, NULL, w2);
	ck_assert_ptr_eq(aWay->right->way,w2);
	w2 = initWay(1,"true",NULL,NULL,1,"test");
	insert(&aWay, NULL, w2);
	ck_assert_ptr_eq(aWay->left->way,w2);
	w2 = initWay(4,"true",NULL,NULL,1,"test");
	insert(&aWay, NULL, w2);
	ck_assert_ptr_eq(aWay->right->right->way,w2);
	deleteAvl(&aWay,0);
}END_TEST

START_TEST(insertAvlWayReq){
	Avl *aWay = NULL;
	Way *w = initWay(2,"true",NULL,NULL,1,"test");
	init(&aWay, NULL, w);

	Way *w2 = initWay(3,"true",NULL,NULL,1,"test");
	insert(&aWay, NULL, w2);
	ck_assert_ptr_eq(aWay->right->way,w2);
	w2 = initWay(1,"true",NULL,NULL,1,"test");
	insert(&aWay, NULL, w2);
	ck_assert_ptr_eq(aWay->left->way,w2);
	w2 = initWay(4,"true",NULL,NULL,1,"test");
	insert(&aWay, NULL, w2);
	ck_assert_ptr_eq(aWay->right->right->way,w2);

	w2 = initWay(5,"true",NULL,NULL,1,"test");
	insert(&aWay, NULL, w2);
	ck_assert_ptr_eq(aWay->right->right->way,w2);
	ck_assert_uint_eq(aWay->right->way->id,4);
	ck_assert_uint_eq(aWay->right->left->way->id,3);
	w2 = initWay(6,"true",NULL,NULL,1,"test");
	insert(&aWay, NULL, w2);
	ck_assert_ptr_eq(aWay->right->right->way,w2);
	ck_assert_uint_eq(aWay->left->left->way->id,1);
	ck_assert_uint_eq(aWay->left->way->id,2);
	ck_assert_uint_eq(aWay->left->right->way->id,3);
	ck_assert_uint_eq(aWay->way->id,4);
	ck_assert_uint_eq(aWay->right->way->id,5);
	deleteAvl(&aWay,0);
}END_TEST

START_TEST(insertAvlWayIdYes){
	Avl *aWay = NULL;
	Way *w = initWay(2,"true",NULL,NULL,1,"test");
	init(&aWay, NULL, w);

	Way *w2 = initWay(3,"true",NULL,NULL,1,"test");
	insert(&aWay, NULL, w2);
	ck_assert_ptr_eq(aWay->right->way,w2);
	w2 = initWay(3,"true",NULL,NULL,1,"test");
	if(insert(&aWay, NULL, w2) == NULL){
		ck_assert_uint_eq(aWay->right->node->id,w2->id);
		ck_abort_msg("Insertion impossible car il existe deja ce noeud dans l'avl");
	}
	deleteAvl(&aWay,0);
}END_TEST


START_TEST(insertAvlNodeNULLWayNULL){
	Avl* avlWay =NULL;
	ck_assert_msg(insert(&avlWay ,NULL, NULL)==NULL, "Check Avl insert Erreur type avl non reconnue");
	deleteAvl(&avlWay,0);
}END_TEST

START_TEST(insertAvlNodeNOTNULLWayNOTNULL){
	Avl* avl =NULL;
	Bounds *bo = initBounds(1.0,2.0,2.0,2.0);
	Way *w = initWay(1,"true",NULL,NULL,1,"test");
	Node *n = initNode(1,1.0,2.0,"true",bo, "name");
	ck_assert_msg(insert(&avl,n, w)==NULL, "Check Avl insert Erreur 2 type avl");
	deleteAvl(&avlWay,0);
	deleteBounds(bo);
}END_TEST

START_TEST(insertAvlNULL){
	Avl* avl =NULL;
	Bounds *bo = initBounds(1.0,2.0,2.0,2.0);
	Node *n = initNode(1,1.0,2.0,"true",bo, "name");
	avl = insert(&avl,n, NULL);
	ck_assert_msg(avl->height == 1,"Il y a deja des elements dans l'avl, appeler la methode init");
	deleteAvl(&avlWay,1);
	deleteBounds(bo);
}END_TEST

START_TEST(searchNodeAvlYes){
	Avl *aNode = NULL;
	Bounds *bo = initBounds(1.0,2.0,2.0,2.0);
	Node *n = initNode(2,1.0,2.0,"true",bo, "name");
	init(&aNode ,n, NULL);

	Node *n2 = initNode(1,1.0,2.0,"true",bo,"name");
	insert(&aNode,n2,NULL);
	ck_assert_ptr_eq(aNode->left->node,n2);
	n2 = initNode(3,1.0,2.0,"true",bo,"name");
	insert(&aNode,n2,NULL);
	ck_assert_ptr_eq(aNode->right->node,n2);
	ck_assert_ptr_eq(searchNode(aNode,3),n2);
	ck_assert_ptr_ne(searchNode(aNode,3),NULL);
	deleteBounds(bo);
	deleteAvl(&aNode,1);
}END_TEST

START_TEST(searchNodeAvlNo){
	Avl *aNode = NULL;
	Bounds *bo = initBounds(1.0,2.0,2.0,2.0);
	Node *n = initNode(2,1.0,2.0,"true",bo,"name");
	init(&aNode ,n, NULL);

	Node *n2 = initNode(1,1.0,2.0,"true",bo, "name");
	insert(&aNode,n2,NULL);
	ck_assert_ptr_eq(aNode->left->node,n2);
	Node *n3 = initNode(3,1.0,2.0,"true",bo, "name");
	insert(&aNode,n3,NULL);
	ck_assert_ptr_eq(aNode->right->node,n3);
	ck_assert_ptr_ne(searchNode(aNode,5),n3);
	ck_assert_ptr_ne(searchNode(aNode,5),n2);
	ck_assert_ptr_ne(searchNode(aNode,5),n);
	ck_assert_ptr_eq(searchNode(aNode,5),NULL);
	deleteBounds(bo);
	deleteAvl(&aNode,1);
}END_TEST

START_TEST(searchNodeAvlNULL){
	Avl* avl =NULL;
	Bounds *bo = initBounds(1.0,2.0,2.0,2.0);
	Node *n = initNode(1,1.0,2.0,"true",bo, "name");
	if(searchNode(avl,n->id) != NULL){
		ck_abort_msg("L'avl est vide");
	}
	deleteBounds(bo);
	deleteAvl(&avlWay,1);
}END_TEST

START_TEST(searchWayAvlYes){
	Avl *aWay = NULL;
	Way *w = initWay(2,"true",NULL,NULL,1,"test");
	init(&aWay, NULL, w);

	Way *w2 = initWay(1,"true",NULL,NULL,1,"test");
	insert(&aWay, NULL, w2);
	ck_assert_ptr_eq(aWay->left->way,w2);
	w2 = initWay(3,"true",NULL,NULL,1,"test");
	insert(&aWay, NULL, w2);
	ck_assert_ptr_eq(aWay->right->way, w2);
	ck_assert_ptr_eq(searchWay(aWay,3), w2);
	ck_assert_ptr_ne(searchWay(aWay,3), NULL);
	deleteAvl(&aWay,0);
}END_TEST

START_TEST(searchWayAvlNo){
	Avl *aWay = NULL;
	Way *w = initWay(2,"true",NULL,NULL,1,"test");
	init(&aWay, NULL, w);

	Way *w2 = initWay(1,"true",NULL,NULL,1,"test");
	insert(&aWay, NULL, w2);
	ck_assert_ptr_eq(aWay->left->way,w2);
	Way * w3 = initWay(3,"true",NULL,NULL,1,"test");
	insert(&aWay, NULL, w3);
	ck_assert_ptr_eq(aWay->right->way, w3);
	ck_assert_ptr_ne(searchWay(aWay,5),w3);
	ck_assert_ptr_ne(searchWay(aWay,5),w2);
	ck_assert_ptr_ne(searchWay(aWay,5),w);
	ck_assert_ptr_eq(searchWay(aWay,5),NULL);
	deleteAvl(&aWay,0);
}END_TEST

START_TEST(searchWayAvlNULL){
	Avl* avl =NULL;
	Way *w = initWay(2,"true",NULL,NULL,1,"test");
	if(searchWay(avl,w->id) != NULL){
		ck_abort_msg("L'avl est vide");
	}
	deleteAvl(&avlWay,0);
}END_TEST

Suite* init_suiteAvl(void){
	Suite* s= suite_create("avl");
	TCase *tc= tcase_create("StandardAvl");
	//tcase_add_checked_fixture(tc, setup,teardown);
	tcase_add_test(tc, initAvlNode);
	tcase_add_test(tc, initAvlWay);
	tcase_add_test(tc, insertAvlNode);
	tcase_add_test(tc, insertAvlNodeReq);
	tcase_add_test(tc, insertAvlWay);
	tcase_add_test(tc, insertAvlWayReq);
	tcase_add_test(tc, searchNodeAvlYes);
	tcase_add_test(tc, searchWayAvlYes);
	suite_add_tcase(s , tc) ;

	TCase *tc_limits = tcase_create("LimitsAvl");
	tcase_add_test(tc_limits, initAvlNodeNULLWayNULL);
	tcase_add_test(tc_limits, initAvlNodeNOTNULLWayNOTNULL);
	tcase_add_test(tc_limits, initAvlNOTNULL);
	tcase_add_test(tc_limits, insertAvlNodeIdYes);
	tcase_add_test(tc_limits, insertAvlWayIdYes);
	tcase_add_test(tc_limits, insertAvlNodeNULLWayNULL);
	tcase_add_test(tc_limits, insertAvlNodeNOTNULLWayNOTNULL);
	tcase_add_test(tc_limits, insertAvlNULL);
	tcase_add_test(tc_limits, searchNodeAvlNo);
	tcase_add_test(tc_limits, searchNodeAvlNULL);
	tcase_add_test(tc_limits, searchWayAvlNo);
	tcase_add_test(tc_limits, searchWayAvlNULL);
	suite_add_tcase (s , tc_limits) ;
	return s;
}
