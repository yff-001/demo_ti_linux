#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void timer_init();
void permtick_count();
void systick_count();
uint8_t has_permtick_elapsed();
uint8_t has_systick_elapsed();

#endif
