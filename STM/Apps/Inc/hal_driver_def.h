// ----------------------------------------------------------------------------
//         AZRY Microcontroller Software Support 
// ----------------------------------------------------------------------------
// Copyright (c) 2009, AZRY Corporation
//
// All rights reserved.
//
// File Name          : hal_driver_def.h
// Author             : Irakli Khokhiashvili 
// Date First Issued  : 08/09/2019 :  Version V01.01
// Description        : Device configuration file
// ----------------------------------------------------------------------------

#ifndef _STM32_HAL_DRIVER_DEF_H
#define _STM32_HAL_DRIVER_DEF_H



#ifdef __cplusplus
 extern "C" {
#endif

#define HAL_DRIVER_DEBUG_ENABLE	 
#define HAL_NETWORK_DEBUG_ENABLE	 
	 
#ifdef HAL_DRIVER_DEBUG_ENABLE
#define HAL_DRIVER_DEBUG(a, b) if(a) if (*a) b
#else
#define HAL_DRIVER_DEBUG(a, b) {}
#endif

#ifdef HAL_NETWORK_DEBUG_ENABLE
#define HAL_NETWORK_DEBUG(a, b) if(a) if (*a) b
#else
#define HAL_NETWORK_DEBUG(a, b) {}
#endif
	
	 
enum {
				HAL_DMA_PRIOR_LOW,
				HAL_DMA_PRIOR_MED,
				HAL_DMA_PRIOR_HIGH,
				HAL_DMA_PRIOR_VHIGH,
			};	 

enum {
				HAL_DMA_MODE_OFF,
				HAL_DMA_MODE_NORMAL,
				HAL_DMA_MODE_CIRCULAR,
			};	 

enum {
				HAL_DEFAULT_MODE_SYNC,
				HAL_DEFAULT_MODE_IRQ,
				HAL_DEFAULT_MODE_DMA,
				HAL_DEFAULT_MODE_DMA_IRQ,
				HAL_DEFAULT_MODE_CDMA,
				HAL_DEFAULT_MODE_CDMA_IRQ,
			};	 


typedef struct {
									unsigned char id; 
									unsigned int* status_in;
									unsigned int* status_out; 
									unsigned char rx_mode; 
									unsigned char tx_mode; 
									char* name;
									char* debug;
	
								} dev_info_t;

typedef struct { 
									int index, size; 
									unsigned char* buf;
	
								} dev_info_dma_t;

typedef struct { 
									unsigned int size; 
									unsigned int priority; 
									unsigned char irq_priority;
									void (*irq_cbf_half)(void *hdma);
									void (*irq_cbf_full)(void *hdma);	
									unsigned char dma_id;
									unsigned char dma_cn;
									unsigned char mode;
	
								} dev_init_dma_t;


void hal_driver_set_info(dev_info_t* info_1, dev_info_t* info_2);
unsigned char hal_driver_set_dma_irq(int dma_id, int id, void* irq_data);

unsigned char mem_alloc(unsigned char** pData, unsigned int nData, char* name);


#ifdef __cplusplus
}
#endif


#endif
