#ifndef LAMP_H
#define LAMP_H
#include <stdbool.h>
#include <stdint.h>
void lamp_init();

void lamp_set_brightness(uint8_t percent);
bool get_lamp_is_auto();
bool get_lamp_is_enabled();
void lamp_toggle_auto();
void lamp_toggle_enabled();
void lamp_off();
void lamp_on();
void lamp_send_sensor_pct(uint8_t sensor_pct);

#endif