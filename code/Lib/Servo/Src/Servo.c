#include "servo.h"
#include "tim.h"

void servo_set_angle(uint16_t angle, uint8_t mode)
{
	uint16_t val;

	if(angle > ANGLE_MAX)
	{
	  angle = ANGLE_MAX;
	}
	else if (angle < ANGLE_MIN)
	{
	  angle = ANGLE_MIN;
	}

	if(mode)
	{
    val = PWM_MAX - ((angle - ANGLE_MIN) * STEP) / 1000;
	}
	else
	{
    val = PWM_MIN + ((angle - ANGLE_MIN) * STEP) / 1000;
	}

	__HAL_TIM_SET_COMPARE(&TIM_NO, TIM_CH_NO, val);
}



