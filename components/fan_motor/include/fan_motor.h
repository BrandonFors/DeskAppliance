#ifndef FAN_MOTOR_H
#define FAN_MOTOR_H
#include <stdint.h>

void fan_init();
void fan_set_speed(uint8_t percent);
void fan_on();
void fan_off();

#endif