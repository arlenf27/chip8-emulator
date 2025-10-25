/*
 * main.c
 *
 *  Created on: Oct 4, 2025
 *      Author: Arlen Feng
 */

#include <stdio.h>
#include <stdlib.h>
#include "core_state.h"
#include "instructions.h"

int main(int argc, char *argv[]) {
	/* Test/Debug Code */
	core_state* test_state = initialize_state();
	if(test_state == NULL){
		exit(EXIT_FAILURE);
	}
	uint8_t* test_data = (uint8_t*) malloc(sizeof(uint8_t) * 5);
	if(test_data == NULL){
		exit(EXIT_FAILURE);
	}
	test_data[0] = 0x4E;
	test_data[1] = 0x05;
	test_data[2] = 0xFF;
	test_data[3] = 0xA0;
	test_data[4] = '\0';
	if(load_program_instructions(test_state, test_data) == INSTR_LOAD_SUCCESS){
		uint16_t instr = get_instruction_at_pc(test_state);
		while(instr != INVALID_INSTR){
			printf("0x%X\n", instr);
			if(increment_pc(test_state) == FAILURE){
				break;
			}
			instr = get_instruction_at_pc(test_state);
		}
	}else{
		printf("Load Fault");
	}
	free(test_data);
	delete_state(test_state);
	return 0;
}

