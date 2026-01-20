#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <stdint.h>
#include "driver/gptimer.h"

void potentiometer_init();
int invert_reading(int raw);
int read_pot_vltg();
int read_pot_pct();

extern gptimer_handle_t pot_timer;

#endif