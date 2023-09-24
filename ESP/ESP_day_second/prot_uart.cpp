// #include "prot_uart.h"

// #include "HardwareSerial.h"

// int addTwoInts(int a, int b)
// {
//   return a + b;
// }

// HardwareSerial stm_uart(2);

// prot_uart_t base;

// char uart_prot_init(int speed, char rx, char tx){

//   stm_uart.begin(speed, SERIAL_8N1, rx, tx);

//   Serial.println("<UART INIT>");
//   Serial.print("Speed: ");
//   Serial.println(speed);
//   return 1;
// }

// void uart_prot_thread(){

//   while(stm_uart.available()){

//     base.temp_ = stm_uart.read();
//     Serial.print(base.temp_, HEX);
//     Serial.print(" ");
//     if(base.temp_ == MESSAGE_START_FAST) base.stm_rx_index = 0;
//     else base.STM_RX_BUF[base.stm_rx_index++] = base.temp_;

//     if(base.stm_rx_index >127 ) base.stm_rx_index = 0;
//     if(base.temp_ == MESSAGE_END_FAST)break;

//   }
//   Serial.println("");
//   if(base.STM_RX_BUF[base.stm_rx_index-1] == MESSAGE_END_FAST) {

//     stm_uart.println("OK <3");
//     // analyze_stm_packet();
//     Serial.println("mec dzalian miyvarxar");
  
//   }
// }