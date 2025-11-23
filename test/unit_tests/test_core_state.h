/*
 * test_core_state.h
 *
 *  Created on: Nov 2, 2025
 *      Author: Arlen Feng
 */

#ifndef TEST_CORE_STATE_H_
#define TEST_CORE_STATE_H_

#include <stdbool.h>
#include "test_core.h"
#include "core_state.h"

/*** Test Struct Definitions ***/

typedef struct test_case_is_valid_instruction_address{
	uint16_t input;
	bool expected_output;
} test_case_is_valid_instruction_address;

typedef struct test_case_load_program_instructions{
	size_t bin_data_size;
	instruction_load_status expected_status;
} test_case_load_program_instructions;

typedef struct test_case_get_instruction_at_pc{
	uint16_t current_pc;
	bool expect_invalid_instr;
} test_case_get_instruction_at_pc;

/*** Public Global Static Data ***/

static const test_case_is_valid_instruction_address test_cases_is_valid_instruction_address[] = {
	{.input = 0x0000, .expected_output = false},
	{.input = MEMORY_PROGRAM_INSTRUCTIONS_START - 2, .expected_output = false},
	{.input = MEMORY_PROGRAM_INSTRUCTIONS_START, .expected_output = true},
	{.input = MEMORY_PROGRAM_INSTRUCTIONS_START + 1, .expected_output = false},
	{.input = 0x07B0, .expected_output = true},
	{.input = MEMORY_RESERVED_VARIABLES_START - 2, .expected_output = true},
	{.input = MEMORY_RESERVED_VARIABLES_START - 1, .expected_output = false},
	{.input = MEMORY_RESERVED_VARIABLES_START, .expected_output = false},
	{.input = 0xFFFF, .expected_output = false}
};

static const test_case_load_program_instructions test_cases_load_program_instructions[] = {
		{.bin_data_size = MEMORY_RESERVED_VARIABLES_START - MEMORY_PROGRAM_INSTRUCTIONS_START + 1, .expected_status = MEMORY_OVERFLOW_FAULT},
		{.bin_data_size = 0, .expected_status = NULL_POINTER_FAULT},
		{.bin_data_size = 0x200, .expected_status = INSTR_LOAD_SUCCESS}
};

static const test_case_get_instruction_at_pc test_cases_get_instruction_at_pc[] = {
		{.current_pc = MEMORY_PROGRAM_INSTRUCTIONS_START - 2, .expect_invalid_instr = true},
		{.current_pc = MEMORY_PROGRAM_INSTRUCTIONS_START, .expect_invalid_instr = false},
		{.current_pc = MEMORY_RESERVED_VARIABLES_START, .expect_invalid_instr = true},
		{.current_pc = MEMORY_PROGRAM_INSTRUCTIONS_START + 0xB3, .expect_invalid_instr = true}
};

/*** Public Function Declarations ***/

test_details test_initialize_state();

test_details test_is_valid_instruction_address();

/**
 * @Precondition: REQUIRES srand() to be called before function call!
 * Recommendation: srand() should be called to seed the pseudo-random number generator at unit test program start.
 */
test_details test_load_program_instructions();

test_details test_get_instruction_at_pc();

#endif /* TEST_CORE_STATE_H_ */
