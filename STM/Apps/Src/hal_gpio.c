// ----------------------------------------------------------------------------
//         AZRY Microcontroller Software Support 
// ----------------------------------------------------------------------------
// Copyright (c) 2009, AZRY Corporation
//
// All rights reserved.
//
// File Name          : stm32f4_gpio.c
// Author             : Irakli Khokhiashvili 
// Date First Issued  : 08/03/2016 :  Version V01.01
// Description        : Device source file
// ----------------------------------------------------------------------------

#include "global.h"
#include "hal_gpio.h"

//------------------------------------------------------------------------------
//         Internal definitions
//------------------------------------------------------------------------------
void (*gpio_irq_cbf[16])(void);  // gpio interrupt function pointer 


//------------------------------------------------------------------------------
//         internal Functions
//------------------------------------------------------------------------------

//void EXTI0_IRQHandler(void){ (*gpio_irq_cbf[0])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_0);}
void EXTI1_IRQHandler(void){ (*gpio_irq_cbf[1])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_1);}
void EXTI2_IRQHandler(void){ (*gpio_irq_cbf[2])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);}
void EXTI3_IRQHandler(void){ (*gpio_irq_cbf[3])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);}
void EXTI4_IRQHandler(void){ (*gpio_irq_cbf[4])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);}

void EXTI9_5_IRQHandler(void)
{ 
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != RESET) { (*gpio_irq_cbf[5])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5); }
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6) != RESET) { (*gpio_irq_cbf[6])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_6); }
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_7) != RESET) { (*gpio_irq_cbf[7])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_7); }
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_8) != RESET) { (*gpio_irq_cbf[8])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_8); }
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9) != RESET) { (*gpio_irq_cbf[9])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_9); }
}

void EXTI15_10_IRQHandler(void)
{ 
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_10) != RESET) { (*gpio_irq_cbf[10])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_10); }
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_11) != RESET) { (*gpio_irq_cbf[11])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_11); }
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) != RESET) { (*gpio_irq_cbf[12])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_12); }
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != RESET) { (*gpio_irq_cbf[13])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_13); }
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_14) != RESET) { (*gpio_irq_cbf[14])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_14); }
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_15) != RESET) { (*gpio_irq_cbf[15])(); __HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_15); }
}


//------------------------------------------------------------------------------
//         GPIO Local Functions
//------------------------------------------------------------------------------
GPIO_TypeDef* dev_gpio_id_port(UINT8 gpio_id)
{
		switch(gpio_id)
		{
				case GPIO_PA : return GPIOA;
				case GPIO_PB : return GPIOB;
				case GPIO_PC : return GPIOC;
				case GPIO_PD : return GPIOD;
				case GPIO_PE : return GPIOE;
			
#ifdef	GPIOF			
				case GPIO_PF : return GPIOF; 
#endif
			
#ifdef	GPIOG			
				case GPIO_PG : return GPIOG;
#endif
			
#ifdef	GPIOH			
				case GPIO_PH : return GPIOH;
#endif
			
#ifdef	GPIOI			
				case GPIO_PI : return GPIOI;
#endif

		}

		return (GPIO_TypeDef*)0;	
}

UINT16 dev_gpio_id_pin(UINT8 gpio_id)
{
		switch(gpio_id)
		{
				case GPIO_Pin_0 : return GPIO_PIN_0;
				case GPIO_Pin_1 : return GPIO_PIN_1;
				case GPIO_Pin_2 : return GPIO_PIN_2;
				case GPIO_Pin_3 : return GPIO_PIN_3;
				case GPIO_Pin_4 : return GPIO_PIN_4;
				case GPIO_Pin_5 : return GPIO_PIN_5;
				case GPIO_Pin_6 : return GPIO_PIN_6;
				case GPIO_Pin_7 : return GPIO_PIN_7;
				case GPIO_Pin_8 : return GPIO_PIN_8;
				case GPIO_Pin_9 : return GPIO_PIN_9;
				case GPIO_Pin_10 : return GPIO_PIN_10;
				case GPIO_Pin_11 : return GPIO_PIN_11;
				case GPIO_Pin_12 : return GPIO_PIN_12;
				case GPIO_Pin_13 : return GPIO_PIN_13;
				case GPIO_Pin_14 : return GPIO_PIN_14;
				case GPIO_Pin_15 : return GPIO_PIN_15;
		}

		return 0;	
}

