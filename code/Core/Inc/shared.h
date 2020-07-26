/*
 * shared.h
 *
 *  Created on: Jun 6, 2020
 *      Author: tymon
 */

#ifndef INC_SHARED_H_
#define INC_SHARED_H_
#endif /* INC_SHARED_H_ */

#include <stdio.h>
#include <math.h>

volatile uint8_t liquid1;
volatile uint8_t liquid2;

void liquid_add_percent(uint8_t *liquid, int8_t value);
