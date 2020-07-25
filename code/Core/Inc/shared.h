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
volatile uint16_t distance_milimeters;

void liquid_add_percent(uint8_t *liquid, int8_t value);
uint16_t start_cup_height_measurement(void);
