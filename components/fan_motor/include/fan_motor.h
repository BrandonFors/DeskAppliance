#ifndef FAN_MOTOR_H
#define FAN_MOTOR_H
#include <stdint.h>
#include <stdbool.h>

void fan_init();
void fan_set_speed(uint8_t percent);
void fan_on();
void fan_off();
bool get_fan_is_auto();
bool get_fan_is_enabled();
void fan_toggle_auto();
void fan_toggle_enabled();


#endif