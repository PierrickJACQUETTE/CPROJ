#include "check_conversionElements.h"

START_TEST(DistanceXY){
	ck_assert_uint_eq(distanceXY(1., 1., 4., 5.),5);
}END_TEST

START_TEST(DistanceY){
	ck_assert_uint_eq(distanceY(1.,3.),2);
}END_TEST

START_TEST(DistanceX){
	ck_assert_uint_eq(distanceX(1.,3.),2);
}END_TEST

Suite* convert_suite(void){
	Suite* s= suite_create("convert");
	TCase *tc= tcase_create("convert"); 

	tcase_add_test(tc, DistanceXY);
	tcase_add_test(tc, DistanceY);
	tcase_add_test(tc, DistanceX);
	
	suite_add_tcase(s, tc);
	return s;
}
