#include "prot_uart.h"

#include "HardwareSerial.h"

HardwareSerial stm_uart(0);

prot_uart_t base;

prot_uart_t* uart_prot_init(int speed, int rx, int tx){

  stm_uart.begin(speed, SERIAL_8N1, rx, tx);

  Serial.print("<UART INIT> rx: ");
  Serial.print(rx);
  Serial.print(" tx: ");
  Serial.println(tx);
  Serial.print("Speed: ");
  Serial.println(speed);
  return &base;
}


void preety_number_preety_result(){
  if(base.params.valid){
    base.params.saturation /= 1000;
    base.params.temp /= 1000; 
  }
  if(base.params.finger_on == 0){
    base.params.heart_rate = 0;
    base.params.saturation = 0;
  }
  if(base.params.heart_rate < 40  || base.params.heart_rate >90) base.params.heart_rate = 0;
  if(base.params.saturation > 100 || base.params.saturation <75) base.params.saturation = 0;
  if(base.params.temp < 20 || base.params.temp > 40 ) base.params.temp = 0;
}


void analyze_message(){
  Serial.println("start message analyze");

  while(stm_uart.available()){
     
    if(base.state == STOP_RECEIVE) break;

    base.temp_ = stm_uart.read();
    // Serial.print(base.temp_, HEX);
    // Serial.print("state ");
    // Serial.println(base.state);

    switch(base.state){
      case MESSAGE_SERIAL_ID_1: {
        base.params.serial_ID = base.temp_;
        base.state = MESSAGE_SERIAL_ID_2;
      }break;

      case MESSAGE_SERIAL_ID_2: {
        base.params.serial_ID += base.temp_ <<8;
        base.state = MESSAGE_SERIAL_ID_3;
      }break;

      case MESSAGE_SERIAL_ID_3: {
        base.params.serial_ID += base.temp_ <<16;
        base.state = MESSAGE_SERIAL_ID_4;
      }break;

      case MESSAGE_SERIAL_ID_4: {
        base.params.serial_ID += base.temp_ <<24;
        base.state = MESSAGE_TEMP_PARAM_1;
      }break;

      case MESSAGE_TEMP_PARAM_1: {
        base.params.temp = base.temp_;
        base.state = MESSAGE_TEMP_PARAM_2; 
      }break;
      
      case MESSAGE_TEMP_PARAM_2: {
        base.params.temp += base.temp_ << 8;
        base.state = MESSAGE_TEMP_PARAM_3;
      }break;

      case MESSAGE_TEMP_PARAM_3: {
        base.params.temp += base.temp_ << 16;
        base.state = MESSAGE_TEMP_PARAM_4;
      }break;

      case MESSAGE_TEMP_PARAM_4: {
        base.params.temp += base.temp_ << 24;
        base.state = MESSAGE_PULSE_PARAM_1;
      }break;

      // case MESSAGE_SYS_PARAM_1: {
      //   base.params.SYS += base.temp_;
      //   base.state = MESSAGE_SYS_PARAM_2
      // }break;
      
      // case MESSAGE_SYS_PARAM_2: {
      //   base.params.SYS += base.temp_ << 8;
      //   base.state = MESSAGE_SYS_PARAM_3
      // }break;

      // case MESSAGE_SYS_PARAM_3: {
      //   base.params.SYS += base.temp_ << 16;
      //   base.state = MESSAGE_SYS_PARAM_4
      // }break;

      // case MESSAGE_SYS_PARAM_4: {
      //   base.params.SYS += base.temp_ << 24;
      //   base.state = MESSAGE_DIA_PARAM_1
      // }break;

      // case MESSAGE_DIA_PARAM_1: {
      //   base.params.DIA += base.temp_;
      //   base.state = MESSAGE_DIA_PARAM_2;
      // }break;
      
      // case MESSAGE_DIA_PARAM_2: {
      //   base.params.DIA += base.temp_ << 8;
      //   base.state = MESSAGE_DIA_PARAM_3;
      // }break;
      
      // case MESSAGE_DIA_PARAM_3: {
      //   base.params.DIA += base.temp_ << 16;
      //   base.state = MESSAGE_DIA_PARAM_4;
      // }break;

      // case MESSAGE_DIA_PARAM_4: {
      //   base.params.DIA += base.temp_;
      //   base.state = MESSAGE_PULSE_PARAM_1;
      // }break;

      case MESSAGE_PULSE_PARAM_1:{
        base.params.heart_rate = base.temp_;
        base.state = MESSAGE_PULSE_PARAM_2;
      }break;

      case MESSAGE_PULSE_PARAM_2:{
        base.params.heart_rate += base.temp_ << 8;
        base.state = MESSAGE_PULSE_PARAM_3;
      }break;
      
      case MESSAGE_PULSE_PARAM_3:{
        base.params.heart_rate += base.temp_ << 16;
        base.state = MESSAGE_PULSE_PARAM_4;
      }break;

      case MESSAGE_PULSE_PARAM_4:{
        base.params.heart_rate += base.temp_ << 24;
        base.state = MESSAGE_SAT_PARAM_1;
      }break;
      
      case MESSAGE_SAT_PARAM_1: {
        base.params.saturation = base.temp_;
        base.state = MESSAGE_SAT_PARAM_2;
      }break;

      case MESSAGE_SAT_PARAM_2: {
        base.params.saturation += base.temp_ << 8;
        base.state = MESSAGE_SAT_PARAM_3;
      }break;

      case MESSAGE_SAT_PARAM_3: {
        base.params.saturation += base.temp_ << 16;
        base.state = MESSAGE_SAT_PARAM_4;
      }break;

      case MESSAGE_SAT_PARAM_4: {
        base.params.saturation += base.temp_ << 24;
        base.state = MESSAGE_FINGER_ON_PARAM;
      }break;

      case MESSAGE_FINGER_ON_PARAM:{
        base.params.finger_on = base.temp_;
        base.state = MESSAGE_END_P;
      }break;

      case MESSAGE_END_P : {
        base.state = STOP_RECEIVE;
        base.params.valid = base.temp_ == MESSAGE_END_P;
      }break;

      default: {
        Serial.print(base.state);
        Serial.println("MSG FAST STATUS ERROR!!!");
      }break;
    }
  }

  Serial.println("");
}

void uart_prot_thread(){
  if(stm_uart.available()){
    base.temp_ = stm_uart.read();
    base.params.valid = 0;
    if( base.temp_ == MESSAGE_START_P){
      base.state = MESSAGE_SERIAL_ID_1;
      analyze_message();

      preety_number_preety_result();
      Serial.print("serial id ");
      Serial.println(base.params.serial_ID);
      Serial.print("temp ");
      Serial.println(base.params.temp);
      Serial.print("heart rate ");
      Serial.println(base.params.heart_rate);
      Serial.print("saturation ");
      Serial.println(base.params.saturation);
      Serial.print("finger status ");
      Serial.println(base.params.finger_on);
    }

  }

}