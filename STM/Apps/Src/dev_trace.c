// ----------------------------------------------------------------------------
//         AZRY Microcontroller Software Support 
// ----------------------------------------------------------------------------
// Copyright (c) 2009, AZRY Corporation
//
// All rights reserved.
//
// ----------------------------------------------------------------------------

//#include "global_def.h"
#include "stdarg.h"
#include "dev_trace.h"

enum
{
		TRACE_SPI_MOSI,
		TRACE_SPI_SCK,
		TRACE_SPI_NSS,
		TRACE_SPI_NUMBER
};

//------------------------------------------------------------------------------
//         Global Variables
//------------------------------------------------------------------------------
//#if defined(DEBUG_SPI_GPIO_PORT)
//static const UINT8 gpio_port[] = DEBUG_SPI_GPIO_PORT;
//#else
//#error DEBUG_SPI_GPIO_PORT - Not Defined!!!
//#endif

//#ifdef DEBUG_SPI_GPIO_PIN
//static const UINT16 gpio_pin[] = DEBUG_SPI_GPIO_PIN;
//#else
//#error DEBUG_SPI_GPIO_PIN - Not Defined!!!
//#endif

#define HB2HEX(a)    (a / 10)? (a + 0x41 - 10):  (a + 0x30)

static UINT8 trace_ready = 0;
static UINT8 trace_error_id = 0;

static dev_gpio_t trace_spi[TRACE_SPI_NUMBER]; 



//------------------------------------------------------------------------------
//         Local functions
//------------------------------------------------------------------------------
void dev_trace_send_byte_int(UINT8 b)
{
		UINT8 i; 

		for (i=0; i<8; i++)
		{
				dev_gpio_set(&trace_spi[TRACE_SPI_MOSI], b & 0x80); 
//				dev_gpio_set(&trace_spi[TRACE_SPI_MOSI], b & 0x80); 
				dev_gpio_set(&trace_spi[TRACE_SPI_SCK], 1); 
//				dev_gpio_set(&trace_spi[TRACE_SPI_SCK], 1); 
				dev_gpio_set(&trace_spi[TRACE_SPI_SCK], 0); 
//				dev_gpio_set(&trace_spi[TRACE_SPI_SCK], 0); 
//	HAL_GPIO_WritePin(trace_spi[TRACE_SPI_SCK].port, trace_spi[TRACE_SPI_SCK].pin, b & 0x80);
//	HAL_GPIO_WritePin(trace_spi[TRACE_SPI_MOSI].port, trace_spi[TRACE_SPI_MOSI].pin, 1);
//	HAL_GPIO_WritePin(trace_spi[TRACE_SPI_MOSI].port, trace_spi[TRACE_SPI_MOSI].pin, 0);
			
				b = b << 1;
		}
}

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------
UINT8 dev_trace_init(dev_trace_init_t* init)
{
		UINT8 ret;


		ret = dev_gpio_init_simp(&trace_spi[TRACE_SPI_MOSI], init->mosi.port, init->mosi.pin, GPIO_MODE_OUTPUT_PP);
		if (ret) return TRACE_EERROR(ret);
		ret = dev_gpio_init_simp(&trace_spi[TRACE_SPI_SCK], init->sck.port, init->sck.pin, GPIO_MODE_OUTPUT_PP);
		if (ret) return TRACE_EERROR(ret);
		ret = dev_gpio_init_simp(&trace_spi[TRACE_SPI_NSS], init->nss.port, init->nss.pin, GPIO_MODE_OUTPUT_PP);
		if (ret) return TRACE_EERROR(ret);
	
//	  GPIO_InitTypeDef GPIO_InitStruct = {0};


//	__HAL_RCC_GPIOA_CLK_ENABLE();
//  __HAL_RCC_GPIOB_CLK_ENABLE();

//		trace_spi[TRACE_SPI_MOSI].pin = GPIO_PIN_5;
//		trace_spi[TRACE_SPI_MOSI].port = GPIOB;
//	GPIO_InitStruct.Pin = trace_spi[TRACE_SPI_MOSI].pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
//  HAL_GPIO_Init(trace_spi[TRACE_SPI_MOSI].port, &GPIO_InitStruct);
//	
//		trace_spi[TRACE_SPI_SCK].pin = GPIO_PIN_4;
//		trace_spi[TRACE_SPI_SCK].port =  GPIOA;
//	GPIO_InitStruct.Pin = trace_spi[TRACE_SPI_SCK].pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
//  HAL_GPIO_Init(trace_spi[TRACE_SPI_SCK].port, &GPIO_InitStruct);
//		
//	trace_spi[TRACE_SPI_NSS].pin = GPIO_PIN_12;
//	trace_spi[TRACE_SPI_NSS].port = GPIOA;
//	GPIO_InitStruct.Pin = trace_spi[TRACE_SPI_NSS].pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
//  HAL_GPIO_Init(trace_spi[TRACE_SPI_NSS].port, &GPIO_InitStruct);	

//		trace_spi[TRACE_SPI_MOSI].pin = GPIO_PIN_0;
//		trace_spi[TRACE_SPI_MOSI].port = GPIOA;
//	GPIO_InitStruct.Pin = trace_spi[TRACE_SPI_MOSI].pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
//  HAL_GPIO_Init(trace_spi[TRACE_SPI_MOSI].port, &GPIO_InitStruct);
//	
//		trace_spi[TRACE_SPI_SCK].pin = GPIO_PIN_1;
//		trace_spi[TRACE_SPI_SCK].port =  GPIOA;
//	GPIO_InitStruct.Pin = trace_spi[TRACE_SPI_SCK].pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
//  HAL_GPIO_Init(trace_spi[TRACE_SPI_SCK].port, &GPIO_InitStruct);
//		
//	trace_spi[TRACE_SPI_NSS].pin = GPIO_PIN_2;
//	trace_spi[TRACE_SPI_NSS].port = GPIOA;
//	GPIO_InitStruct.Pin = trace_spi[TRACE_SPI_NSS].pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
//  HAL_GPIO_Init(trace_spi[TRACE_SPI_NSS].port, &GPIO_InitStruct);	
	
//	HAL_GPIO_WritePin(trace_spi[TRACE_SPI_NSS].port, trace_spi[TRACE_SPI_NSS].pin, 1);
//	HAL_GPIO_WritePin(trace_spi[TRACE_SPI_SCK].port, trace_spi[TRACE_SPI_SCK].pin, 0);
//	HAL_GPIO_WritePin(trace_spi[TRACE_SPI_MOSI].port, trace_spi[TRACE_SPI_MOSI].pin, 0);
		dev_gpio_set(&trace_spi[TRACE_SPI_NSS], 1);
		dev_gpio_set(&trace_spi[TRACE_SPI_SCK], 0);
		dev_gpio_set(&trace_spi[TRACE_SPI_MOSI], 0);

		trace_ready = 1;	

		return RET_OK;
}

