#ifndef _PROT_UART_H_
#define _PROT_UART_H_


#include <Arduino.h>

#define MESSAGE_START_FAST   0xAA
#define MESSAGE_END_FAST     0x55

#define MESSAGE_START_SLOW   0xCC
#define MESSAGE_END_SLOW     0x77


#define STOP_RECEIVE 17

typedef enum{
  F_START,
  F_PULSE_PARAM_1,
  F_PULSE_PARAM_2,
  F_PULSE_PARAM_3,
  F_PULSE_PARAM_4,
  F_SAT_PARAM_1,
  F_SAT_PARAM_2,
  F_SAT_PARAM_3,
  F_SAT_PARAM_4,
  F_TEMP_PARAM_1,
  F_TEMP_PARAM_2,
  F_TEMP_PARAM_3,
  F_TEMP_PARAM_4,
  F_END_1,
  F_END_2
}fast_e;

typedef enum{
  S_START,
  S_PREASURE_1,
  S_PREASURE_2,
  S_PREASURE_3,
  S_PREASURE_4,
  S_END_1,
  S_END_2
}slow_e;

typedef struct{

  int temp;
  int preasure;
  int heart_rate;
  int saturation;
  uint8_t valid;

}measured_params_t;

typedef struct{
  measured_params_t params;
  char temp_;

  uint8_t state;

}prot_uart_t;

char uart_prot_init(int speed, char rx, char tx);
void uart_prot_thread(void);

#endif