// See LICENSE for license details.

#ifndef UART_HEADER_H
#define UART_HEADER_H

#include <stdint.h>
//#include "dev_map.h"

#define UART_BASE 0x60030000
extern volatile uint32_t *uart;

#define UART_RX		0
#define UART_TX		1
#define UART_STATUS	2
#define UART_CONTROL	3

#define UART_REGION		16

#define UART_STATUS_RXVALID	0x01
#define UART_STATUS_RXFULL	0x02
#define UART_STATUS_TXEMPTY	0x04
#define UART_STATUS_TXFULL	0x08
#define UART_STATUS_IE		0x10
#define UART_STATUS_OVERRUN	0x20
#define UART_STATUS_FRAME	0x40
#define UART_STATUS_PARITY	0x80

#define UART_CONTROL_RST_TX	0x01
#define UART_CONTROL_RST_RX	0x02
#define UART_CONTROL_IE	        0x10

// UART APIs
extern void uart_init();
extern void uart_send(uint8_t);
extern void uart_send_string(const char *str);
extern int32_t uart_getchar();

void debugPrint_uintptr(char * msg, uintptr_t val);
#endif
