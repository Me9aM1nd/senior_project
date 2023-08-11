// ----------------------------------------------------------------------------
//         AZRY Microcontroller Software Support 
// ----------------------------------------------------------------------------
// Copyright (c) 2009, AZRY Corporation
//
// All rights reserved.
//
// File Name          : hal_driver_def.c
// Author             : Irakli Khokhiashvili 
// Date First Issued  : 08/09/2019 :  Version V01.01
// Description        : Device source file
// ----------------------------------------------------------------------------

//#include "stm32f1xx_hal.h"
#include "hal_driver_def.h"
#include "global.h"

//static void (*dma_irq_cbf_half[16])(void* dma);
//static void (*dma_irq_cbf_full[16])(void* dma);

static void* dma_1_irq_data[16];
static void* dma_2_irq_data[16];



void hal_driver_set_info(dev_info_t* info_1, dev_info_t* info_2)
{
		info_2->id = info_1->id;
		info_2->status_in = info_1->status_in;
		info_2->status_out = info_1->status_out;
		info_2->name = info_1->name;
	
		info_2->rx_mode = HAL_DEFAULT_MODE_SYNC;
		info_2->tx_mode = HAL_DEFAULT_MODE_SYNC;
}


unsigned char hal_driver_set_dma_irq(int dma_id, int id, void* irq_data)
{
		if (id >= 16) return TRACE_GERROR("Dma ID!!!");
	
		if (dma_id == 0) dma_1_irq_data[id] = irq_data;
		if (dma_id == 1) dma_2_irq_data[id] = irq_data;
	
		return RET_OK;
}


//void DMA1_Channel1_IRQHandler(void)
//{
//		HAL_DMA_IRQHandler((DMA_HandleTypeDef*)dma_1_irq_data[0]);
//}

//void DMA1_Channel2_IRQHandler(void)
//{
//		HAL_DMA_IRQHandler((DMA_HandleTypeDef*)dma_1_irq_data[1]);
//}

//void DMA1_Channel3_IRQHandler(void)
//{
//		HAL_DMA_IRQHandler((DMA_HandleTypeDef*)dma_1_irq_data[2]);
//}

//void DMA1_Channel4_IRQHandler(void)
//{
//		HAL_DMA_IRQHandler((DMA_HandleTypeDef*)dma_1_irq_data[3]);
//}

//void DMA1_Channel5_IRQHandler(void)
//{
//		HAL_DMA_IRQHandler((DMA_HandleTypeDef*)dma_1_irq_data[4]);
//}

//void DMA1_Channel6_IRQHandler(void)
//{
//		HAL_DMA_IRQHandler((DMA_HandleTypeDef*)dma_1_irq_data[5]);
//}

//void DMA1_Channel7_IRQHandler(void)
//{
//		HAL_DMA_IRQHandler((DMA_HandleTypeDef*)dma_1_irq_data[6]);
//}


unsigned char mem_alloc(unsigned char** pData, unsigned int nData, char* name)
{
		if (*pData) return TRACE_GERROR("Malloc Data!!!"); 
	
    *pData = malloc(nData); 
	
		debug_printf("%s Malloc >>> %u %u\n\r", name, *pData, nData);

		if (*pData == NULL) return TRACE_GERROR("Malloc Size!!!"); 
	
		return RET_OK;
}


//void DMA1_Stream0_IRQHandler(void)  
//{
//		void HAL_DMA_IRQHandler(DMA_HandleTypeDef *hdma)

//				 if(DMA_GetITStatus(DMA1_Stream0, DMA_IT_TCIF0)) {(*dma_irq_cbf_full[0])(dma_irq_data[0]); DMA_ClearITPendingBit(DMA1_Stream0, DMA_IT_TCIF0);}
//		else if(DMA_GetITStatus(DMA1_Stream0, DMA_IT_HTIF0)) {(*dma_irq_cbf_half[0])(dma_irq_data[0]); DMA_ClearITPendingBit(DMA1_Stream0, DMA_IT_HTIF0);}
//}

//void DMA1_Stream1_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA1_Stream1, DMA_IT_TCIF1)) {(*dma_irq_cbf_full[1])(dma_irq_data[1]); DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_TCIF1);}
//		else if(DMA_GetITStatus(DMA1_Stream1, DMA_IT_HTIF1)) {(*dma_irq_cbf_half[1])(dma_irq_data[1]); DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_HTIF1);}
//}

//void DMA1_Stream2_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA1_Stream2, DMA_IT_TCIF2)) {(*dma_irq_cbf_full[2])(dma_irq_data[2]); DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_TCIF2);}
//		else if(DMA_GetITStatus(DMA1_Stream2, DMA_IT_HTIF2)) {(*dma_irq_cbf_half[2])(dma_irq_data[2]); DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_HTIF2);}
//}

//void DMA1_Stream3_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA1_Stream3, DMA_IT_TCIF3)) {(*dma_irq_cbf_full[3])(dma_irq_data[3]); DMA_ClearITPendingBit(DMA1_Stream3, DMA_IT_TCIF3);}
//		else if(DMA_GetITStatus(DMA1_Stream3, DMA_IT_HTIF3)) {(*dma_irq_cbf_half[3])(dma_irq_data[3]); DMA_ClearITPendingBit(DMA1_Stream3, DMA_IT_HTIF3);}
//}

//void DMA1_Stream4_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA1_Stream4, DMA_IT_TCIF4)) {(*dma_irq_cbf_full[4])(dma_irq_data[4]); DMA_ClearITPendingBit(DMA1_Stream4, DMA_IT_TCIF4);}
//		else if(DMA_GetITStatus(DMA1_Stream4, DMA_IT_HTIF4)) {(*dma_irq_cbf_half[4])(dma_irq_data[4]); DMA_ClearITPendingBit(DMA1_Stream4, DMA_IT_HTIF4);}
//}