int dev_gpio_pin_id(UINT16 pin)
{
		if (pin & 0x0001) return 0;
		if (pin & 0x0002) return 1;
		if (pin & 0x0004) return 2;
		if (pin & 0x0008) return 3;
		if (pin & 0x0010) return 4;
		if (pin & 0x0020) return 5;
		if (pin & 0x0040) return 6;
		if (pin & 0x0080) return 7;
	
		if (pin & 0x0100) return 8;
		if (pin & 0x0200) return 9;
		if (pin & 0x0400) return 10;
		if (pin & 0x0800) return 11;
		if (pin & 0x1000) return 12;
		if (pin & 0x2000) return 13;
		if (pin & 0x4000) return 14;
		if (pin & 0x8000) return 15;

		return -1;	
}

//------------------------------------------------------------------------------
//         GPIO Init Functions
//------------------------------------------------------------------------------
UINT8 dev_gpio_init_rcc(UINT8 gpio_id)
{
		switch(gpio_id)
		{
				case GPIO_PA : __HAL_RCC_GPIOA_CLK_ENABLE(); break;
				case GPIO_PB : __HAL_RCC_GPIOB_CLK_ENABLE(); break;
				case GPIO_PC : __HAL_RCC_GPIOC_CLK_ENABLE(); break;
				case GPIO_PD : __HAL_RCC_GPIOD_CLK_ENABLE(); break;
				case GPIO_PE : __HAL_RCC_GPIOE_CLK_ENABLE(); break;

#ifdef	GPIOF			
				case GPIO_PF : __HAL_RCC_GPIOF_CLK_ENABLE(); break;
#endif
			
#ifdef	GPIOG			
				case GPIO_PG : __HAL_RCC_GPIOG_CLK_ENABLE(); break;
#endif
			
#ifdef	GPIOH			
				case GPIO_PH : __HAL_RCC_GPIOH_CLK_ENABLE(); break;
#endif
			
#ifdef	GPIOI			
				case GPIO_PI : __HAL_RCC_GPIOI_CLK_ENABLE(); break;
#endif
			
				default : TRACE_GERROR("Unknow GPIO !!!");
		}
		
		return RET_OK;
}

