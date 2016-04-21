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

START_TEST(DistanceLatLon){
	ck_assert_uint_eq(distanceLatLon(2.3, 2.5, 2, 2.4),35.16);
}END_TEST

START_TEST(ConvertBounds){
	Bounds *bo = initBounds(2.3,2.5,2.2, 2.4);
	bo=convertBounds(bo);	
	ck_assert_uint_eq(bo->min->y,0);
	ck_assert_uint_eq(bo->min->x,0);
	ck_assert_uint_eq(bo->max->y,22.239);
	ck_assert_uint_eq(bo->max->x,22.221);	
}END_TEST



Suite* convert_suite(void){
	Suite* s= suite_create("convert");
	TCase *tc= tcase_create("convert");

	tcase_add_test(tc, DistanceXY);
	tcase_add_test(tc, DistanceY);
	tcase_add_test(tc, DistanceX);
	tcase_add_test(tc, DistanceLatLon);
	tcase_add_test(tc, ConvertBounds);

	suite_add_tcase(s, tc);
	return s;
}