// Send one Byte 
void dev_trace_send_byte(UINT8 b)
{
	if (trace_ready == 0) return;

//		dev_gpio_set(&trace_spi[TRACE_SPI_NSS], 0);
		HAL_GPIO_WritePin(trace_spi[TRACE_SPI_NSS].port, trace_spi[TRACE_SPI_NSS].pin, 0);
		dev_trace_send_byte_int(b);
//		dev_gpio_set(&trace_spi[TRACE_SPI_NSS], 1);
	HAL_GPIO_WritePin(trace_spi[TRACE_SPI_NSS].port, trace_spi[TRACE_SPI_NSS].pin, 1);
//		HAL_GPIO_WritePin(trace_spi[TRACE_SPI_SCK].port, trace_spi[TRACE_SPI_SCK].pin, 0);
//	HAL_GPIO_WritePin(trace_spi[TRACE_SPI_MOSI].port, trace_spi[TRACE_SPI_MOSI].pin, 0);
}

// Send data buffer
void dev_trace_send_buf(UINT8* pData, UINT16 nData)
{
		UINT16 i;

		if (trace_ready == 0) return;

		dev_gpio_set(&trace_spi[TRACE_SPI_NSS], 0);
//	HAL_GPIO_WritePin(trace_spi[TRACE_SPI_NSS].port, trace_spi[TRACE_SPI_NSS].pin, 0);
		for (i=0; i<nData; i++) dev_trace_send_byte(pData[i]);
		dev_gpio_set(&trace_spi[TRACE_SPI_NSS], 1);
//	HAL_GPIO_WritePin(trace_spi[TRACE_SPI_NSS].port, trace_spi[TRACE_SPI_NSS].pin, 1);
//		HAL_GPIO_WritePin(trace_spi[TRACE_SPI_SCK].port, trace_spi[TRACE_SPI_SCK].pin, 0);
//	HAL_GPIO_WritePin(trace_spi[TRACE_SPI_MOSI].port, trace_spi[TRACE_SPI_MOSI].pin, 0);
}

