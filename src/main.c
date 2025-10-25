/*
 * main.c
 *
 *  Created on: Oct 4, 2025
 *      Author: Arlen Feng
 */

#include <stdio.h>
#include <stdlib.h>
#include "core_state.h"

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
	test_data[2] = 0x34;
	test_data[3] = 0xA0;
	test_data[4] = '\0';
	if(load_program_instructions(test_state, test_data) == INSTR_LOAD_SUCCESS){
		printf("Getting instruction at 0x202: 0x%X", get_instruction(test_state, 0x202));
	}else{
		printf("Load Fault");
	}
	free(test_data);
	delete_state(test_state);
	return 0;
}

