#include "check_init.h"

START_TEST(InitNode){
	Bounds *bo = initBounds(1.0,2.0,2.0,2.0);
	Node *nd = initNode(1,1.0,2.0,"true",bo);
	ck_assert_uint_eq(nd->id,1);
	ck_assert_uint_eq(nd->c->x, 0);
	ck_assert_uint_eq(nd->c->y,0);
	ck_assert_str_eq(nd->visible,"T");
	deleteBounds(bo);
	deleteNode(nd);
}END_TEST

START_TEST(InitNode_limits){
	Bounds *bo = initBounds(0.0,1.0,0.0,1.0);
	Node *nd = initNode(1,0.0,1.0,"true",bo);
	ck_assert_uint_ne(nd->c->y, 1);
	nd= initNode(1,-1.0,-1.0,"",bo);
	ck_assert((nd->c->y)<0);
	ck_assert_str_eq(nd->visible,"T");
	nd= initNode(1,-1.0,-1.0,"",NULL);
	ck_assert_ptr_eq(nd,NULL);
	nd= initNode(-1,1.0,1.0,"",bo);
	ck_assert_ptr_eq(nd,NULL);
	nd= initNode(1,100.0,1.0,"",bo);
	ck_assert_ptr_eq(nd,NULL);
	deleteBounds(bo);
	deleteNode(nd);
}END_TEST


START_TEST(InitBounds){
	Bounds *bo = initBounds(1.0,2.0,2.0,2.0);
	ck_assert_uint_eq(bo->min->x, 2.0);
	ck_assert_uint_eq(bo->max->x,2.0);
	ck_assert_uint_eq(bo->min->y, 1.0);
	ck_assert_uint_eq(bo->max->y,2.0);
	deleteBounds(bo);
}END_TEST

START_TEST(InitBounds_limits){
	Bounds *bo = initBounds(100.0,2.0,2.0,2.0);
	ck_assert_ptr_eq(bo,NULL);
	bo= initBounds(1.0,100.0,2.0,2.0);
	ck_assert_ptr_eq(bo,NULL);
	deleteBounds(bo);
}END_TEST

START_TEST(InitWay){
	Way *w = initWay(1,"true", NULL, NULL, 1, "name");
	ck_assert_uint_eq(w->id, 1);
	ck_assert_str_eq(w->visible,"T");
	ck_assert_ptr_eq(w->listNd, NULL);
	ck_assert_ptr_eq(w->tag,NULL);
	ck_assert_int_eq(w->size, 1);
	ck_assert_str_eq(w->name,"name");
	deleteWay(w);
}END_TEST

START_TEST(InitWay_limits){
	Way *w = initWay(-1,"true", NULL, NULL, 1, "name");
	ck_assert_ptr_eq(w, NULL);
	w= initWay(1," ", NULL, NULL, 1, "name");
	ck_assert_str_eq(w->visible,"T");
	deleteWay(w);
}END_TEST

START_TEST(InitTag){
	Color *c=malloc(sizeof(Color));	
	Tag* t = initTag("key","value", c, 0, 0, 1); 
	ck_assert_str_eq(t->tagKey, "key");
	ck_assert_str_eq(t->tagValue,"value");
	ck_assert_ptr_eq(t->c,c);
	ck_assert_int_eq(t->type,0);
	ck_assert_int_eq(t->thick, 0);
	ck_assert_int_eq(t->priority,1);
	deleteTag(t);
}END_TEST

START_TEST(InitTag_limits){
	Tag* t = initTag("key","value", NULL, 0, 0, 1); 
	ck_assert_ptr_eq(t, NULL);
	deleteTag(t);
}END_TEST

START_TEST(InitRelation){
	Relation* r = initRelation(1, "true", NULL, NULL, NULL); 
	ck_assert_uint_eq(r->id, 1);
	ck_assert_str_eq(r->visible,"T");
	ck_assert_ptr_eq(r->listW, NULL);
	ck_assert_ptr_eq(r->listN, NULL);
	ck_assert_ptr_eq(r->tag, NULL);
	deleteRelation(r);
}END_TEST

<<<<<<< HEAD
=======
START_TEST(InitRelation_limits){
	Relation* r = initRelation(1, " ", NULL, NULL, NULL); 
	ck_assert_str_eq(r->visible,"T");
	r= initRelation(-1, " ", NULL, NULL, NULL); 
	ck_assert_ptr_eq(r, NULL);
	deleteRelation(r);
}END_TEST




>>>>>>> origin/master
Suite* init_suite(void){
	Suite* s= suite_create("ini");
	TCase *tc= tcase_create("standar"); 

	tcase_add_test(tc, InitNode);
	tcase_add_test(tc, InitBounds);
	tcase_add_test(tc, InitWay);
	tcase_add_test(tc, InitTag);
	tcase_add_test(tc, InitRelation);

	TCase* tc_limits = tcase_create ("Limits" ) ;
	tcase_add_test(tc_limits, InitNode_limits);
	tcase_add_test(tc_limits, InitBounds_limits);
	tcase_add_test(tc_limits, InitWay_limits);
	tcase_add_test(tc_limits, InitTag_limits);
	tcase_add_test(tc_limits, InitRelation_limits);

	suite_add_tcase( s , tc ) ;
	suite_add_tcase ( s , tc_limits ) ;
	return s;
}


