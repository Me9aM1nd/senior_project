// ----------------------------------------------------------------------------
//         AZRY Microcontroller Software Support 
// ----------------------------------------------------------------------------
// Copyright (c) 2009, AZRY Corporation
//
// All rights reserved.
//
// ----------------------------------------------------------------------------


#ifndef _TRACE_SPI_H
#define _TRACE_SPI_H

#include "binary.h"
#include "hal_gpio.h"

#ifdef __cplusplus
 extern "C" {
#endif
	 
typedef struct {dev_gpio_info_t mosi, sck, nss;} dev_trace_init_t;

uint8_t dev_trace_init(dev_trace_init_t* init);
void dev_trace_send_byte(uint8_t b);
void dev_trace_send_buf(uint8_t* pData, uint16_t nData);

uint8_t dev_trace_get_error(uint8_t error_value, char* file_name, uint32_t file_line);
uint8_t dev_trace_generate_error(char* error_name, char* file_name, uint32_t file_line);
uint8_t dev_trace_generate_verror(char* error_name, UINT32 error_value, char* file_name, UINT32 file_line);

void debug_printf(char* text, ...);

//------------------------------------------------------------------------------
//         Global Definitions
//------------------------------------------------------------------------------

/// Softpack Version
#define SOFTPACK_VERSION "1.5"

#define TRACE_LEVEL_DEBUG      5
#define TRACE_LEVEL_INFO       4
#define TRACE_LEVEL_WARNING    3
#define TRACE_LEVEL_ERROR      2
#define TRACE_LEVEL_FATAL      1
#define TRACE_LEVEL_NO_TRACE   0

// By default, all traces are output except the debug one.
#if !defined(TRACE_LEVEL)    
#define TRACE_LEVEL TRACE_LEVEL_INFO
//#define TRACE_LEVEL TRACE_LEVEL_DEBUG
//#define TRACE_LEVEL TRACE_LEVEL_NO_TRACE
#endif

// By default, trace level is static (not dynamic)
#if !defined(DYN_TRACES)
#define DYN_TRACES 0
#endif

#if defined(NOTRACE)
#error "Error: NOTRACE has to be not defined !"
#endif

#undef NOTRACE
#if (TRACE_LEVEL == TRACE_LEVEL_NO_TRACE)
#define NOTRACE
#endif

//------------------------------------------------------------------------------
//         Global Macros
//------------------------------------------------------------------------------
#if defined(NOTRACE)

// Empty macro
#define TRACE_DEBUG(...)      			{ }
#define TRACE_INFO(...)       			{ }
#define TRACE_WARNING(...)    			{ }               
#define TRACE_ERROR(...)      			{ }
#define TRACE_EERROR(error_val)      	error_val 
#define TRACE_GERROR(...)      			1
#define TRACE_FATAL(...)      			{ while(1); }

#define TRACE_DEBUG_WP(...)   			{ }
#define TRACE_INFO_WP(...)    			{ }
#define TRACE_WARNING_WP(...) 			{ }
#define TRACE_ERROR_WP(...)   			{ }
#define TRACE_FATAL_WP(...)   			{ while(1); }

#elif (DYN_TRACES == 1)

// Trace output depends on traceLevel value
#define TRACE_DEBUG(...)      { if (traceLevel >= TRACE_LEVEL_DEBUG)   { debug_printf("D> " __VA_ARGS__); } }
#define TRACE_INFO(...)       { if (traceLevel >= TRACE_LEVEL_INFO)    { debug_printf("I> " __VA_ARGS__); } }
#define TRACE_WARNING(...)    { if (traceLevel >= TRACE_LEVEL_WARNING) { debug_printf("W> " __VA_ARGS__); } }
#define TRACE_ERROR(...)      { if (traceLevel >= TRACE_LEVEL_ERROR)   { debug_printf("E> " __VA_ARGS__); } }
#define TRACE_FATAL(...)      { if (traceLevel >= TRACE_LEVEL_FATAL)   { debug_printf("F> " __VA_ARGS__); while(1); } }

#define TRACE_DEBUG_WP(...)   { if (traceLevel >= TRACE_LEVEL_DEBUG)   { debug_printf(__VA_ARGS__); } }
#define TRACE_INFO_WP(...)    { if (traceLevel >= TRACE_LEVEL_INFO)    { debug_printf(__VA_ARGS__); } }
#define TRACE_WARNING_WP(...) { if (traceLevel >= TRACE_LEVEL_WARNING) { debug_printf(__VA_ARGS__); } }
#define TRACE_ERROR_WP(...)   { if (traceLevel >= TRACE_LEVEL_ERROR)   { debug_printf(__VA_ARGS__); } }
#define TRACE_EERROR_WP(...)   { if (traceLevel >= TRACE_LEVEL_ERROR)  { debug_printf(__VA_ARGS__); } }
#define TRACE_FATAL_WP(...)   { if (traceLevel >= TRACE_LEVEL_FATAL)   { debug_printf(__VA_ARGS__); while(1); } }

#else

// Trace compilation depends on TRACE_LEVEL value
#if (TRACE_LEVEL >= TRACE_LEVEL_DEBUG)
#define TRACE_DEBUG(...)      { debug_printf("D> " __VA_ARGS__); }
#define TRACE_DEBUG_WP(...)   { debug_printf(__VA_ARGS__); }
#else
#define TRACE_DEBUG(...)      { }
#define TRACE_DEBUG_WP(...)   { }
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_INFO)
#define TRACE_INFO(...)       { debug_printf("I> " __VA_ARGS__); }
#define TRACE_INFO_WP(...)    { debug_printf(__VA_ARGS__); }

