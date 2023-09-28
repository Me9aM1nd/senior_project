/*
 * com_preasure.h
 *
 *  Created on: Sep 28, 2023
 *      Author: AzRy
 */

#ifndef COM_PREASURE_H_
#define COM_PREASURE_H_

#include "main.h"

void init_bpm(UART_HandleTypeDef* huart, GPIO_TypeDef* port, int num);
void turn_on_bpm();

void bpm_thread(int* DIA, int* SYS, int* PIL);
void get_status();


#endif /* COM_PREASURE_H_ */
