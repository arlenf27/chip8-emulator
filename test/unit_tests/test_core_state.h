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

/*** Public Function Declarations ***/

test_details test_initialize_state();

test_details test_is_valid_instruction_address();

#endif /* TEST_CORE_STATE_H_ */
