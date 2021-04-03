#pragma once
#include <stdint.h>

void matrix_begin();
void matrix_power_off();
void matrix_power_on();
void matrix_IRQ_call();
void matrix_print_char(uint8_t x, uint8_t y, uint8_t ch);
void matrix_write_pixel(uint8_t x, uint8_t y, uint8_t vl);