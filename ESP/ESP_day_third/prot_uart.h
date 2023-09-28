#ifndef _PROT_UART_H_
#define _PROT_UART_H_


#include <Arduino.h>

#define MESSAGE_START_P   0xAA
#define MESSAGE_END_P     0x55

#define STOP_RECEIVE    20

typedef enum{

  MESSAGE_SERIAL_ID_1,
  MESSAGE_SERIAL_ID_2,
  MESSAGE_SERIAL_ID_3,
  MESSAGE_SERIAL_ID_4,

  MESSAGE_TEMP_PARAM_1,
  MESSAGE_TEMP_PARAM_2,
  MESSAGE_TEMP_PARAM_3,
  MESSAGE_TEMP_PARAM_4,
  
  // MESSAGE_SYS_PARAM_1,
  // MESSAGE_SYS_PARAM_2,
  // MESSAGE_SYS_PARAM_3,
  // MESSAGE_SYS_PARAM_4,

  // MESSAGE_DIA_PARAM_1,
  // MESSAGE_DIA_PARAM_2,
  // MESSAGE_DIA_PARAM_3,
  // MESSAGE_DIA_PARAM_4,

  MESSAGE_PULSE_PARAM_1,
  MESSAGE_PULSE_PARAM_2,
  MESSAGE_PULSE_PARAM_3,
  MESSAGE_PULSE_PARAM_4,

  MESSAGE_SAT_PARAM_1,
  MESSAGE_SAT_PARAM_2,
  MESSAGE_SAT_PARAM_3,
  MESSAGE_SAT_PARAM_4,

  MESSAGE_FINGER_ON_PARAM,

  MESSAGE_END
}fast_e;

typedef struct{

  float temp;
  int heart_rate;
  float saturation;
  int SYS;
  int DIA;
  int serial_ID;
  uint8_t valid;
  uint8_t finger_on;

}measured_params_t;

typedef struct{
  measured_params_t params;
  char temp_;

  uint8_t state;
  uint8_t screen_idx;

}prot_uart_t;

prot_uart_t* uart_prot_init(int speed, char rx, char tx);
void uart_prot_thread(void);

#endif