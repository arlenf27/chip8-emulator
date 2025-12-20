/*
 * instructions.c
 *
 *  Created on: Nov 8, 2025
 *      Author: Arlen Feng
 */

#include <stdbool.h>
#include <stdlib.h>
#include "instructions.h"
#include "core_state.h"

/*** Private Definitions ***/

typedef struct hex_digits{
	unsigned int hex0: 4;
	unsigned int hex1: 4;
	unsigned int hex2: 4;
	unsigned int hex3: 4;
} hex_digits;

/*** Private Function Declarations ***/

bool go_to_next_instruction(core_state* state, const char** increment_message);

void execute_subroutine(core_state* state, uint16_t subroutine_address, bool* success, const char** custom_message);

void return_from_subroutine(core_state* state, bool* success, const char** custom_message);

void jump(core_state* state, uint16_t address, bool* success, const char** custom_message);

void skip_if_value_vx_equals_nn(core_state* state, uint8_t nn, uint8_t v_reg, bool* success, const char** custom_message);

void skip_if_value_vx_not_equals_nn(core_state* state, uint8_t nn, uint8_t v_reg, bool* success, const char** custom_message);

void skip_if_value_vx_equals_value_vy(core_state* state, uint8_t v_reg_x, uint8_t v_reg_y, bool* success, const char** custom_message);

void store_nn_in_vx(core_state* state, uint8_t nn, uint8_t v_reg, bool* success, const char** custom_message);

/*** Public Functions ***/

