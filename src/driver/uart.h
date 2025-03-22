#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_init(void(*callback)(uint8_t));
void uart_send_byte(uint8_t data);

#endif
