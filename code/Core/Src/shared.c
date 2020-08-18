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
  max_pouring_distance = sensor_to_cup_distance + 20;
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

  pumps_off(1);
  pumps_off(2);

  menu_go_home();
}

void init_pouring(void) {
  LCD_Clear(BLACK);
  menu_display_pouring();
  menu_state = MENU_STATE_POURING;

  HAL_TIM_Base_Start_IT(&htim3);

  last_measurements_index = 0;
  last_measurements_filled = 0;

  liquid1_distance =  sensor_to_cup_bottom_distance - max_pouring_height * liquid1 / 100;
  liquid2_distance =  liquid1_distance -  (max_pouring_height * liquid2 / 100);

  if(liquid1 > 0)
    pumps_on(1);

  else if (liquid2 > 0)
    pumps_on(2);

  else
    stop_pouring();
}

uint16_t get_average_distance() {
  last_measurements[last_measurements_index++] = distance_milimeters;
  if(last_measurements_index == MAX_LAST_MEASUREMENTS) {
    last_measurements_index = 0;
    last_measurements_filled = 1;
  }

  uint8_t max_index = last_measurements_filled == 1 ? MAX_LAST_MEASUREMENTS : last_measurements_index;
  uint16_t distance_average = 0;
  for(uint8_t i = 0; i < max_index; i++) {
    distance_average += last_measurements[i];
  }
  distance_average /= max_index;

  return distance_average;
}

void perform_pouring(void) {
  menu_display_pouring();

  average_distance = get_average_distance();

  if(average_distance > sensor_to_cup_bottom_distance)
    pour_percentage = 0;
  else
    pour_percentage = 100 * (sensor_to_cup_bottom_distance - distance_milimeters) / liquid2_distance;

  if(average_distance < max_pouring_distance) {
    stop_pouring();
    return;
  }

  if(pumps_is_on(1))
  {
    if(average_distance <= liquid1_distance) {
      pumps_off(1);
      if (liquid2_distance > 0)
        pumps_on(2);
    }
  }

  if(pumps_is_on(2))
  {
    if(average_distance <= liquid2_distance) {
      pumps_off(2);
      stop_pouring();
    }
  }
}

void stop_pouring(void) {
  HAL_TIM_Base_Stop_IT(&htim3);
  htim3.Instance->CNT = 0;

  pumps_off(1);
  pumps_off(2);

  LCD_Clear(BLACK);
  menu_go_home();
}
