// See LICENSE for license details.

#include "uart.h"
#include <stdio.h>

volatile uint32_t *uart = (uint32_t *)(UART_BASE);
int snprintf(char* out, size_t n, const char* s, ...);

void uart_init() {
  uart[2]=0x04;
  uart[3]=0x00;
}

int32_t uart_getchar() {
  if (!(uart[UART_STATUS] & UART_STATUS_RXVALID))
    return -1;

  return uart[UART_RX];
}

void uart_send(uint8_t data) {
  if (uart[UART_STATUS] & UART_STATUS_TXFULL)
    return ;

  else {
    while((uart[UART_STATUS] & UART_STATUS_TXEMPTY) != UART_STATUS_TXEMPTY);
    uart[UART_TX] = data;
  }
}

void uart_send_string(const char *str) {
  while(*str != 0) {
     while((uart[UART_STATUS] & UART_STATUS_TXEMPTY) != UART_STATUS_TXEMPTY);
     uart[UART_TX] = *(str++);
  }
}

void debugPrint_uintptr(char * msg, uintptr_t val)
{
  char buf[128] = {0,};
  snprintf(buf, sizeof buf, "[SUKER]*INFO* : %s=0x%lx \r\n", msg, val);
  uart_send_string(buf);
}
