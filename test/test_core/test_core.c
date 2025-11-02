/*
 * test_core.c
 *
 *  Created on: Nov 2, 2025
 *      Author: Arlen Feng
 */

#include "test_core.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/*** Public Functions ***/

void run_tests(const test_function tests[], size_t num_tests){
	int tests_passed = 0;

	for(int i = 0; i < (int) num_tests; i++){
		test_details details = tests[i]();
		if(details.passed){
			printf("Test \"%s\" PASSED, %d sub-checks PASSED. \n", details.name, details.sub_checks_passed);
			tests_passed++;
		}else{
			printf("Test \"%s\" FAILED, %d sub-checks PASSED, %d sub-checks FAILED. \n", details.name, details.sub_checks_passed, details.sub_checks_failed);
		}
	}

	printf("\n");
	printf("Unit Test Summary: %d tests PASSED, %d total tests. \n", tests_passed, (int) num_tests);
}
