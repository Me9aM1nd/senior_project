#include "prot_uart.h"

#include "HardwareSerial.h"

HardwareSerial stm_uart(2);

prot_uart_t base;

char uart_prot_init(int speed, char rx, char tx){

  stm_uart.begin(speed, SERIAL_8N1, rx, tx);

  Serial.println("<UART INIT> rx: ");
  Serial.print(rx);
  Serial.print(" tx: ");
  Serial.println(tx);
  Serial.print("Speed: ");
  Serial.println(speed);
  return 1;
}

void analyze_fast(){
  Serial.println("start msg fast");

  while(stm_uart.available()){
     
    if(base.state == STOP_RECEIVE) break;

    base.temp_ = stm_uart.read();
    Serial.print(base.temp_);
    Serial.print(" ");
    

    switch(base.state){
      case F_START: {
        if(base.temp_ == MESSAGE_START_FAST) base.state = F_PULSE_PARAM_1;
        else base.state = STOP_RECEIVE;
      }break;

      case F_PULSE_PARAM_1: {
        base.params.heart_rate = base.temp_;
        base.state = F_PULSE_PARAM_2;
      }break;

      case F_PULSE_PARAM_2: {
        base.params.heart_rate += base.temp_ << 8;
        base.state = F_PULSE_PARAM_3;
      }break;

      case F_PULSE_PARAM_3: {
        base.params.heart_rate += base.temp_ << 16;
        base.state = F_PULSE_PARAM_4;
      }break;

      case F_PULSE_PARAM_4: {
        base.params.heart_rate += base.temp_ << 24;
        base.state = F_SAT_PARAM_1;
      }break;

      case F_SAT_PARAM_1: {
        base.params.preasure = base.temp_;
        base.state = F_SAT_PARAM_2;
      }break;
      
      case F_SAT_PARAM_2: {
        base.params.preasure += base.temp_ << 8;
        base.state = F_SAT_PARAM_3;
      }break;

      case F_SAT_PARAM_3: {
        base.params.preasure += base.temp_ << 16;
        base.state = F_SAT_PARAM_4;
      }break;

      case F_SAT_PARAM_4: {
        base.params.preasure += base.temp_ << 24;
        base.state = F_TEMP_PARAM_1;
      }break;

      case F_TEMP_PARAM_1: {
        base.params.temp = base.temp_;
        base.state = F_TEMP_PARAM_2; 
      }break;
      
      case F_TEMP_PARAM_2: {
        base.params.temp += base.temp_ << 8;
        base.state = F_TEMP_PARAM_3;
      }break;

      case F_TEMP_PARAM_3: {
        base.params.temp += base.temp_ << 16;
        base.state = F_TEMP_PARAM_4;
      }break;

      case F_TEMP_PARAM_4: {
        base.params.temp += base.temp_ << 24;
        base.state = F_END_1;
      }break;

      case F_END_1: {
        if(base.temp_ == MESSAGE_END_FAST){
          base.state = F_END_2;
        } else{
          base.state = STOP_RECEIVE;
          base.params.valid = 0;
        }
      }

      case F_END_2: {
        base.state = STOP_RECEIVE;
        if(base.temp_ == MESSAGE_END_FAST){
          base.params.valid = 1;
        } else {
          base.params.valid = 0;
        }
      }

      default: {
        Serial.println("MSG FAST STATUS ERROR!!!");
      }break;
    }
  }

  Serial.println("");
}


void analyze_slow(){
  Serial.println("start analyze slow msg");

  while(stm_uart.available()){
    
    if(base.state == STOP_RECEIVE) break;

    base.temp_ = stm_uart.read();
    Serial.print(base.temp_);
    Serial.print(" ");

    switch (base.state){
      
      case S_START: {
        if(base.temp_ == MESSAGE_START_SLOW) base.state = S_PREASURE_1;
        else base.state = STOP_RECEIVE;
      }break;

      case S_PREASURE_1: {
        base.params.preasure = base.temp_;
        base.state = S_PREASURE_2;
      }break;

      case S_PREASURE_2: {
        base.params.preasure += base.temp_ << 8;
        base.state = S_PREASURE_3;
      }break;

      case S_PREASURE_3: {
        base.params.preasure += base.temp_ << 16;
        base.state = S_PREASURE_4;
      }break;

      case S_PREASURE_4: {
        base.params.preasure += base.temp_ << 24;
        base.state = S_END_1;
      }break;

      case S_END_1: {
        if(base.temp_ == MESSAGE_END_SLOW) {
          base.state = S_END_2;
        }else {
          base.state = STOP_RECEIVE;
          base.params.valid = 0;
        }
      }break;

      case S_END_2: {
        base.state = STOP_RECEIVE;
        if(base.temp_ == MESSAGE_END_SLOW) {
          base.params.valid = 1;
        }else{
          base.params.valid = 0;
        }
      }

      default: {
        Serial.println("MSG SLOW STATUS ERROR!!!");
      }break;
   }
  }
  Serial.println("");

}

void uart_prot_thread(){
  if(stm_uart.available()){
    base.temp_ = stm_uart.read();
    
    switch (base.temp_){
      case MESSAGE_START_FAST:{
        base.state = F_START;
        analyze_fast();
      }break;

      case MESSAGE_START_SLOW:{
        base.state = S_START;
        analyze_slow();
      }
      
      default: {
        Serial.println("Wrong Message Start !!!");
      }

    }

  }

}