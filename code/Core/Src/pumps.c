/*
 * pumps.c
 *
 *  Created on: Jun 7, 2020
 *      Author: tymon
 */

#include "pumps.h"


void pumps_init(void) {
  pumps_off(1);
  pumps_off(2);
}


uint8_t pumps_is_on(uint8_t channel) {
  return channel == 1
      ? HAL_GPIO_ReadPin(PWM1_GPIO_Port, PWM1_Pin)
      : HAL_GPIO_ReadPin(PWM2_GPIO_Port, PWM2_Pin);
}

void pumps_on(uint8_t channel) {
  channel == 1
      ? HAL_GPIO_WritePin(PWM1_GPIO_Port, PWM1_Pin, GPIO_PIN_SET)
      : HAL_GPIO_WritePin(PWM2_GPIO_Port, PWM2_Pin, GPIO_PIN_SET);
}

void pumps_off(uint8_t channel) {
  channel == 1
      ? HAL_GPIO_WritePin(PWM1_GPIO_Port, PWM1_Pin, GPIO_PIN_RESET)
      : HAL_GPIO_WritePin(PWM2_GPIO_Port, PWM2_Pin, GPIO_PIN_RESET);
}

void pumps_toggle(uint8_t channel) {
  if(pumps_is_on(channel) > 0)
    pumps_off(channel);
  else
    pumps_on(channel);
}
