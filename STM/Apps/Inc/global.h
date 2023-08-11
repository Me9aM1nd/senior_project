#ifndef _GLOBAL_H
#define _GLOBAL_H


#include "binary.h"
#include "dev_trace.h"
#include "stdlib.h"

//#include "tools.h"

#include <stdio.h>


#define GLOBAL_INTERRUPT_DISABLE 	__disable_irq();
#define GLOBAL_INTERRUPT_ENABLE 	__enable_irq();

#endif

