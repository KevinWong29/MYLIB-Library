// *****************************************************************************
// *  File: interrupt.h
// *
// *  Purpose:                                                                         
// *  This header file defines all of the interrupt control function primitives
// *  and constants. Interrupt vectors for the processor may also be defined  
// *  here.
// * 
// *  By: Kevin Wong
// *  Revision 1.0
// *  Date: 11/09/2016  
// *
// *
// *
// *****************************************************************************

#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "libUtility.h"
#include <stdint.h>
#include <stdbool.h>

#define COMPILED_INTERRUPT_CTL

//*****************************************************************************
//
// Generic constants defined here.  
//
//*****************************************************************************

#define DISABLE_INT		0
#define ENABLE_INT		1

#define INT__INVALID_INTERRUPT_ID   20


//*****************************************************************************
//
// Base addresses to registers with interrupt enable control are defined here.
//
//*****************************************************************************

#define PORT1_IE_REG_ADDR	(MSP430_PORT1_ADDR + OFS_IE)  //Base address to PORT1 P1IE register
#define PORT2_IE_REG_ADDR	(MSP430_PORT2_ADDR + OFS_IE)  //Base address to PORT2 P2IE register

//*****************************************************************************
//
// Interrupt ID defined here, use these to define the interrupt to be configured
//
//*****************************************************************************

//GPIO interrupt ID

#define IO_INT_0	0
#define IO_INT_1	1 
#define IO_INT_2	2
#define IO_INT_3	3
#define IO_INT_4	4
#define IO_INT_5	5
#define IO_INT_6	6
#define IO_INT_7	7
#define IO_INT_8	8
#define IO_INT_9	9
#define IO_INT_10	10
#define IO_INT_11	11
#define IO_INT_12	12
#define IO_INT_13	13
#define IO_INT 		0

//Timer A interrupt ID

#define TIMERA_INT       14
#define TIMERA_CC0_INT   15
#define TIMERA_CC1_INT   16
#define TIMERA_CC2_INT   17

//*****************************************************************************
//
// Function prototype defined here
// 
//*****************************************************************************

void INT__Enable(uint8_t int_id);
void INT__Disable(uint8_t int_id);
void INT__EnableInterrupts(void);
void INT__DisableInterrupts(void);

#endif //__INTERRUPT_H__
