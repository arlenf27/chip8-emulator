/*
 * core_state.h
 *
 *  Created on: Oct 10, 2025
 *      Author: Arlen Feng
 */

#ifndef CORE_STATE_H_
#define CORE_STATE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

/*** Core Memory Definitions ***/

#define MEMORY_SIZE 0x1000
#define MEMORY_RESERVED_INTERPRETER_START 0x00
#define MEMORY_PROGRAM_INSTRUCTIONS_START 0x0200
#define MEMORY_RESERVED_VARIABLES_START 0x0EA0
#define MEMORY_RESERVED_DISPLAY_START 0x0F00

/*** Stack Definitions ***/

#define STACK_SIZE 0x10

/*** Data (V) Registers Definitions ***/

#define NUM_V_REGISTERS 0x10

/*** Display Definitions ***/

#define NUM_DISPLAY_ROWS 0x20
#define PIXEL_OFF 0x00
#define PIXEL_ON 0x01
typedef uint64_t display_row;

/*** Sound Definitions ***/

#define SOUND_OFF 0x00
#define SOUND_ON 0x02

/*** Status Definitions ***/

typedef enum instruction_load_status{
	INSTR_LOAD_SUCCESS,
	MEMORY_OVERFLOW_FAULT,
	NULL_POINTER_FAULT
} instruction_load_status;

typedef enum stack_result{
	STACK_SUCCESS,
	STACK_OVERFLOW,
	STACK_UNDERFLOW
} stack_result;

typedef enum generic_result{
	SUCCESS,
	FAILURE
} generic_result;

typedef enum vf_flag_value{
	VF_NO_CARRY = 0x00,
	VF_BORROW_OCCURS = 0x00,
	VF_NO_SET_PIXELS_CHANGED_TO_UNSET = 0x00,
	VF_LEAST_SIG_BIT_ZERO = 0x00,
	VF_MOST_SIG_BIT_ZERO = 0x00,
	VF_CARRY_OCCURS = 0x01,
	VF_NO_BORROW = 0x01,
	VF_ANY_SET_PIXELS_CHANGED_TO_UNSET = 0x01,
	VF_LEAST_SIG_BIT_ONE = 0x01,
	VF_MOST_SIG_BIT_ONE = 0x01,
} vf_flag_value;

/*** Struct Declarations ***/

/**
 * Core State of Emulator
 * Contains core memory, stack, registers
 */
typedef struct core_state core_state;

/*** Public Function Declarations ***/

bool is_valid_instruction_address(uint16_t memory_address);

core_state* initialize_state();

/**
 * @Precondition: state must have been dynamically allocated with malloc, calloc, realloc,
 * or a similar allocation function.
 */
void delete_state(core_state* state);

/**
 * @Precondition: 2-byte instructions MUST be valid instructions.
 * @Precondition: 2-byte instructions in bin_data are stored in big-endian.
 */
instruction_load_status load_program_instructions(core_state* state, uint8_t* bin_data, size_t bin_data_size);

uint16_t get_instruction_at_pc(core_state* state);

generic_result increment_pc(core_state* state);

generic_result set_pc(core_state* state, uint16_t memory_address);

stack_result push_pc_value_on_stack(core_state* state);

stack_result pop_value_from_stack_to_pc(core_state* state);

generic_result set_v_register(core_state* state, uint8_t v_reg, uint8_t value);

generic_result get_v_register(core_state* state, uint8_t v_reg, uint8_t* result);

generic_result set_vf_to_flag_value(core_state* state, vf_flag_value value);

generic_result set_index_register(core_state* state, uint16_t memory_address);

generic_result get_index_register(core_state* state, uint16_t* result);

#endif /* CORE_STATE_H_ */
