/*
 * main.c
 *
 *  Created on: Nov 2, 2025
 *      Author: Arlen Feng
 */

#include <stdlib.h>
#include <time.h>
#include "test_core.h"
#include "test_core_state.h"

int main(int argc, char* argv[]){
	srand(time(NULL));
	const test_function test_functions[] = {test_initialize_state, test_is_valid_instruction_address, test_load_program_instructions};
	const int num_tests = sizeof(test_functions) / sizeof(test_function);
	run_tests(test_functions, num_tests);
	return 0;
}
