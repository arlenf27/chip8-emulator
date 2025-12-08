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
#include "test_core_state.h"
#include "core_state.h"
#include "instructions.h"

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
				fprintf(stderr, "Expected core state's display row %d's integer representation of pixels to be %lX, but was %lX instead. Failed at %s:%d. \n", i, expected_display_row, actual_display_row, __FILE__, __LINE__);
				details.sub_checks_failed++;
				details.passed = false;
			}
		}
	}
	delete_state((core_state*) test_state);
	return details;
}

test_details test_is_valid_instruction_address(){
	test_details details = {.name = (char*) __func__, .passed = true, .sub_checks_passed = 0, .sub_checks_failed = 0};
	for(size_t i = 0; i < sizeof(test_cases_is_valid_instruction_address) / sizeof(test_case_is_valid_instruction_address); i++){
		const test_case_is_valid_instruction_address* current = &test_cases_is_valid_instruction_address[i];
		bool actual_output = is_valid_instruction_address(current->input);
		if(EXPR_EQUAL(actual_output, current->expected_output)){
			details.sub_checks_passed++;
		}else{
			fprintf(stderr, "Expected %d, but was %d instead. Failed at %s:%d. \n", current->expected_output, actual_output, __FILE__, __LINE__);
			details.sub_checks_failed++;
			details.passed = false;
		}
	}
	return details;
}

test_details test_load_program_instructions(){
	test_details details = {.name = (char*) __func__, .passed = true, .sub_checks_passed = 0, .sub_checks_failed = 0};
	for(size_t i = 0; i < sizeof(test_cases_load_program_instructions) / sizeof(test_case_load_program_instructions); i++){
		core_state* test_state = (core_state*) malloc(sizeof(core_state));
		if(test_state != NULL){
			const test_case_load_program_instructions* current = &test_cases_load_program_instructions[i];
			uint8_t* bin_data;
			if(current->bin_data_size != 0){
				bin_data = (uint8_t*) malloc(sizeof(uint8_t) * current->bin_data_size);
			}else{
				/* Testing NULL input with 0 length. */
				bin_data = NULL;
			}
			if(bin_data != NULL){
				for(int j = 0; j < current->bin_data_size; j++){
					bin_data[j] = (rand() % (0xFF + 0x01));
				}
				for(size_t j = 0; j < MEMORY_SIZE; j++){
					test_state->memory[j] = 0xFF;
				}
				instruction_load_status actual_status = load_program_instructions(test_state, bin_data, current->bin_data_size);
				for(int j = 0; j < current->bin_data_size && j < (MEMORY_RESERVED_VARIABLES_START - MEMORY_PROGRAM_INSTRUCTIONS_START); j++){
					const uint8_t actual_data = test_state->memory[j + MEMORY_PROGRAM_INSTRUCTIONS_START];
					const uint8_t expected_data = bin_data[j];
					if(EXPR_EQUAL(actual_data, expected_data)){
						details.sub_checks_passed++;
					}else{
						fprintf(stderr, "Expected core state's memory byte %d to be %d, but was %d instead. Failed at %s:%d. \n", j, expected_data, actual_data, __FILE__, __LINE__);
						details.sub_checks_failed++;
						details.passed = false;
					}
				}
				if(EXPR_EQUAL(actual_status, current->expected_status)){
					details.sub_checks_passed++;
				}else{
					fprintf(stderr, "Expected status enumeration %d, but was %d instead. Failed at %s:%d. \n", current->expected_status, actual_status, __FILE__, __LINE__);
					details.sub_checks_failed++;
					details.passed = false;
				}
			}
			free(bin_data);
		}
		free(test_state);
	}
	return details;
}