// Get Trace error
uint8_t dev_trace_get_error(uint8_t error_value, char* file_name, uint32_t file_line)
{
		if (error_value == RET_OK) return RET_OK;
	
		debug_printf("EE> %d at %s:%d\n\r", error_value, file_name, file_line); 

		return error_value;
}

// Generate Trace error
uint8_t dev_trace_generate_error(char* error_name, char* file_name, uint32_t file_line)
{
		trace_error_id++;
		if (trace_error_id < 100) trace_error_id = 100;
		if (trace_error_id >= 200) trace_error_id = 100;

		debug_printf("GE> %d %s at %s:%d\n\r", trace_error_id, error_name, file_name, file_line);

		return trace_error_id;
}

// Generate Trace error
UINT8 dev_trace_generate_verror(char* error_name, UINT32 error_value, char* file_name, UINT32 file_line)
{
		trace_error_id++;
		if (trace_error_id < 100) trace_error_id = 100;
		if (trace_error_id >= 200) trace_error_id = 100;

		debug_printf("VE> %d %d %s at %s:%d\n\r", trace_error_id, error_value, error_name, file_name, file_line); 

		return trace_error_id;
}

// Custom Printf function
//////////////////////////////////////////////////////////////////////////
void debug_printf_char(UINT8 c)
{
    if (c < ' ') 
    {    
        dev_trace_send_byte('~');
        dev_trace_send_byte(HB2HEX(c / 0x10));
        dev_trace_send_byte(HB2HEX(c % 0x10));
    }
    else dev_trace_send_byte(c);
}

void debug_printf_text(char* text)
{
   int i = 0;

   while(text[i] != 0)
   {   
      dev_trace_send_byte(text[i]);
      i++;
   }   
}

void debug_printf_ulong(unsigned long d)
{
   UINT8 buf[10], len = 0;

   if (d == 0) 
   {
      dev_trace_send_byte('0');
      return;
   }   
   
   while (d > 0)
   {   
      buf[len] = d % 10;
      d = d / 10;
      len++;
   }   

   while (len > 0)
   {   
      dev_trace_send_byte(buf[len - 1] + 0x30);
      len--;
   }   
}

void debug_printf_slong(signed long d)
{
   if (d < 0) 
   {
      dev_trace_send_byte('-');
      d = -d;
   }    

   debug_printf_ulong(d);
}

void debug_printf_long(unsigned long d, UINT8 mode)
{
   UINT8 buf[10], len = 0;

   if (d == 0) 
   {
      dev_trace_send_byte('0');
      return;
   }   
   
   if (mode == 'd') 
   if ((signed long)d < 0) 
   {
      dev_trace_send_byte('-');
      d = -((signed long)d);
   }   

   while (d > 0)
   {   
      buf[len] = d % 10;
      d = d / 10;
      len++;
   }   

   while (len > 0)
   {   
      dev_trace_send_byte(buf[len - 1] + 0x30);
      len--;
   }   
}

void debug_printf_hex(UINT32 d, UINT8 mode)
{
   UINT32 buf = 0;
   UINT8 b, len = 0;

   if (d == 0) 
   {
      dev_trace_send_byte('0');
      return;
   }   

   while (d > 0)
   {  
      buf = buf << 4;
      buf = buf + d % 0x10;
      d = d >> 4;
      len++;
   }   

   while (len > 0)
   {   
      b = buf % 0x10;
   
      if (b < 0xA) dev_trace_send_byte(b + 0x30);
      else  
      {      
         if (mode == 'X') dev_trace_send_byte(b + 0x41 - 0xA);
                  else  dev_trace_send_byte(b + 0x61 - 0xA);
      }

      buf = buf >> 4;
      len--;
   }   
}

