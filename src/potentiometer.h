#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <stdint.h>


void potentiometer_init();
int invert_reading(int raw);
int read_pot_raw();
int read_pot_pct();
float read_pot_volt();

#endif