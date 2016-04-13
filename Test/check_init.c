#include "check_init.h"


START_TEST(test_ega){
	ck_assert_int_eq(egalite(5) , 1 );
}END_TEST


Suite* init_suite(void){
	Suite* s= suite_create("init");
	TCase *tc= tcase_create("init"); 
	//tcase_add_checked_fixture(tc, cree struct, free struct);

	tcase_add_test(tc, test_ega);
	//t c _ l i m i t s = tcase_create (" Limits " ) ;
	//tcase_add_test ( t c _ l i m i t s , test_money_create_neg ) ;
	//tcase_add_test ( t c _ l i m i t s , test_money_create_zero ) ;
	suite_add_tcase ( s , tc ) ;
	//suite_add_tcase ( s , t c _ l i m i t s ) ;
	return s;
}