void debug_printf_bin(UINT32 d, UINT8 mode)
{
   UINT32 buf = 0;
   UINT8 i, len = 0;

   if (mode == 'B') len = 32;
                else len = 8;

   for(i=0; i<len; i++)
   {
      buf = buf << 1;
      if (d % 2) buf++;
      d = d >> 1;      
   }   
                
   for(i=0; i<len; i++)
   {
      if (buf % 2) dev_trace_send_byte('1');
            else dev_trace_send_byte('0');
               
      buf = buf >> 1;      
   }   
}

void debug_printf(char* text, ...)
{
   va_list tag;
   int i = 0;

   va_start(tag, text);
   
   while(text[i] != 0)
   {
      if (text[i] != '%') 
      {
         dev_trace_send_byte(text[i]);
         i++;
//         continue;
      }   
      else if (text[i + 1] != 0)
      {   
         switch(text[i + 1])   
         {
            case 'd' : 
               {
                  signed long d = va_arg(tag, signed long);
                  debug_printf_long(d, 'd');
               } break;

            case 'u' : 
               {
                  unsigned long d = va_arg(tag, unsigned long);
                  debug_printf_long(d, 'u');
               } break;

            case 'f' :
               {
                  signed long l;
                  unsigned char i, m[8];
                  double d = va_arg(tag, double);

                  if (d < 0)
                  {
                    d = -d;
                    dev_trace_send_byte('-');
                  }

                  debug_printf_ulong(d);
                  dev_trace_send_byte('.');

                  d =  d - (signed long)d;
                  l = d * 1000000000;

                  if ((l % 1000) > 500) l = l / 1000 + 1;
                                  else  l = l / 1000;

//                  if (l == 0)
  //                {
    //                  m[0] = '0';
      //                m[1] = 0;
        //              debug_printf_text(m);
          //            break;
            //      }

                  i = 6; //sizeof(m);
//                  while ((l % 10) == 0)
  //                {
    //                 l = l / 10;
      //               i--;
        //          }

                  m[i] = 0;
                  while (i)
                  {
                     i--;
                     m[i] = 0x30 + (l % 10);
                     l = l / 10;
                  }

                  debug_printf_text((char*)m);

               } break;
           
            case 's' : 
               {
                  char* s = va_arg(tag, char*);
                  debug_printf_text(s);
               } break;

            case 'c' : 
               {
                  UINT8 b = va_arg(tag, unsigned long);
                  debug_printf_char(b);
               } break;
           
            case 'x' : 
               {
                  UINT32 d = va_arg(tag, UINT32);
                  debug_printf_hex(d, 'x');
               } break;
            
            case 'X' : 
               {
                  UINT32 d = va_arg(tag, UINT32);
                  debug_printf_hex(d, 'X');
               } break;
            
            case 'b' : 
               {
                  UINT32 d = va_arg(tag, UINT32);
                  debug_printf_bin(d, 'b');
               } break;
            
            case 'B' : 
               {
                  UINT32 d = va_arg(tag, UINT32);
                  debug_printf_bin(d, 'B');
               } break;
            
            case 'm' : 
               {
                  UINT8* mm = va_arg(tag, UINT8*);
                  UINT16 size = va_arg(tag, int);
                  int ii;

                  for(ii=0; ii<size; ii++) 
                  {   
                     dev_trace_send_byte(HB2HEX(mm[ii] / 0x10));
                     dev_trace_send_byte(HB2HEX(mm[ii] % 0x10));
                     dev_trace_send_byte(' ');
                  }
               
               } break;

            case 'M' : 
               {
                  UINT8* mm = va_arg(tag, UINT8*);
                  UINT16 size = va_arg(tag, int);
                  int ii;

                  for(ii=0; ii<size; ii++) 
                  {   
                     debug_printf_long(mm[ii], 'u');
                     dev_trace_send_byte(' ');
                  }
               
               } break;

            case 'p' : 
               {
                  UINT8* mm = va_arg(tag, UINT8*);
               
                  debug_printf_long(mm[0], 'u');
                  dev_trace_send_byte('.');
                  debug_printf_long(mm[1], 'u');
                  dev_trace_send_byte('.');
                  debug_printf_long(mm[2], 'u');
                  dev_trace_send_byte('.');
                  debug_printf_long(mm[3], 'u');
               
               } break;
           
         }
      
         i += 2;
      }
   }   

}


void assert_failed(uint8_t* file, uint32_t line)
{
		debug_printf("ASSERT > %s:%d\n\r", file, line);
}