instruction_result execute_instruction(uint16_t instruction, core_state* state){
	instruction_result result = {.type = INVALID_INSTRUCTION_TYPE, .success = false, .custom_message = ""};
	hex_digits digits = {0, 0, 0, 0};
	digits.hex0 = (unsigned int) (instruction) & 0xF;
	digits.hex1 = (unsigned int) (instruction >> 4) & 0xF;
	digits.hex2 = (unsigned int) (instruction >> 8) & 0xF;
	digits.hex3 = (unsigned int) (instruction >> 12) & 0xF;
	uint16_t lower_3_hex_digits = instruction & 0x0FFF;
	uint8_t lower_2_hex_digits = (uint8_t) (instruction & 0x00FF);
	switch(digits.hex3)
	{
		case 0x0:
		{
			switch(lower_3_hex_digits)
			{
				case 0x0E0:
				{
					result.type = CLEAR_SCREEN;
					/* TODO: Handle CLEAR_SCREEN */
					break;
				}
				case 0x0EE:
				{
					result.type = RETURN_FROM_SUBROUTINE;
					return_from_subroutine(state, &result.success, &result.custom_message);
					break;
				}
				default:
				{
					result.type = EXECUTE_MACHINE_LANGUAGE_SUBROUTINE;
					/* TODO: Handle EXECUTE_MACHINE_LANGUAGE_SUBROUTINE */
					break;
				}
			}
			break;
		}
		case 0x1:
		{
			result.type = JUMP;
			jump(state, lower_3_hex_digits, &result.success, &result.custom_message);
			break;
		}
		case 0x2:
		{
			result.type = EXECUTE_SUBROUTINE;
			execute_subroutine(state, lower_3_hex_digits, &result.success, &result.custom_message);
			break;
		}
		case 0x3:
		{
			result.type = SKIP_IF_VALUE_VX_EQUALS_NN;
			skip_if_value_vx_equals_nn(state, lower_2_hex_digits, (uint8_t) digits.hex2, &result.success, &result.custom_message);
			break;
		}
		case 0x4:
		{
			result.type = SKIP_IF_VALUE_VX_NOT_EQUALS_NN;
			skip_if_value_vx_not_equals_nn(state, lower_2_hex_digits, (uint8_t) digits.hex2, &result.success, &result.custom_message);
			break;
		}
		case 0x5:
		{
			if(digits.hex0 == 0x0){
				result.type = SKIP_IF_VALUE_VX_EQUALS_VALUE_VY;
				skip_if_value_vx_equals_value_vy(state, (uint8_t) digits.hex2, (uint8_t) digits.hex1, &result.success, &result.custom_message);
			}else{
				result.type = INVALID_INSTRUCTION_TYPE;
				/* TODO: Handle INVALID_INSTRUCTION_TYPE */
			}
			break;
		}
		case 0x6:
		{
			result.type = STORE_NN_IN_VX;
			store_nn_in_vx(state, lower_2_hex_digits, (uint8_t) digits.hex2, &result.success, &result.custom_message);
			break;
		}
		case 0x7:
		{
			result.type = ADD_NN_TO_VX;
			/* TODO: Handle ADD_NN_TO_VX */
			break;
		}
		case 0x8:
		{
			switch(digits.hex0)
			{
				case 0x0:
				{
					result.type = STORE_VALUE_VY_IN_VX;
					/* TODO: Handle STORE_VALUE_VY_IN_VX */
					break;
				}
				case 0x1:
				{
					result.type = SET_VX_TO_VX_OR_VY;
					/* TODO: Handle SET_VX_TO_VX_OR_VY */
					break;
				}
				case 0x2:
				{
					result.type = SET_VX_TO_VX_AND_VY;
					/* TODO: Handle SET_VX_TO_VX_AND_VY */
					break;
				}
				case 0x3:
				{
					result.type = SET_VX_TO_VX_XOR_VY;
					/* TODO: Handle SET_VX_TO_VX_XOR_VY */
					break;
				}
				case 0x4:
				{
					result.type = ADD_VALUE_VY_TO_VX;
					/* TODO: Handle ADD_VALUE_VY_TO_VX */
					break;
				}
				case 0x5:
				{
					result.type = SUBTRACT_VALUE_VY_FROM_VX;
					/* TODO: Handle SUBTRACT_VALUE_VY_FROM_VX */
					break;
				}
				case 0x6:
				{
					result.type = STORE_VALUE_VY_SHIFTED_RIGHT_ONE_BIT_TO_VX;
					/* TODO: Handle STORE_VALUE_VY_SHIFTED_RIGHT_ONE_BIT_TO_VX */
					break;
				}
				case 0x7:
				{
					result.type = SET_VX_TO_VALUE_VY_MINUX_VX;
					/* TODO: Handle SET_VX_TO_VALUE_VY_MINUX_VX */
					break;
				}
				case 0xE:
				{
					result.type = STORE_VALUE_VY_SHIFTED_LEFT_ONE_BIT_TO_VX;
					/* TODO: Handle STORE_VALUE_VY_SHIFTED_LEFT_ONE_BIT_TO_VX */
					break;
				}
				default:
				{
					result.type = INVALID_INSTRUCTION_TYPE;
					/* TODO: Handle INVALID_INSTRUCTION_TYPE */
					break;
				}
			}
			break;
		}
		case 0x9:
		{
			result.type = SKIP_IF_VALUE_VX_NOT_EQUAL_TO_VALUE_VY;
			/* TODO: Handle SKIP_IF_VALUE_VX_NOT_EQUAL_TO_VALUE_VY */
			break;
		}
		case 0xA:
		{
			result.type = STORE_NNN_IN_REGISTER_I;
			/* TODO: Handle STORE_NNN_IN_REGISTER_I */
			break;
		}
		case 0xB:
		{
			result.type = JUMP_TO_ADDRESS_NNN_PLUS_V0;
			/* TODO: Handle JUMP_TO_ADDRESS_NNN_PLUS_V0 */
			break;
		}
		case 0xC:
		{
			result.type = SET_VX_TO_RANDOM_NUMBER_WITH_MASK_OF_NN;
			/* TODO: Handle SET_VX_TO_RANDOM_NUMBER_WITH_MASK_OF_NN */
			break;
		}
		case 0xD:
		{
			result.type = DRAW_SPRITE;
			/* TODO: Handle DRAW_SPRITE */
			break;
		}
		case 0xE:
		{
			switch(lower_2_hex_digits)
			{
				case 0x9E:
				{
					result.type = SKIP_IF_KEY_STORED_IN_VX_PRESSED;
					/* TODO: Handle SKIP_IF_KEY_STORED_IN_VX_PRESSED */
					break;
				}
				case 0xA1:
				{
					result.type = SKIP_IF_KEY_STORED_IN_VX_NOT_PRESSED;
					/* TODO: Handle SKIP_IF_KEY_STORED_IN_VX_NOT_PRESSED */
					break;
				}
				default:
				{
					result.type = INVALID_INSTRUCTION_TYPE;
					/* TODO: Handle INVALID_INSTRUCTION_TYPE */
					break;
				}
			}
			break;
		}
		case 0xF:
		{
			switch(lower_2_hex_digits)
			{
				case 0x07:
				{
					result.type = STORE_VALUE_DELAY_TIMER_IN_VX;
					/* TODO: Handle STORE_VALUE_DELAY_TIMER_IN_VX */
					break;
				}
				case 0x0A:
				{
					result.type = WAIT_FOR_KEY_PRESS;
					/* TODO: Handle WAIT_FOR_KEY_PRESS */
					break;
				}
				case 0x15:
				{
					result.type = SET_DELAY_TIMER_TO_VALUE_VX;
					/* TODO: Handle SET_DELAY_TIMER_TO_VALUE_VX */
					break;
				}
				case 0x18:
				{
					result.type = SET_SOUND_TIMER_TO_VALUE_VX;
					/* TODO: Handle SET_SOUND_TIMER_TO_VALUE_VX */
					break;
				}
				case 0x1E:
				{
					result.type = ADD_VALUE_VX_TO_REGISTER_I;
					/* TODO: Handle ADD_VALUE_VX_TO_REGISTER_I */
					break;
				}
				case 0x29:
				{
					result.type = SET_I_TO_MEMORY_ADDRESS_OF_SPRITE_DATA;
					/* TODO: Handle SET_I_TO_MEMORY_ADDRESS_OF_SPRITE_DATA */
					break;
				}
				case 0x33:
				{
					result.type = STORE_BINARY_CODED_DECIMAL_EQUIVALENT;
					/* TODO: Handle STORE_BINARY_CODED_DECIMAL_EQUIVALENT */
					break;
				}
				case 0x55:
				{
					result.type = STORE_VALUES_V0_VX;
					/* TODO: Handle STORE_VALUES_V0_VX */
					break;
				}
				case 0x65:
				{
					result.type = FILL_REGISTERS_V0_VX;
					/* TODO: Handle FILL_REGISTERS_V0_VX */
					break;
				}
				default:
				{
					result.type = INVALID_INSTRUCTION_TYPE;
					/* TODO: Handle INVALID_INSTRUCTION_TYPE */
					break;
				}
			}
			break;
		}
		default:
		{
			result.type = INVALID_INSTRUCTION_TYPE;
			/* TODO: Handle INVALID_INSTRUCTION_TYPE */
			break;
		}
	}
	return result;
}

