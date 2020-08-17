/*
 * shared.c
 *
 *  Created on: Jun 6, 2020
 *      Author: tymon
 */

#include <shared.h>
#include "servo.h"
#include "stm32f4xx_hal.h"
#include "tim.h"
#include "lcd_menu.h"

void liquid_add_percent(uint8_t *liquid, int8_t value) {
  uint8_t new_value = (*liquid) + value;
  uint8_t total_value = liquid1 + liquid2 + value;

  if(new_value < 0 || new_value > 100 || total_value > 100 || total_value < 0)
    return;

  (*liquid) = new_value;
}

void init_cup_height_measurement(void) {
  menu_state = MENU_STATE_MEASUREMENT;

  HAL_TIM_Base_Start_IT(&htim3);

  servo_set_angle(0, 0);
  min_distance = distance_milimeters;
  sensor_to_cup_bottom_distance = distance_milimeters;
  min_distance_angle = current_servo_angle;

  sensor_to_cup_distance = 0;
  cup_height = 0;
  max_pouring_distance = 0;
  max_pouring_height = 0;
  pour_percentage = 0;

  if(distance_milimeters > 120) {
    interrupt_procedures();
    return;
  }

  LCD_Clear(BLACK);
  menu_display_measurement();
}

void perform_cup_height_measurement(void) {
  menu_display_measurement();

  if(current_servo_angle > 900) {
    interrupt_procedures();
    return;
  }

  if(distance_milimeters < min_distance) {
    min_distance = distance_milimeters;
    min_distance_angle = current_servo_angle;
  }

  servo_set_angle(current_servo_angle + 10, 0);

  if(distance_milimeters > min_distance + 30) {
    stop_cup_height_measurement();
    return;
  }
}

void stop_cup_height_measurement(void) {
  HAL_TIM_Base_Stop_IT(&htim3);
  htim3.Instance->CNT = 0;
  servo_set_angle(0, 0);

  sensor_to_cup_distance = cos(min_distance_angle * 3.14 / 1800) * min_distance;
  cup_height = sensor_to_cup_bottom_distance - sensor_to_cup_distance;
  max_pouring_distance = sensor_to_cup_distance + 40;
  max_pouring_height = sensor_to_cup_bottom_distance - max_pouring_distance;

  if(max_pouring_height > 120) {
    interrupt_procedures();
    return;
  }

  LCD_Clear(BLACK);
  menu_state = MENU_STATE_CONFIRM_MEASUREMENT;
  menu_display_confirm_measurement();
}

void interrupt_procedures(void) {
  HAL_TIM_Base_Stop_IT(&htim3);
  htim3.Instance->CNT = 0;

  servo_set_angle(0, 0);

  pumps_off(PUMP_1);
  pumps_off(PUMP_2);

  menu_go_home();
}

void init_pouring(void) {
  LCD_Clear(BLACK);
  menu_display_pouring();
  menu_state = MENU_STATE_POURING;

  HAL_TIM_Base_Start_IT(&htim3);

  pumps_on(liquid1 > 0 ? PUMP_1 : PUMP_2);

  last_measurements_index = 0;
  last_measurements_filled = 0;
}

uint8_t check_is_pouring() {
  last_measurements[last_measurements_index++] = distance_milimeters;
  if(last_measurements_index == MAX_LAST_MEASUREMENTS) {
    last_measurements_index = 0;
    last_measurements_filled = 1;
  }

  if(last_measurements_filled == 0)
    return 1;

  uint16_t distance_average = 0;
  for(uint8_t i = 0; i < MAX_LAST_MEASUREMENTS; i++) {
    distance_average += last_measurements[i];
  }
  distance_average /= MAX_LAST_MEASUREMENTS;

  if(distance_average - distance_milimeters < 10)
    return 0;

  return 1;
}

void perform_pouring(void) {
  menu_display_pouring();

  if(distance_milimeters < max_pouring_distance) {
    stop_pouring();
    return;
  }

  if(check_is_pouring() == 0) {
    stop_pouring();
    return;
  }

  pour_percentage = (sensor_to_cup_bottom_distance - distance_milimeters) / max_pouring_height;

  if(pour_percentage >= liquid1) {
    pumps_off(PUMP_1);

    if(liquid2 > 0)
      pumps_on(PUMP_2);
  }

  if(pour_percentage >= liquid1 + liquid2) {
    stop_pouring();
  }
}

void stop_pouring(void) {
  HAL_TIM_Base_Stop_IT(&htim3);
  htim3.Instance->CNT = 0;

  pumps_off(PUMP_1);
  pumps_off(PUMP_2);

  menu_go_home();
}
