/*
 * test_core_state.c
 *
 *  Created on: Nov 2, 2025
 *      Author: Arlen Feng
 */

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "test_core.h"
#include "core_state.h"

/*** Public Functions ***/

test_details test_initialize_state(){
	test_details details = {.name = (char*) __func__, .passed = true, .sub_checks_passed = 0, .sub_checks_failed = 0};
	const core_state* test_state = initialize_state();
	if(test_state != NULL){
		for(int i = 0; i < MEMORY_SIZE; i++){
			const uint8_t actual_memory_byte = test_state->memory[i];
			const uint8_t expected_memory_byte = 0xFF;
			if(EXPR_EQUAL(actual_memory_byte, expected_memory_byte)){
				details.sub_checks_passed++;
			}else{
				fprintf(stderr, "Expected core state's memory byte %d to be %d, but was %d instead. Failed at %s:%d. \n", i, expected_memory_byte, actual_memory_byte, __FILE__, __LINE__);
				details.sub_checks_failed++;
				details.passed = false;
			}
		}
		for(int i = 0; i < STACK_SIZE; i++){
			const uint16_t actual_data = test_state->stack[i];
			const uint16_t expected_data = 0;
			if(EXPR_EQUAL(actual_data, expected_data)){
				details.sub_checks_passed++;
			}else{
				fprintf(stderr, "Expected core state's stack entry %d to be %d, but was %d instead. Failed at %s:%d. \n", i, expected_data, actual_data, __FILE__, __LINE__);
				details.sub_checks_failed++;
				details.passed = false;
			}
		}
		for(int i = 0; i < NUM_V_REGISTERS; i++){
			const uint8_t actual_data = test_state->v_registers[i];
			const uint8_t expected_data = 0;
			if(EXPR_EQUAL(actual_data, expected_data)){
				details.sub_checks_passed++;
			}else{
				fprintf(stderr, "Expected core state's register %d to be %d, but was %d instead. Failed at %s:%d. \n", i, expected_data, actual_data, __FILE__, __LINE__);
				details.sub_checks_failed++;
				details.passed = false;
			}
		}
		const uint16_t actual_pc = test_state->pc;
		if(EXPR_EQUAL(actual_pc, MEMORY_PROGRAM_INSTRUCTIONS_START)){
			details.sub_checks_passed++;
		}else{
			fprintf(stderr, "Core state's pc expected to start at %d, but started at %d instead. Failed at %s:%d. \n", MEMORY_PROGRAM_INSTRUCTIONS_START, actual_pc, __FILE__, __LINE__);
			details.sub_checks_failed++;
			details.passed = false;
		}
		const uint16_t actual_index_register = test_state->index_register;
		if(EXPR_EQUAL(actual_index_register, MEMORY_SIZE)){
			details.sub_checks_passed++;
		}else{
			fprintf(stderr, "Core state's index register expected to start at %d, but started at %d instead. Failed at %s:%d. \n", MEMORY_SIZE, actual_index_register, __FILE__, __LINE__);
			details.sub_checks_failed++;
			details.passed = false;
		}
		const uint8_t actual_sp = test_state->sp;
		const uint8_t expected_sp = 0;
		if(EXPR_EQUAL(actual_sp, expected_sp)){
			details.sub_checks_passed++;
		}else{
			fprintf(stderr, "Core state's sp expected to start at %d, but started at %d instead. Failed at %s:%d. \n", expected_sp, actual_sp, __FILE__, __LINE__);
			details.sub_checks_failed++;
			details.passed = false;
		}
		const uint8_t actual_dt = test_state->dt;
		const uint8_t expected_dt = 0;
		if(EXPR_EQUAL(actual_dt, expected_dt)){
			details.sub_checks_passed++;
		}else{
			fprintf(stderr, "Core state's dt expected to start at %d, but started at %d instead. Failed at %s:%d. \n", expected_dt, actual_dt, __FILE__, __LINE__);
			details.sub_checks_failed++;
			details.passed = false;
		}
		const uint8_t actual_st = test_state->st;
		if(EXPR_EQUAL(actual_st, SOUND_OFF)){
			details.sub_checks_passed++;
		}else{
			fprintf(stderr, "Core state's st expected to start at %d, but started at %d instead. Failed at %s:%d. \n", SOUND_OFF, actual_st, __FILE__, __LINE__);
			details.sub_checks_failed++;
			details.passed = false;
		}
		for(int i = 0; i < NUM_DISPLAY_ROWS; i++){
			const display_row actual_display_row = test_state->display[i];
			const display_row expected_display_row = (display_row) PIXEL_OFF;
			if(EXPR_EQUAL(actual_display_row, expected_display_row)){
				details.sub_checks_passed++;
			}else{
				fprintf(stderr, "Expected core state's display row %d's integer representation of pixels to be %llX, but was %llX instead. Failed at %s:%d. \n", i, expected_display_row, actual_display_row, __FILE__, __LINE__);
				details.sub_checks_failed++;
				details.passed = false;
			}
		}
	}
	delete_state((core_state*) test_state);
	return details;
}