/*** Private Functions ***/

bool go_to_next_instruction(core_state* state, const char** increment_message){
	bool res = false;
	if(increment_pc(state) == SUCCESS){
		res = true;
	}else{
		*increment_message = "Unable to increment pc. \n";
	}
	return res;
}

void execute_subroutine(core_state* state, uint16_t subroutine_address, bool* success, const char** custom_message){
	if(push_pc_value_on_stack(state) != STACK_OVERFLOW){
		if(set_pc(state, subroutine_address) == SUCCESS){
			*custom_message = "";
			*success = true;
		}else{
			*custom_message = "Setting pc failed, invalid memory address. \n";
			*success = false;
		}
	}else{
		*custom_message = "Stack overflow while pushing pc value onto stack, too many nested subroutines. \n";
		*success = false;
	}
}

void return_from_subroutine(core_state* state, bool* success, const char** custom_message){
	if(pop_value_from_stack_to_pc(state) != STACK_UNDERFLOW){
		*custom_message = "";
		*success = go_to_next_instruction(state, custom_message);
	}else{
		*custom_message = "Stack underflow while pushing pc value onto stack, no pc value stored. \n";
		*success = false;
	}
}

void jump(core_state* state, uint16_t address, bool* success, const char** custom_message){
	if(set_pc(state, address) == SUCCESS){
		*custom_message = "";
		*success = true;
	}else{
		*custom_message = "Setting pc failed, invalid memory address. \n";
		*success = false;
	}
}

void skip_if_value_vx_equals_nn(core_state* state, uint8_t nn, uint8_t v_reg, bool* success, const char** custom_message){
	uint8_t to_compare = 0;
	if(get_v_register(state, v_reg, &to_compare) == SUCCESS){
		if(to_compare == nn){
			*custom_message = "Value VX equals NN, skipping. \n";
			*success = go_to_next_instruction(state, custom_message);
		}else{
			*custom_message = "Value VX not equals NN, not skipping. \n";
			*success = true;
		}
		if(*success){
			*success = go_to_next_instruction(state, custom_message);
		}
	}else{
		*custom_message = "Getting value of register failed, invalid register. \n";
		*success = false;
	}
}

void skip_if_value_vx_not_equals_nn(core_state* state, uint8_t nn, uint8_t v_reg, bool* success, const char** custom_message){
	uint8_t to_compare = 0;
	if(get_v_register(state, v_reg, &to_compare) == SUCCESS){
		if(to_compare != nn){
			*custom_message = "Value VX not equals NN, skipping. \n";
			*success = go_to_next_instruction(state, custom_message);
		}else{
			*custom_message = "Value VX equals NN, not skipping. \n";
			*success = true;
		}
		if(*success){
			*success = go_to_next_instruction(state, custom_message);
		}
	}else{
		*custom_message = "Getting value of register failed, invalid register. \n";
		*success = false;
	}
}

void skip_if_value_vx_equals_value_vy(core_state* state, uint8_t v_reg_x, uint8_t v_reg_y, bool* success, const char** custom_message){
	uint8_t value_vx = 0, value_vy = 0;
	if((get_v_register(state, v_reg_x, &value_vx) == SUCCESS) && (get_v_register(state, v_reg_y, &value_vy) == SUCCESS)){
		if(value_vx == value_vy){
			*custom_message = "Value VX equals value VY, skipping. \n";
			*success = go_to_next_instruction(state, custom_message);
		}else{
			*custom_message = "Value VX not equals value VY, not skipping. \n";
			*success = true;
		}
		if(*success){
			*success = go_to_next_instruction(state, custom_message);
		}
	}else{
		*custom_message = "Getting value of register(s) failed, invalid register(s). \n";
		*success = false;
	}
}

void store_nn_in_vx(core_state* state, uint8_t nn, uint8_t v_reg, bool* success, const char** custom_message){
	if(set_v_register(state, v_reg, nn) == SUCCESS){
		*custom_message = "";
		*success = go_to_next_instruction(state, custom_message);
	}else{
		*custom_message = "Setting value of register failed, invalid register. \n";
		*success = false;
	}
}