test_details test_get_instruction_at_pc(){
	test_details details = {.name = (char*) __func__, .passed = true, .sub_checks_passed = 0, .sub_checks_failed = 0};
	for(size_t i = 0; i < sizeof(test_cases_get_instruction_at_pc) / sizeof(test_case_get_instruction_at_pc); i++){
		core_state* test_state = (core_state*) malloc(sizeof(core_state));
		if(test_state != NULL){
			for(size_t j = 0; j < MEMORY_SIZE; j++){
				test_state->memory[j] = 0x5A;
			}
			const test_case_get_instruction_at_pc* current = &test_cases_get_instruction_at_pc[i];
			test_state->pc = current->current_pc;
			uint16_t actual_instr = get_instruction_at_pc(test_state);
			if(current->expect_invalid_instr){
				if(EXPR_EQUAL(actual_instr, GENERIC_INVALID_INSTR)){
					details.sub_checks_passed++;
				}else{
					fprintf(stderr, "Expected %d, but was %d instead. Failed at %s:%d. \n", GENERIC_INVALID_INSTR, actual_instr, __FILE__, __LINE__);
					details.sub_checks_failed++;
					details.passed = false;
				}
			}else{
				if(EXPR_EQUAL(actual_instr, 0x5A5A)){
					details.sub_checks_passed++;
				}else{
					fprintf(stderr, "Expected %d, but was %d instead. Failed at %s:%d. \n", 0x5A5A, actual_instr, __FILE__, __LINE__);
					details.sub_checks_failed++;
					details.passed = false;
				}
			}
		}
		free(test_state);
	}
	return details;
}

test_details test_increment_pc(){
	test_details details = {.name = (char*) __func__, .passed = true, .sub_checks_passed = 0, .sub_checks_failed = 0};
	for(size_t i = 0; i < sizeof(test_cases_increment_pc) / sizeof(test_case_increment_pc); i++){
		core_state* test_state = (core_state*) malloc(sizeof(core_state));
		if(test_state != NULL){
			const test_case_increment_pc* current = &test_cases_increment_pc[i];
			test_state->pc = current->current_pc;
			generic_result actual_res = increment_pc(test_state);
			if(EXPR_EQUAL(actual_res, current->expected_result)){
				details.sub_checks_passed++;
			}else{
				fprintf(stderr, "Expected %d, but was %d instead. Failed at %s:%d. \n", current->expected_result, actual_res, __FILE__, __LINE__);
				details.sub_checks_failed++;
				details.passed = false;
			}
			if(current->expected_result == SUCCESS){
				if(EXPR_EQUAL(test_state->pc, current->current_pc + 2)){
					details.sub_checks_passed++;
				}else{
					fprintf(stderr, "Expected new pc to be %d, but was %d instead. Failed at %s:%d. \n", current->current_pc + 2, test_state->pc, __FILE__, __LINE__);
					details.sub_checks_failed++;
					details.passed = false;
				}
			}
		}
		free(test_state);
	}
	return details;
}

test_details test_set_pc(){
	test_details details = {.name = (char*) __func__, .passed = true, .sub_checks_passed = 0, .sub_checks_failed = 0};
	for(size_t i = 0; i < sizeof(test_cases_set_pc) / sizeof(test_case_set_pc); i++){
		core_state* test_state = (core_state*) malloc(sizeof(core_state));
		if(test_state != NULL){
			const test_case_set_pc* current = &test_cases_set_pc[i];
			test_state->pc = MEMORY_PROGRAM_INSTRUCTIONS_START;
			generic_result actual_res = set_pc(test_state, current->memory_address);
			if(EXPR_EQUAL(actual_res, current->expected_result)){
				details.sub_checks_passed++;
			}else{
				fprintf(stderr, "Expected %d, but was %d instead. Failed at %s:%d. \n", current->expected_result, actual_res, __FILE__, __LINE__);
				details.sub_checks_failed++;
				details.passed = false;
			}
			if(current->expected_result == SUCCESS){
				if(EXPR_EQUAL(test_state->pc, current->memory_address)){
					details.sub_checks_passed++;
				}else{
					fprintf(stderr, "Expected new pc to be %d, but was %d instead. Failed at %s:%d. \n", current->memory_address, test_state->pc, __FILE__, __LINE__);
					details.sub_checks_failed++;
					details.passed = false;
				}
			}
		}
		free(test_state);
	}
	return details;
}