#define TRACE_INIT(...)       { debug_printf("INIT> " __VA_ARGS__); }
#define TRACE_INIT_WP(...)    { debug_printf(__VA_ARGS__); }

#define TRACE_LEVEL_INFO_ENABLE

#else
#define TRACE_INFO(...)       { }
#define TRACE_INFO_WP(...)    { }
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_WARNING)
#define TRACE_WARNING(...)    { debug_printf("W> " __VA_ARGS__); }
#define TRACE_WARNING_WP(...) { debug_printf(__VA_ARGS__); }
#else
#define TRACE_WARNING(...)    { }
#define TRACE_WARNING_WP(...) { }
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_ERROR)
#define TRACE_ERROR(...)      { debug_printf("E> " __VA_ARGS__); }
#define TRACE_ERROR_WP(...)   { debug_printf(__VA_ARGS__); }
#else
#define TRACE_ERROR(...)      { }
#define TRACE_ERROR_WP(...)   { }
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_ERROR)
#define TRACE_EERROR(error_value) dev_trace_get_error(error_value, __FILE__, __LINE__) 
#define TRACE_GERROR(error_name) dev_trace_generate_error(error_name, __FILE__, __LINE__) 
#define TRACE_VERROR(error_name, error_value) dev_trace_generate_verror(error_name, error_value, __FILE__, __LINE__) 
#else
#define TRACE_EERROR(error_val)   	error_val
#define TRACE_GERROR(...)   		1
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_FATAL)
#define TRACE_FATAL(...)      { debug_printf("F> " __VA_ARGS__); while(1); }
#define TRACE_FATAL_WP(...)   { debug_printf(__VA_ARGS__); while(1); }
#else
#define TRACE_FATAL(...)      { while(1); }
#define TRACE_FATAL_WP(...)   { while(1); }
#endif

#endif


//------------------------------------------------------------------------------
//         Exported variables
//------------------------------------------------------------------------------
// Depending on DYN_TRACES, traceLevel is a modifable runtime variable
// or a define
#if !defined(NOTRACE) && (DYN_TRACES == 1)
    extern unsigned int traceLevel;
#endif	 
	 

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

	 
#ifdef __cplusplus
}
#endif


#endif
