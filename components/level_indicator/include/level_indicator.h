#ifndef LEVEL_INDICATOR_H
#define LEVEL_INDICATOR_H
#include <stdint.h>


void indicator_init(); //initialize the indicator LEDS

void set_level_indicator(int lvl); // set the level or amount of LEDS that are lit up

void set_level_indicator_from_pct(uint8_t percent); // set level based on percentage

#endif