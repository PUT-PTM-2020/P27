/*
 * shared.c
 *
 *  Created on: Jun 6, 2020
 *      Author: tymon
 */

#include <shared.h>
#include "servo.h"
#include "stm32f4xx_hal.h"

void liquid_add_percent(uint8_t *liquid, int8_t value) {
  uint8_t new_value = (*liquid) + value;
  uint8_t total_value = liquid1 + liquid2 + value;

  if(new_value < 0 || new_value > 100 || total_value > 100 || total_value < 0)
    return;

  (*liquid) = new_value;
}

uint16_t start_cup_height_measurement(void) {
  uint16_t min_distance = distance_milimeters;
  uint16_t min_distance_angle = 0;

  servo_set_angle(0, 0);
  HAL_Delay(300);

  for(uint16_t angle = 0; angle <= 1500; angle += 50) {
    servo_set_angle(angle, 0);
    HAL_Delay(50);

    if(distance_milimeters < min_distance) {
      min_distance = distance_milimeters;
      min_distance_angle = angle;
    }
  }

  servo_set_angle(0, 0);
  HAL_Delay(300);

  return cos(min_distance_angle * 3.14 / 1800) * min_distance;


  /*
   *
  HAL_Delay(50);
  servo_angle += 10;
  if(servo_angle > 450) {
    servo_angle = 0;
    return_servo = 1;
  }

  servo_set_angle(servo_angle, 0);

  if(return_servo == 1) {
    return_servo = 0;
    HAL_Delay(1000);
  }
   *
   * */
}
