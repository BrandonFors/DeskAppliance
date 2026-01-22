#ifndef VENT_H
#define VENT_H
#include <stdbool.h>
#include <stdint.h>

void vent_init();
uint32_t angle_to_duty(uint8_t angle);
void vent_set_angle(uint8_t angle);
bool get_vent_is_auto();
bool get_vent_is_enabled();
void vent_toggle_enabled();
void vent_toggle_auto();
void vent_send_sensor_pct(uint8_t sensor_pct);

#endif