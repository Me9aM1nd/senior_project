/*
 * hrspo2_converter.c
 *
 *  Created on: Sep 19, 2023
 *      Author: ASUS
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "MAX30102.h"
#include "dev_trace.h"
#include "algorithm_by_RF.h"
#include "hrspo2_converter.h"
#include "max30102_for_stm32_hal.h"

/* USER CODE END Includes */
extern I2C_HandleTypeDef hi2c1;

void max30102_plot(uint32_t ir_sample, uint32_t red_sample);


static uint32_t aun_ir_buffer[BUFFER_SIZE]; //infrared LED sensor data
static uint32_t aun_red_buffer[BUFFER_SIZE];  //red LED sensor data
uint32_t buf_index;

uint8_t en_reg[2] = {0};

// MAX30102 object
max30102_t max30102;


void max30102_setup()
{
	max30102_init(&max30102, &hi2c1);
	//  max30102_on_interrupt(&max30102);

	  max30102_reset(&max30102);
	  max30102_clear_fifo(&max30102);


	  // FIFO configurations
	  max30102_set_fifo_config(&max30102, max30102_smp_ave_8, 1, 7);

	  // LED configurations
	  max30102_set_led_pulse_width(&max30102, max30102_pw_16_bit);
	  max30102_set_adc_resolution(&max30102, max30102_adc_2048);
	  max30102_set_sampling_rate(&max30102, max30102_sr_800);
	  max30102_set_led_current_1(&max30102, 6.2);
	  max30102_set_led_current_2(&max30102, 6.2);

	    // Enter SpO2 mode
	  max30102_set_mode(&max30102, max30102_spo2);

	   // Enable FIFO_A_FULL interrupt
	  max30102_set_a_full(&max30102, 1);

	  // Enable die temperature measurement
	  max30102_set_die_temp_en(&max30102, 1);

	  // Enable DIE_TEMP_RDY interrupt
	  max30102_set_die_temp_rdy(&max30102, 1);


	  max30102_read(&max30102, 0x00, en_reg, 1);
}


void max30102_loop()
{


  max30102_read(&max30102, 0x07, en_reg, 1);
  max30102_interrupt_handler(&max30102);


  if (buf_index >= BUFFER_SIZE){
	  float n_spo2;
	  float ratio;
	  float correl;
	  int8_t ch_spo2_valid;  				// indicator to show if the SPO2 calculation is valid
	  int32_t n_heart_rate; 				// heart rate value
	  int8_t  ch_hr_valid;  				// indicator to show if the heart rate calculation is valid


	  // calculate heart rate and SpO2 after BUFFER_SIZE samples (ST seconds of samples) using Robert's method
	  rf_heart_rate_and_oxygen_saturation(aun_ir_buffer, BUFFER_SIZE, aun_red_buffer, &n_spo2, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid, &ratio, &correl);


	  // display results
//	  if (ch_hr_valid && ch_spo2_valid)
//	  {
		debug_printf("SPO2: %f , Heart Rate: %f\r\n", n_spo2, n_heart_rate);
//	  }
//	  else
//	  {
//		debug_printf("Not valid. Are you still alive?\r\n");
//	  }
	  buf_index = 0;
  }
}


// Override plot function
void max30102_plot(uint32_t ir_sample, uint32_t red_sample)
{
    // printf("ir:%u\n", ir_sample);                  // Print IR only
    // printf("r:%u\n", red_sample);                  // Print Red only
	debug_printf("ir:%d,r:%d\n\r", ir_sample, red_sample);    // Print IR and Red

//	memcpy(&tx_buffer[5], &ir_sample, 4);
//	memcpy(&tx_buffer[9], &red_sample, 4);
//	HAL_UART_Transmit_DMA(&huart1, samples_buf, sizeof(samples_buf));

	if (buf_index < BUFFER_SIZE){
		aun_ir_buffer[buf_index]=ir_sample;
		aun_red_buffer[buf_index] = red_sample;
		buf_index ++;
	}


}


