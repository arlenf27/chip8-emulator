/*
 * core_state.c
 *
 *  Created on: Oct 10, 2025
 *      Author: Arlen Feng
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "core_state.h"
#include "instructions.h"
#include "core_state_internal.h"

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
		state->index_register = MEMORY_SIZE;
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

instruction_load_status load_program_instructions(core_state* state, uint8_t* bin_data, size_t bin_data_size){
	if(bin_data == NULL) return NULL_POINTER_FAULT;
	int i = MEMORY_PROGRAM_INSTRUCTIONS_START;
	for(; i < MEMORY_RESERVED_VARIABLES_START && i - MEMORY_PROGRAM_INSTRUCTIONS_START < bin_data_size; i++){
		state->memory[i] = *bin_data;
		bin_data++;
	}
	if(i == MEMORY_RESERVED_VARIABLES_START && i - MEMORY_PROGRAM_INSTRUCTIONS_START < bin_data_size){
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

stack_result push_pc_value_on_stack(core_state* state){
	if(state->sp >= STACK_SIZE) return STACK_OVERFLOW;
	state->stack[state->sp] = state->pc;
	state->sp++;
	return STACK_SUCCESS;
}

stack_result pop_value_from_stack_to_pc(core_state* state){
	if(state->sp <= 0) return STACK_UNDERFLOW;
	state->sp--;
	state->pc = state->stack[state->sp];
	return STACK_SUCCESS;
}

generic_result set_v_register(core_state* state, uint8_t v_reg, uint8_t value){
	if(v_reg >= NUM_V_REGISTERS) return FAILURE;
	state->v_registers[v_reg] = value;
	return SUCCESS;
}

generic_result get_v_register(core_state* state, uint8_t v_reg, uint8_t* result){
	if(v_reg >= NUM_V_REGISTERS) return FAILURE;
	*result = state->v_registers[v_reg];
	return SUCCESS;
}

generic_result set_vf_to_flag_value(core_state* state, vf_flag_value value){
	if(value < 0 || value > 1) return FAILURE;
	state->v_registers[0x0F] = (uint8_t) value;
	return SUCCESS;
}

generic_result set_index_register(core_state* state, uint16_t memory_address){
	if(memory_address >= MEMORY_SIZE) return FAILURE;
	state->index_register = memory_address;
	return SUCCESS;
}

generic_result get_index_register(core_state* state, uint16_t* result){
	if(state->index_register >= MEMORY_SIZE) return FAILURE;
	*result = state->index_register;
	return SUCCESS;
}
