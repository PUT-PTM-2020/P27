/*
 * pumps.c
 *
 *  Created on: Jun 7, 2020
 *      Author: tymon
 */

#include "pumps.h"


void pumps_init(void) {
  // Start TIM4 for L293D
  HAL_TIM_PWM_Start(&PUMPS_TIMER, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&PUMPS_TIMER, TIM_CHANNEL_2);

  // Start first motor clock wise rotation
  HAL_GPIO_WritePin(L293D_PUMP1_1_GPIO_Port, L293D_PUMP1_1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(L293D_PUMP1_2_GPIO_Port, L293D_PUMP1_2_Pin, GPIO_PIN_RESET);

  pump_max_pwm = __HAL_TIM_GET_AUTORELOAD(&PUMPS_TIMER);
}


uint8_t pumps_is_on(uint32_t channel) {
  return __HAL_TIM_GET_COMPARE(&PUMPS_TIMER, channel) > 0 ? 1 : 0;
}

void pumps_on(uint32_t channel) {
  __HAL_TIM_SET_COMPARE(&PUMPS_TIMER, channel, pump_max_pwm);
}

void pumps_off(uint32_t channel) {
  __HAL_TIM_SET_COMPARE(&PUMPS_TIMER, channel, 0);
}

void pumps_toggle(uint32_t channel) {
  if(__HAL_TIM_GET_COMPARE(&PUMPS_TIMER, channel) > 0)
    pumps_off(channel);
  else
    pumps_on(channel);
}
