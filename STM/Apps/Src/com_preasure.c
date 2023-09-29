/*
 * com_preasure.c
 *
 *  Created on: Sep 28, 2023
 *      Author: AzRy
 */

#include "com_preasure.h"
#include "stdlib.h"
#include "string.h"


#define WAIT_TIME 60000

int status = 0;
UART_HandleTypeDef* huart_p;
GPIO_TypeDef* button_port;
int button_num;
uint8_t buffer[1024];
int curr_index;

//char KEY_CODE[] = "find a space:";
uint8_t KEY_CODE[]= {0x0d,0x0a,0x0d,0x0a};


void init_bpm(UART_HandleTypeDef* huart, GPIO_TypeDef* port, int num){
	huart_p = huart;
	button_port = port;
	button_num = num;
	debug_printf("blood preasure measurement system init\r\n");
}

void turn_on_bpm(){
	HAL_GPIO_WritePin(button_port, button_num, 1);
	HAL_Delay(10);
	HAL_GPIO_WritePin(button_port, button_num, 0);
}

int convert(uint8_t a, uint8_t b){
	int result = (a - 0x30) * 16 + b - 0x30;

	return result;
}

void analyze_it (int* DIA, int* SYS, int* PUL){

	char buf[20];
	for(int q = 0; q < sizeof(buffer); q++){
		if(memcmp(&buffer[q], KEY_CODE, sizeof(KEY_CODE)) == 0){

			*SYS = convert(buffer[q + sizeof(KEY_CODE)], buffer[q + sizeof(KEY_CODE) + 1]);
			*DIA = convert(buffer[q + sizeof(KEY_CODE) + 2], buffer[q + sizeof(KEY_CODE) + 3]);
//			*PUL = convert(buffer[q + sizeof(KEY_CODE) + 6], buffer[q + sizeof(KEY_CODE) + 7]);
		}
	}

}

void bpm_thread(int* DIA, int* SYS, int* PUL){
	int start_time = HAL_GetTick();
	int rame = start_time;
	memset(buffer, 0, sizeof(buffer));
	curr_index = 0;

	debug_printf("me move %d\r\n", HAL_UART_Receive_IT(huart_p, &buffer[curr_index], 1));

	while(HAL_GetTick() - start_time < WAIT_TIME){
		if(HAL_GetTick() - rame > 5000){
			debug_printf("buffer -> %s\r\n", buffer);
			debug_printf("buffer -> %m\r\n", buffer, sizeof(buffer));
			rame = HAL_GetTick();
		}
	}

	analyze_it(DIA,SYS,PUL);


}
void get_status();


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    // Check if the UART instance is UART2
    if (huart->Instance == USART2) {
    	curr_index++;
        HAL_UART_Receive_IT(huart_p, &buffer[curr_index], 1);
    }
}
