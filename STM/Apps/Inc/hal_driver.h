// ----------------------------------------------------------------------------
//         AZRY Microcontroller Software Support 
// ----------------------------------------------------------------------------
// Copyright (c) 2009, AZRY Corporation
//
// All rights reserved.
//
// File Name          : hal_driver.h
// Author             : Irakli Khokhiashvili 
// Date First Issued  : 08/09/2019 :  Version V01.01
// Description        : Device configuration file
// ----------------------------------------------------------------------------

#ifndef _STM32_HAL_DRIVER_H
#define _STM32_HAL_DRIVER_H

#include "binary.h"
//#include "stm32f1xx_hal.h"
#include "hal_gpio.h"
//#include "stm32f4xx.h"

#ifdef __cplusplus
 extern "C" {
#endif



//typedef struct {UINT16 pin; UINT8 port;} dev_gpio_info_t;
//typedef struct {GPIO_TypeDef* port; UINT16 pin; UINT8 port_id, irq_line;} dev_gpio_t;

//// Initial Functions
//UINT8 dev_gpio_init(dev_gpio_t* gpio, UINT8 port_id, UINT16 gpio_pin, UINT8 gpio_mode);
//UINT8 dev_gpio_init_all(dev_gpio_t* gpio, UINT8 port_id, UINT16 gpio_pin, UINT8 gpio_mode, UINT8 gpio_speed);
//UINT8 dev_gpio_init_irq(dev_gpio_t* gpio, UINT8 irq_line, UINT8 irq_mode, void (*cbf)(void), UINT8 irq_prior);
////UINT8 dev_gpio_init_rcc(dev_gpio_t* gpio);

//UINT8 dev_gpio_init_af(UINT8 port_id, UINT16 gpio_pin, UINT8 af_mode);
//UINT8 dev_gpio_init_an(UINT8 port_id, UINT16 gpio_pin);

//// Main Functions
//UINT16 dev_gpio_get(dev_gpio_t* gpio);
//UINT8 dev_gpio_get_bit(dev_gpio_t* gpio);
//void dev_gpio_set(dev_gpio_t* gpio, UINT8 val);
//void dev_gpio_set_data(dev_gpio_t* gpio, UINT16 val);
//void dev_gpio_set_mask(dev_gpio_t* gpio, UINT16 mask, UINT8 val);
//void dev_gpio_invert(dev_gpio_t* gpio);
//void dev_gpio_invert_mask(dev_gpio_t* gpio, UINT16 mask);

//// Manage Functions
//UINT8 dev_gpio_set_mode(dev_gpio_t* gpio, UINT8 gpio_mode, UINT8 gpio_speed);
//void dev_gpio_irq_enable(dev_gpio_t* gpio, UINT8 enable);





typedef struct {dev_info_t info; UINT8 id, debug;} dev_tim_t;
//typedef struct {dev_info_t info; UINT8 id, debug;} dev_adc_t;
typedef struct {dev_info_t info; UINT8 id, debug;} dev_dac_t;
//typedef struct {dev_info_t info; UINT8 id, debug;} dev_spi_t;
typedef struct {dev_info_t info; UINT8 id, debug;} dev_wdg_t;
typedef struct {dev_info_t info; UINT8 id, debug;} dev_eth_t;
//typedef struct {dev_info_t info; UINT8 id, debug;} dev_gpio_t;
//typedef struct {dev_info_t info; UINT8 id, debug;} dev_uart_t;
typedef struct {dev_info_t info; UINT8 id, debug;} dev_flash_t;

typedef struct {dev_info_t info; UINT8 mode;} dev_tim_init_t;
//typedef struct {dev_info_t info; UINT8 mode;} dev_adc_init_t;
typedef struct {dev_info_t info; UINT8 mode;} dev_dac_init_t;
//typedef struct {dev_info_t info; UINT8 mode;} dev_spi_init_t;
typedef struct {dev_info_t info; UINT8 mode;} dev_wdg_init_t;
typedef struct {dev_info_t info; UINT8 mode;} dev_eth_init_t;
//typedef struct {dev_info_t info; UINT8 mode;} dev_uart_init_t;
//typedef struct {dev_info_t info; UINT8 mode;} dev_gpio_init_t;
typedef struct {dev_info_t info; UINT8 mode;} dev_flash_init_t;



UINT8 dev_tim_init(dev_tim_t* dev, dev_tim_init_t* init);
//UINT8 dev_adc_init(dev_adc_t* dev, dev_adc_init_t* init);
UINT8 dev_dac_init(dev_dac_t* dev, dev_dac_init_t* init);
//UINT8 dev_spi_init(dev_spi_t* dev, dev_spi_init_t* init);
UINT8 dev_wdg_init(dev_wdg_t* dev, dev_wdg_init_t* init);
UINT8 dev_eth_init(dev_eth_t* dev, dev_eth_init_t* init);
//UINT8 dev_gpio_init(dev_gpio_t* dev, dev_gpio_init_t* init);
//UINT8 dev_uart_init(dev_uart_t* dev, dev_uart_init_t* init);
UINT8 dev_flash_init(dev_flash_t* dev, dev_flash_init_t* init);


UINT8 dev_tim_deinit(dev_tim_t* dev);
//UINT8 dev_adc_deinit(dev_adc_t* dev);
UINT8 dev_dac_deinit(dev_dac_t* dev);
//UINT8 dev_spi_deinit(dev_spi_t* dev);
UINT8 dev_wdg_deinit(dev_wdg_t* dev);
UINT8 dev_eth_deinit(dev_eth_t* dev);

//UINT8 dev_gpio_deinit(dev_gpio_t* dev);
//UINT8 dev_uart_deinit(dev_uart_t* dev);
UINT8 dev_flash_deinit(dev_flash_t* dev);


//int dev_dac_write(dev_uart_t* dev, UINT8* pData, int nData);
//int dev_eth_write(dev_uart_t* dev, UINT8* pData, int nData);
////int dev_spi_write(dev_uart_t* dev, UINT8* pData, int nData);
////int dev_uart_write(dev_uart_t* dev, UINT8* pData, int nData);
//int dev_flash_write(dev_uart_t* dev, UINT8* pData, int nData);

////int dev_adc_read(dev_uart_t* dev, UINT8* pData, int nData);
//int dev_eth_read(dev_uart_t* dev, UINT8* pData, int nData);
////int dev_spi_read(dev_uart_t* dev, UINT8* pData, int nData);
////int dev_uart_read(dev_uart_t* dev, UINT8* pData, int nData);
//int dev_flash_read(dev_uart_t* dev, UINT8* pData, int nData);



//// Gpio Data Functions
////////////////////////////////////////////////////////////
//UINT8 dev_gpio_get(dev_gpio_t* gpio);
//UINT16 dev_gpio_get_data(dev_gpio_t* gpio);

//void dev_gpio_set(dev_gpio_t* gpio, UINT8 val);
//void dev_gpio_set_data(dev_gpio_t* gpio, UINT16 val);
//void dev_gpio_set_mask(dev_gpio_t* gpio, UINT8 val, UINT16 mask);
//void dev_gpio_set_invert(dev_gpio_t* gpio);
//void dev_gpio_set_invert_mask(dev_gpio_t* gpio, UINT16 mask);





#ifdef __cplusplus
}
#endif


#endif
