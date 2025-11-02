/*
 * test_core.h
 *
 *  Created on: Nov 2, 2025
 *      Author: Arlen Feng
 */

#ifndef TEST_CORE_H_
#define TEST_CORE_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "core_state_internal.h"

/*** Test Definitions ***/

#define EXPR_TRUE(expr) ((expr) ? true : false)
#define EXPR_FALSE(expr) ((expr) ? false : true)
#define EXPR_EQUAL(expr1, expr2) (((expr1) == (expr2)) ? true : false)

/*** Struct Declarations ***/

typedef struct all_test_results{
	uint32_t total;
	uint32_t passed;
	uint32_t failed;
} all_test_results;

typedef struct test_details{
	char* name;
	bool passed;
	uint32_t sub_checks_passed;
	uint32_t sub_checks_failed;
} test_details;

/*** Typedefs ***/

typedef test_details (*test_function) (void);

/*** Public Function Declarations ***/

void run_tests(const test_function tests[], size_t num_tests);

#endif /* TEST_CORE_H_ */
