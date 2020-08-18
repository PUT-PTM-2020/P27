/*
 * pumps.h
 *
 *  Created on: Jun 7, 2020
 *      Author: tymon
 */

#ifndef INC_PUMPS_H_
#define INC_PUMPS_H_
#endif /* INC_PUMPS_H_ */

#include "tim.h"
#include "main.h"

#define PUMPS_TIMER htim12
#define PUMP_1 TIM_CHANNEL_1
#define PUMP_2 TIM_CHANNEL_2

uint16_t pump_max_pwm;

void pumps_init(void);
uint8_t pumps_is_on(uint8_t channel);
void pumps_on(uint8_t channel);
void pumps_off(uint8_t channel);
void pumps_toggle(uint8_t channel);
