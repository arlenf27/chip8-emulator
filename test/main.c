/*
 * main.c
 *
 *  Created on: Nov 2, 2025
 *      Author: Arlen Feng
 */

#include "test_core.h"
#include "test_core_state.h"

#define NUM_TESTS 1

int main(int argc, char* argv[]){
	const test_function test_functions[] = {test_initialize_state};
	run_tests(test_functions, NUM_TESTS);
	return 0;
}
