/*
 * memory.h
 *
 *  Created on: Oct 10, 2025
 *      Author: Arlen Feng
 */

#include <stdint.h>
#include <stdbool.h>

#ifndef CORE_STATE_H_
#define CORE_STATE_H_

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

typedef enum generic_result{
	SUCCESS,
	FAILURE
} generic_result;

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
 * @Precondition: bin_data is NULL-terminated.
 */
instruction_load_status load_program_instructions(core_state* state, uint8_t* bin_data);

uint16_t get_instruction_at_pc(core_state* state);

generic_result increment_pc(core_state* state);

generic_result set_pc(core_state* state, uint16_t memory_address);

#endif /* CORE_STATE_H_ */
