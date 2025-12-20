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
	const test_function test_functions[] = {
			test_initialize_state,
			test_is_valid_instruction_address,
			test_load_program_instructions,
			test_get_instruction_at_pc,
			test_increment_pc,
			test_set_pc,
			test_push_pc_value_on_stack,
			test_pop_value_from_stack_to_pc,
			test_set_v_register,
			test_get_v_register,
			test_set_vf_to_flag_value,
			test_set_index_register,
			test_get_index_register
	};
	const int num_tests = sizeof(test_functions) / sizeof(test_function);
	run_tests(test_functions, num_tests);
	return 0;
}
