#include "check_init.h"
#include "check_avl.h"


int main(){
 	int number_failed;
	Suite * s=init_suite();
	SRunner *sr= srunner_create(s);
  srunner_add_suite(sr,init_suiteAvl());
	srunner_run_all(sr, CK_VERBOSE);
	number_failed=srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed==0) ? EXIT_SUCCESS: EXIT_FAILURE;
}
