// ----------------------------------------------------------------------------
//         AZRY Microcontroller Software Support
// ----------------------------------------------------------------------------
// Copyright (c) 2009, AZRY Corporation
//
// All rights reserved.
//
// File Name          : stm32f4_gpio.h
// Author             : Irakli Khokhiashvili
// Date First Issued  : 08/03/2016 :  Version V01.01
// Description        : Device configuration file
// ----------------------------------------------------------------------------

#ifndef _STM32_HAL_GPIO_H
#define _STM32_HAL_GPIO_H

#include "global_def.h"
#include "hal_driver_def.h"

#ifdef __cplusplus
extern "C"
{
#endif

	enum
	{
		GPIO_PA,
		GPIO_PB,
		GPIO_PC,
		GPIO_PD,
		GPIO_PE,
		GPIO_PF,
		GPIO_PG,
		GPIO_PH,
		GPIO_PI,
	};

	enum
	{
		GPIO_Pin_0,
		GPIO_Pin_1,
		GPIO_Pin_2,
		GPIO_Pin_3,
		GPIO_Pin_4,
		GPIO_Pin_5,
		GPIO_Pin_6,
		GPIO_Pin_7,
		GPIO_Pin_8,
		GPIO_Pin_9,
		GPIO_Pin_10,
		GPIO_Pin_11,
		GPIO_Pin_12,
		GPIO_Pin_13,
		GPIO_Pin_14,
		GPIO_Pin_15,
	};

	enum
	{
		GPIO_MODE_IN,
		GPIO_MODE_OUT,
		GPIO_MODE_IN_FLOAT,
		GPIO_MODE_IN_DOWN,
		GPIO_MODE_IN_UP,
		GPIO_MODE_OUT_PP,
		GPIO_MODE_OUT_OD,
		GPIO_MODE_ALF,
		GPIO_MODE_ALF_PP,
		GPIO_MODE_ALF_OD,
		GPIO_MODE_ALF_IN,
		GPIO_MODE_AN,
	};

	enum
	{
		GPIO_PIN_SPEED_VHIGH,
		GPIO_PIN_SPEED_HIGH,
		GPIO_PIN_SPEED_MED,
		GPIO_PIN_SPEED_LOW,
	};

	enum
	{
		GPIO_IRQ_OFF,
		GPIO_IRQ_RISING,
		GPIO_IRQ_FALLING,
		GPIO_IRQ_CHANGE,
		GPIO_IRQ_HIGH,
		GPIO_IRQ_LOW,
	};

	typedef struct
	{
		UINT16 pin;
		UINT8 port;
	} dev_gpio_info_t;
	// typedef struct {GPIO_TypeDef* port; UINT16 pin; UINT8 port_id, irq_line;} dev_gpio_t;
	typedef struct
	{
		GPIO_TypeDef *port;
		dev_info_t info;
		UINT16 pin;
		UINT8 irq_line;
	} dev_gpio_t;
	typedef struct
	{
		dev_info_t info;
		UINT16 pin;
		UINT8 mode, speed, irq_mode, irq_prior;
		void (*irq_cbf)(void);
	} dev_gpio_init_t;

	// Initial Functions
	UINT8 dev_gpio_deinit(dev_gpio_t *dev);
	UINT8 dev_gpio_init(dev_gpio_t *dev, dev_gpio_init_t *init);
	UINT8 dev_gpio_init_simp(dev_gpio_t *gpio, UINT8 gpio_id, UINT16 gpio_pin, UINT8 gpio_mode);
	UINT8 dev_gpio_init_rcc_port(GPIO_TypeDef *gpio);

	// Manage Functions
	UINT8 dev_gpio_set_mode(dev_gpio_t *gpio, UINT8 gpio_mode, UINT8 gpio_speed);
	void dev_gpio_enable_irq(dev_gpio_t *gpio, UINT8 enable);

	// Gpio Data Functions
	//////////////////////////////////////////////////////////
	UINT8 dev_gpio_get(dev_gpio_t *gpio);
	UINT16 dev_gpio_get_data(dev_gpio_t *gpio);

	void dev_gpio_set(dev_gpio_t *gpio, UINT8 val);
	void dev_gpio_set_data(dev_gpio_t *gpio, UINT16 val);
	void dev_gpio_set_data_mask(dev_gpio_t *gpio, UINT16 val, UINT16 mask);
	void dev_gpio_invert(dev_gpio_t *gpio);
	void dev_gpio_invert_mask(dev_gpio_t *gpio, UINT16 mask);

	GPIO_TypeDef *dev_gpio_id_port(UINT8 gpio_id);
	UINT16 dev_gpio_id_pin(UINT8 gpio_id);

#ifdef __cplusplus
}
#endif

#endif
