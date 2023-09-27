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
//#include "graphics.h"


/* USER CODE END Includes */
extern I2C_HandleTypeDef hi2c1;

#define MAX_HEART_BEAT_TRACE 		140.0f
#define MY_SNPRINTF 		snprintf	// newlib snprintf with float support is too heavy and not threadsafe so using local snprintf from printf.c
										// but this causes a compile warning that float support is off so use this macro to prevent it
#define FAKE_MAX30102_CLONE				// if you have a fake Chinese cloned MAX30102 define this

DMA_HandleTypeDef hdma_spi1_tx;

static uint32_t aun_ir_buffer[BUFFER_SIZE]; //infrared LED sensor data
static uint32_t aun_red_buffer[BUFFER_SIZE];  //red LED sensor data

void Max30102Setup();
void Max30102Loop();

void max30102_plot(uint32_t ir_sample, uint32_t red_sample);


static uint32_t aun_ir_buffer[BUFFER_SIZE]; //infrared LED sensor data
static uint32_t aun_red_buffer[BUFFER_SIZE];  //red LED sensor data
uint32_t buf_index;

uint8_t en_reg[2] = {0};

// MAX30102 object
max30102_t max30102;
uint32_t last_time;
uint8_t num;
float n_spo2_sum;
int32_t n_heart_rate_sum;


void Max30102Setup()
{
  uint8_t uch_dummy;

  maxim_max30102_reset();
  maxim_max30102_read_reg(REG_INTR_STATUS_1, &uch_dummy);  // reads/clears the interrupt status register
  maxim_max30102_init();
}

// Takes samples from MAX30102.  Heart rate and SpO2 are calculated every ST seconds
void Max30102Loop(float *spo2_mean, uint32_t *heart_rate_mean, uint8_t *finger_on)
{
  float n_spo2;
  float ratio;
  float correl;
  int8_t ch_spo2_valid;  				// indicator to show if the SPO2 calculation is valid
  int32_t n_heart_rate; 				// heart rate value
  int8_t  ch_hr_valid;  				// indicator to show if the heart rate calculation is valid
  uint8_t i;
  static uint32_t un_min = 0x3FFFFUL;
  static uint32_t un_max = 0UL;
  static uint32_t un_prev_data = 0UL;  	// variables to calculate the on-board LED brightness that reflects the heartbeats
  static float f_heartbeatTrace = 0UL;
  float f_temp;


//  static int16_t x = 1;
//  static int16_t lastY = 35;

  // buffer length of BUFFER_SIZE stores ST seconds of samples running at FS sps
  for (i = 0U; i < BUFFER_SIZE; i++)
  {
//	while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_SET);	// wait until the interrupt pin asserts

#ifdef FAKE_MAX30102_CLONE
    maxim_max30102_read_fifo((aun_ir_buffer + i), (aun_red_buffer + i));  // read from MAX30102 FIFO
#else
    maxim_max30102_read_fifo((aun_red_buffer + i), (aun_ir_buffer + i));  // read from MAX30102 FIFO
#endif
    // calculate LED brightness
    if (aun_red_buffer[i] > un_prev_data)
    {
      f_temp = aun_red_buffer[i] - un_prev_data;
      f_temp /= (un_max - un_min);
      f_temp *= MAX_HEART_BEAT_TRACE;
      f_heartbeatTrace -= f_temp;
      if (f_heartbeatTrace < -25.0f)
      {
        f_heartbeatTrace = -25.0f;
      }
    }
    else
    {
	  f_temp = un_prev_data - aun_red_buffer[i];
	  f_temp /= (un_max - un_min);
	  f_temp *= MAX_HEART_BEAT_TRACE;
	  f_heartbeatTrace += f_temp;
	  if (f_heartbeatTrace > MAX_HEART_BEAT_TRACE + 25.0f)
	  {
		f_heartbeatTrace = MAX_HEART_BEAT_TRACE + 25.0f;
	  }
    }

//    GraphicsLine(x, 210 - lastY, x + 3, 210 - ((int16_t)f_heartbeatTrace + 30), RED);
//    lastY = (int16_t)f_heartbeatTrace + 30;
//    x += 3;
//    if (x == 238)
//    {
//    	GraphicsFilledRectangle(1, 1, 238, 208, BLACK);
//    	x = 1;
//    }
    un_prev_data = aun_red_buffer[i];
  }

  un_min = 0x3FFFFUL;
  un_max = 0UL;
  for (i = 0U; i < BUFFER_SIZE; i++)
  {
    if (un_min > aun_red_buffer[i])
    {
      un_min = aun_red_buffer[i];    //update signal min for next cycle using values from this cycle
    }
    if (un_max < aun_red_buffer[i])
    {
      un_max = aun_red_buffer[i];    //update signal max for next cycle using values from this cycle
    }
  }

  // calculate heart rate and SpO2 after BUFFER_SIZE samples (ST seconds of samples) using Robert's method
  rf_heart_rate_and_oxygen_saturation(aun_ir_buffer, BUFFER_SIZE, aun_red_buffer, &n_spo2, &ch_spo2_valid, &n_heart_rate, &ch_hr_valid, &ratio, &correl);


  if (ch_hr_valid && ch_spo2_valid)
  {
	  *finger_on = 1;
	  *spo2_mean = n_spo2_sum/num;
	  *heart_rate_mean = n_heart_rate_sum/num;
	  if (HAL_GetTick()-last_time > 10000){
//		  *spo2_mean = n_spo2_sum/num;
//		  *heart_rate_mean = n_heart_rate_sum/num;
//		  debug_printf(">>>>>>>>>>>>SPO2: %f , Heart Rate: %d\r\n", *spo2_mean, *heart_rate_mean);
		  num = 0;
		  n_spo2_sum = 0;
		  n_heart_rate_sum = 0;
		  last_time = HAL_GetTick();
	  }

	  n_spo2_sum += n_spo2;
	  n_heart_rate_sum += n_heart_rate;
	  num += 1;
//	  debug_printf("SPO2: %f , Heart Rate: %d\r\n", n_spo2, n_heart_rate);
  }
  else
  {
	  *finger_on = 0;
//	  debug_printf("..........................\r\n");
  }
}

