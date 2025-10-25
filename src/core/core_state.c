/*
 * memory.c
 *
 *  Created on: Oct 10, 2025
 *      Author: Arlen Feng
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "core_state.h"
#include "instructions.h"

/** Data Definitions */

struct core_state{
	uint8_t memory[MEMORY_SIZE];
	uint8_t stack[STACK_SIZE];
	uint8_t v_registers[NUM_V_REGISTERS];
	uint16_t pc;
	uint16_t index_register;
	uint8_t sp;
	uint8_t dt;
	uint8_t st;
	display_row display[NUM_DISPLAY_ROWS];
};

/*** Public Functions ***/

bool is_valid_instruction_address(uint16_t memory_address){
	if(memory_address % 2 != 0 ||
		memory_address < MEMORY_PROGRAM_INSTRUCTIONS_START ||
		memory_address >= MEMORY_RESERVED_VARIABLES_START){
		return false;
	}
	return true;
}

core_state* initialize_state(){
	core_state* state = (core_state*) malloc(sizeof(core_state));
	if(state != NULL){
		for(size_t i = 0; i < MEMORY_SIZE; i++){
			state->memory[i] = 0xFF;
		}
		for(size_t i = 0; i < STACK_SIZE; i++){
			state->stack[i] = 0;
		}
		for(size_t i = 0; i < NUM_V_REGISTERS; i++){
			state->v_registers[i] = 0;
		}
		state->pc = MEMORY_PROGRAM_INSTRUCTIONS_START;
		state->index_register = 0;
		state->sp = 0;
		state->dt = 0;
		state->st = SOUND_OFF;
		for(size_t i = 0; i < NUM_DISPLAY_ROWS; i++){
			state->display[i] = (display_row) PIXEL_OFF;
		}
	}
	return state;
}

void delete_state(core_state* state){
	free(state);
}

instruction_load_status load_program_instructions(core_state* state, uint8_t* bin_data){
	if(bin_data == NULL) return NULL_POINTER_FAULT;
	int i = MEMORY_PROGRAM_INSTRUCTIONS_START;
	for(; i < MEMORY_RESERVED_VARIABLES_START && *bin_data != '\0'; i++){
		state->memory[i] = *bin_data;
		bin_data++;
	}
	if(i == MEMORY_RESERVED_VARIABLES_START && *bin_data != '\0'){
		return MEMORY_OVERFLOW_FAULT;
	}else{
		return INSTR_LOAD_SUCCESS;
	}
}

uint16_t get_instruction_at_pc(core_state* state){
	uint16_t instr = INVALID_INSTR;
	uint16_t memory_address = state->pc;
	if(is_valid_instruction_address(memory_address)){
		instr = state->memory[memory_address] << 8;
		instr |= state->memory[memory_address+1];
	}
	return instr;
}

generic_result increment_pc(core_state* state){
	generic_result res = FAILURE;
	if(is_valid_instruction_address(state->pc + 2)){
		state->pc += 2;
		res = SUCCESS;
	}
	return res;
}

generic_result set_pc(core_state* state, uint16_t memory_address){
	generic_result res = FAILURE;
	if(is_valid_instruction_address(memory_address)){
		state->pc = memory_address;
		res = SUCCESS;
	}
	return res;
}
