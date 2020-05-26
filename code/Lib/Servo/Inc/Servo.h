#ifndef INC_SERVO_H_
#define INC_SERVO_H_
#include <stdint.h>

#define TIM_NO htim13
#define TIM_CH_NO TIM_CHANNEL_1

#define ANGLE_MIN 0
#define ANGLE_MAX 900

#define PWM_MIN 1000
#define PWM_MAX 1950

#define STEP ((1000 * (PWM_MAX - PWM_MIN)) / (ANGLE_MAX - ANGLE_MIN))

void Servo_set_angle(uint16_t angle, uint8_t mode);

#endif /* INC_SERVO_H_ */