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

uint8_t liquid1;
uint8_t liquid2;

uint16_t liquid1_distance;
uint16_t liquid2_distance;

uint8_t pour_wait_time;

volatile uint16_t distance_milimeters;

// Cup height measurements
volatile uint16_t cup_height;
volatile uint16_t max_pouring_distance;
volatile uint16_t sensor_to_cup_bottom_distance;
volatile uint16_t sensor_to_cup_distance;
volatile uint16_t min_distance;
volatile uint16_t min_distance_angle;
volatile uint16_t max_pouring_height;
volatile uint16_t pour_percentage;

#define MAX_LAST_MEASUREMENTS 5
volatile uint8_t last_measurements_index;
volatile uint8_t last_measurements_filled;
volatile uint16_t last_measurements[MAX_LAST_MEASUREMENTS];
volatile uint16_t average_distance;

void liquid_add_percent(uint8_t *liquid, int8_t value);

void init_cup_height_measurement(void);
void perform_cup_height_measurement(void);
void stop_cup_height_measurement(void);

void interrupt_procedures(void);

void init_pouring(void);
uint8_t check_is_pouring();
void perform_pouring(void);
void stop_pouring(void);