//void DMA1_Stream5_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA1_Stream5, DMA_IT_TCIF5)) {(*dma_irq_cbf_full[5])(dma_irq_data[5]); DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_TCIF5);}
//		else if(DMA_GetITStatus(DMA1_Stream5, DMA_IT_HTIF5)) {(*dma_irq_cbf_half[5])(dma_irq_data[5]); DMA_ClearITPendingBit(DMA1_Stream5, DMA_IT_HTIF5);}
//}

//void DMA1_Stream6_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA1_Stream6, DMA_IT_TCIF6)) {(*dma_irq_cbf_full[6])(dma_irq_data[6]); DMA_ClearITPendingBit(DMA1_Stream6, DMA_IT_TCIF6);}
//		else if(DMA_GetITStatus(DMA1_Stream6, DMA_IT_HTIF6)) {(*dma_irq_cbf_half[6])(dma_irq_data[6]); DMA_ClearITPendingBit(DMA1_Stream6, DMA_IT_HTIF6);}
//}

//void DMA1_Stream7_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA1_Stream7, DMA_IT_TCIF7)) {(*dma_irq_cbf_full[7])(dma_irq_data[7]); DMA_ClearITPendingBit(DMA1_Stream7, DMA_IT_TCIF7);}
//		else if(DMA_GetITStatus(DMA1_Stream7, DMA_IT_HTIF7)) {(*dma_irq_cbf_half[7])(dma_irq_data[7]); DMA_ClearITPendingBit(DMA1_Stream7, DMA_IT_HTIF7);}
//}


//void DMA2_Stream0_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0)) {(*dma_irq_cbf_full[8])(dma_irq_data[8]); DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);}
//		else if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_HTIF0)) {(*dma_irq_cbf_half[8])(dma_irq_data[8]); DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_HTIF0);}
//}

//void DMA2_Stream1_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA2_Stream1, DMA_IT_TCIF1)) {(*dma_irq_cbf_full[9])(dma_irq_data[9]); DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_TCIF1);}
//		else if(DMA_GetITStatus(DMA2_Stream1, DMA_IT_HTIF1)) {(*dma_irq_cbf_half[9])(dma_irq_data[9]); DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_HTIF1);}
//}

//void DMA2_Stream2_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA2_Stream2, DMA_IT_TCIF2)) {(*dma_irq_cbf_full[10])(dma_irq_data[10]); DMA_ClearITPendingBit(DMA2_Stream2, DMA_IT_TCIF2);}
//		else if(DMA_GetITStatus(DMA2_Stream2, DMA_IT_HTIF2)) {(*dma_irq_cbf_half[10])(dma_irq_data[10]); DMA_ClearITPendingBit(DMA2_Stream2, DMA_IT_HTIF2);}
//}

//void DMA2_Stream3_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA2_Stream3, DMA_IT_TCIF3)) {(*dma_irq_cbf_full[11])(dma_irq_data[11]); DMA_ClearITPendingBit(DMA2_Stream3, DMA_IT_TCIF3);}
//		else if(DMA_GetITStatus(DMA2_Stream3, DMA_IT_HTIF3)) {(*dma_irq_cbf_half[11])(dma_irq_data[11]); DMA_ClearITPendingBit(DMA2_Stream3, DMA_IT_HTIF3);}
//}

//void DMA2_Stream4_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA2_Stream4, DMA_IT_TCIF4)) {(*dma_irq_cbf_full[12])(dma_irq_data[12]); DMA_ClearITPendingBit(DMA2_Stream4, DMA_IT_TCIF4);}
//		else if(DMA_GetITStatus(DMA2_Stream4, DMA_IT_HTIF4)) {(*dma_irq_cbf_half[12])(dma_irq_data[12]); DMA_ClearITPendingBit(DMA2_Stream4, DMA_IT_HTIF4);}
//}

//void DMA2_Stream5_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA2_Stream5, DMA_IT_TCIF5)) {(*dma_irq_cbf_full[13])(dma_irq_data[13]); DMA_ClearITPendingBit(DMA2_Stream5, DMA_IT_TCIF5);}
//		else if(DMA_GetITStatus(DMA2_Stream5, DMA_IT_HTIF5)) {(*dma_irq_cbf_half[13])(dma_irq_data[13]); DMA_ClearITPendingBit(DMA2_Stream5, DMA_IT_HTIF5);}
//}

//void DMA2_Stream6_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA2_Stream6, DMA_IT_TCIF6)) {(*dma_irq_cbf_full[14])(dma_irq_data[14]); DMA_ClearITPendingBit(DMA2_Stream6, DMA_IT_TCIF6);}
//		else if(DMA_GetITStatus(DMA2_Stream6, DMA_IT_HTIF6)) {(*dma_irq_cbf_half[14])(dma_irq_data[14]); DMA_ClearITPendingBit(DMA2_Stream6, DMA_IT_HTIF6);}
//}

//void DMA2_Stream7_IRQHandler(void)  
//{
//				 if(DMA_GetITStatus(DMA2_Stream7, DMA_IT_TCIF7)) {(*dma_irq_cbf_full[15])(dma_irq_data[15]); DMA_ClearITPendingBit(DMA2_Stream7, DMA_IT_TCIF7);}
//		else if(DMA_GetITStatus(DMA2_Stream7, DMA_IT_HTIF7)) {(*dma_irq_cbf_half[15])(dma_irq_data[15]); DMA_ClearITPendingBit(DMA2_Stream7, DMA_IT_HTIF7);}
//}
