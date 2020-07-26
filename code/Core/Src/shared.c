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