UINT8 dev_gpio_init_rcc_port(GPIO_TypeDef* gpio)
{
		if (gpio == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
		if (gpio == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
		if (gpio == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
		if (gpio == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
		if (gpio == GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();

#ifdef	GPIOF			
		if (gpio == GPIOF) __HAL_RCC_GPIOF_CLK_ENABLE();
#endif
			
#ifdef	GPIOG			
		if (gpio == GPIOG) __HAL_RCC_GPIOG_CLK_ENABLE();
#endif
			
#ifdef	GPIOH			
		if (gpio == GPIOH) __HAL_RCC_GPIOH_CLK_ENABLE();
#endif
			
#ifdef	GPIOI			
		if (gpio == GPIOI) __HAL_RCC_GPIOI_CLK_ENABLE();
#endif
			
		return RET_OK;
}

UINT8 dev_gpio_init_mode(GPIO_InitTypeDef* init, UINT8 gpio_mode)
{
	
		switch(gpio_mode)
		{
				case GPIO_MODE_IN : 
				case GPIO_MODE_IN_FLOAT : 	init->Mode = GPIO_MODE_INPUT;
																		init->Pull = GPIO_NOPULL; break;

				case GPIO_MODE_IN_UP : 			init->Mode = GPIO_MODE_INPUT;
																		init->Pull = GPIO_PULLUP; break;
				
				case GPIO_MODE_IN_DOWN : 		init->Mode = GPIO_MODE_INPUT;
																		init->Pull = GPIO_PULLDOWN; break;

				case GPIO_MODE_OUT : 
				case GPIO_MODE_OUT_PP : 		init->Mode 	= GPIO_MODE_OUTPUT_PP;
																		init->Pull 	= GPIO_NOPULL; break;

				case GPIO_MODE_OUT_OD : 		init->Mode 	= GPIO_MODE_OUTPUT_OD;
																		init->Pull 	= GPIO_NOPULL; break;
#ifdef GPIO_MODE_AF_INPUT				
				case GPIO_MODE_ALF : 
				case GPIO_MODE_ALF_IN : 		init->Mode 	= GPIO_MODE_AF_INPUT;
																		init->Pull 	= GPIO_NOPULL; break;
#endif				
				
				case GPIO_MODE_ALF_PP : 		init->Mode 	= GPIO_MODE_AF_PP;
																		init->Pull 	= GPIO_NOPULL; break;

				case GPIO_MODE_ALF_OD : 		init->Mode 	= GPIO_MODE_AF_OD;
																		init->Pull 	= GPIO_NOPULL; break;

				case GPIO_MODE_AN : 				init->Mode 	= GPIO_MODE_ANALOG;
																		init->Pull 	= GPIO_NOPULL; break;

				default : 									return TRACE_GERROR("Unknow GPIO Mode !!!");
				
		};
		
		return RET_OK;
}

UINT8 dev_gpio_init_speed(GPIO_InitTypeDef* init, UINT8 gpio_speed)
{
		switch(gpio_speed)
		{
				case GPIO_PIN_SPEED_VHIGH : 			init->Speed = GPIO_SPEED_FREQ_HIGH; break;
				case GPIO_PIN_SPEED_HIGH : 				init->Speed = GPIO_SPEED_FREQ_HIGH; break;
				case GPIO_PIN_SPEED_MED : 				init->Speed = GPIO_SPEED_FREQ_MEDIUM; break;
				case GPIO_PIN_SPEED_LOW : 				init->Speed = GPIO_SPEED_FREQ_LOW; break;
			
				default : 									return TRACE_GERROR("Unknow GPIO Speed !!!");
		};

		return RET_OK;
}

UINT8 dev_gpio_deinit(dev_gpio_t* gpio)
{
		HAL_GPIO_DeInit(gpio->port, gpio->pin);
	
		return RET_OK;
}

UINT8 dev_gpio_init(dev_gpio_t* gpio, dev_gpio_init_t* init)
{
		UINT8 ret;
		GPIO_InitTypeDef GPIO_InitStructure;

		hal_driver_set_info(&init->info, &gpio->info);
	
		gpio->port = dev_gpio_id_port(gpio->info.id);
		gpio->pin = init->pin;
	
		GPIO_InitStructure.Pin = gpio->pin; 
	
		ret = dev_gpio_init_rcc(gpio->info.id);
		if (ret) return TRACE_EERROR(ret);
	
		ret = dev_gpio_init_mode(&GPIO_InitStructure, init->mode);
		if (ret) return TRACE_EERROR(ret);
	
		ret = dev_gpio_init_speed(&GPIO_InitStructure, init->speed);
		if (ret) return TRACE_EERROR(ret);
	
	  // EXTI interrupt init
		if (init->irq_cbf)
		{
				switch(init->irq_mode)
				{
						case GPIO_IRQ_RISING : 		GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING; break;
						case GPIO_IRQ_FALLING : 	GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING; break;
						case GPIO_IRQ_CHANGE : 		GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING; break;
				}
		}	
	
		HAL_GPIO_Init(gpio->port, &GPIO_InitStructure);

		HAL_DRIVER_DEBUG(gpio->info.status_in, debug_printf("Init Gpio %s - %d, %X\n\r", gpio->info.name, gpio->info.id, gpio->pin));		

	  // EXTI interrupt init
		if (init->irq_cbf)
		{
				int pin_id = dev_gpio_pin_id(gpio->pin);
			
				if (pin_id < 0) return TRACE_GERROR("Irq Line!!!");
			
				gpio_irq_cbf[pin_id] = init->irq_cbf;
			
				switch(pin_id)
				{
						case 0 : gpio->irq_line = EXTI0_IRQn; break;
						case 1 : gpio->irq_line = EXTI1_IRQn; break;
						case 2 : gpio->irq_line = EXTI2_IRQn; break;
						case 3 : gpio->irq_line = EXTI3_IRQn; break;
						case 4 : gpio->irq_line = EXTI4_IRQn; break;

						case 5 : 
						case 6 : 
						case 7 : 
						case 8 : 
						case 9 : gpio->irq_line = EXTI9_5_IRQn; break;

						case 10 : 
						case 11 : 
						case 12 : 
						case 13 : 
						case 14 : 
						case 15 : gpio->irq_line = EXTI15_10_IRQn; break;
				}
			
				HAL_NVIC_SetPriority((IRQn_Type)gpio->irq_line, (init->irq_prior >> 4) & 0x0F, init->irq_prior & 0x0F);
				HAL_NVIC_EnableIRQ((IRQn_Type)gpio->irq_line);

			
				HAL_DRIVER_DEBUG(gpio->info.status_in, debug_printf("Init Gpio IRQ %s -, %d, %X\n\r", gpio->info.name, gpio->info.id, gpio->irq_line));		
		}	

		return RET_OK;
}

UINT8 dev_gpio_init_simp(dev_gpio_t* gpio, UINT8 gpio_id, UINT16 gpio_pin, UINT8 gpio_mode)
{
		dev_gpio_init_t init;
	
		init.info.id = gpio_id;
		init.info.name = "";
		init.info.status_in = 0; 
		init.info.status_out = 0; 

		init.pin = gpio_pin;
		init.mode = gpio_mode;
		init.speed = 0;

		init.irq_cbf = 0;
		init.irq_mode = 0;
	
		return dev_gpio_init(gpio, &init);
}


//------------------------------------------------------------------------------
//        GPIO Data Functions
//------------------------------------------------------------------------------
UINT8 dev_gpio_get(dev_gpio_t* gpio)
{
		return HAL_GPIO_ReadPin(gpio->port, gpio->pin); 
}

UINT16 dev_gpio_get_data(dev_gpio_t* gpio)
{
		return 0; //HAL_GPIO_ReadPins(gpio->port, gpio->pin); 
}

void dev_gpio_set(dev_gpio_t* gpio, UINT8 val)
{
		if (val) HAL_GPIO_WritePin(gpio->port, gpio->pin, (GPIO_PinState)1); 
				else HAL_GPIO_WritePin(gpio->port, gpio->pin, (GPIO_PinState)0);
}

void dev_gpio_set_data_mask(dev_gpio_t* gpio, UINT16 val, UINT16 mask)
{
			if (val) HAL_GPIO_WritePin(gpio->port, (gpio->pin & mask), (GPIO_PinState)1); 
					else HAL_GPIO_WritePin(gpio->port, (gpio->pin & mask), (GPIO_PinState)0);
}

void dev_gpio_set_data(dev_gpio_t* gpio, UINT16 val)
{
			HAL_GPIO_WritePin(gpio->port, (gpio->pin & ~val), (GPIO_PinState)0);
			HAL_GPIO_WritePin(gpio->port, (gpio->pin & val), (GPIO_PinState)1);
}

void dev_gpio_invert(dev_gpio_t* gpio)
{
		HAL_GPIO_TogglePin(gpio->port, gpio->pin);
}

void dev_gpio_invert_mask(dev_gpio_t* gpio, UINT16 mask)
{
		HAL_GPIO_TogglePin(gpio->port, gpio->pin & mask);
}

//------------------------------------------------------------------------------
//         Manage Functions
//------------------------------------------------------------------------------
void dev_gpio_enable_irq(dev_gpio_t* gpio, UINT8 enable)
{
		if (enable)	HAL_NVIC_EnableIRQ((IRQn_Type)gpio->irq_line);
						else HAL_NVIC_DisableIRQ((IRQn_Type)gpio->irq_line);
}

// GPIO Direction Fast Cahnge
UINT8 dev_gpio_set_mode(dev_gpio_t* gpio, UINT8 gpio_mode, UINT8 gpio_speed)
{
		UINT8 ret;
	
		GPIO_InitTypeDef GPIO_InitStructure;
	
		GPIO_InitStructure.Pin = gpio->pin; 

		ret = dev_gpio_init_mode(&GPIO_InitStructure, gpio_mode);
		if (ret) return TRACE_EERROR(ret);

		ret = dev_gpio_init_speed(&GPIO_InitStructure, gpio_speed);
		if (ret) return TRACE_EERROR(ret);
	
		HAL_GPIO_Init(gpio->port, &GPIO_InitStructure);
	
		HAL_DRIVER_DEBUG(gpio->info.status_in, debug_printf("Change Gpio Mode %s - %d %d\n\r", gpio->info.name, gpio->info.id, gpio_mode));
	
		return RET_OK;
}
