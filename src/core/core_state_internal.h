/*
 * core_state_internal.h
 *
 *  Created on: Nov 2, 2025
 *      Author: Arlen Feng
 */

#ifndef CORE_STATE_INTERNAL_H_
#define CORE_STATE_INTERNAL_H_

#include "core_state.h"

/** Data Definitions */

struct core_state{
	uint8_t memory[MEMORY_SIZE];
	uint16_t stack[STACK_SIZE];
	uint8_t v_registers[NUM_V_REGISTERS];
	uint16_t pc;
	uint16_t index_register;
	uint8_t sp;
	uint8_t dt;
	uint8_t st;
	display_row display[NUM_DISPLAY_ROWS];
};

#endif /* CORE_STATE_INTERNAL_H_ */
