// *****************************************************************************
// *  File: interrupt.c
// *
// *  Purpose:                                                                         
// *  This file contains functions for the control interrupt flags and registers.
// *  Interrupt handler functions may be defined here or in individual driver
// *  code. 
// * 
// *  By: Kevin Wong
// *  Revision 1.0
// *  Date: 27/08/2016  
// *
// *
// *
// *****************************************************************************

#include "interrupt.h"
#include "hardware_ctl.h"
#include "onemillisecond_ctl.h"
#include "tenmillisecond_ctl.h"
#include "gpio.h"

//*****************************************************************************
//
// Interrupt vector callbacks are defined here, handler functions may be 
// defined in individual driver source code.
//
//*****************************************************************************

#if defined PORT1_VECTOR

// Port 1 GPIO interrupt vector call
#pragma vector = PORT1_VECTOR
__interrupt void GPIO_PORT1_Handler(void) 
{
  	GPIO_Port1_Event_Handler();
}

#else
  	#error "interrupt.c: Port 1 not available!"
#endif

#if defined PORT2_VECTOR

// Port 2 GPIO interrupt vector call 
#pragma vector = PORT2_VECTOR
__interrupt void GPIO_PORT2_Handler(void) 
{
  	GPIO_Port2_Event_Handler();
}

#else
  	#error "interrupt.c: Port 2 not available!"
#endif

#if defined TIMERA0_VECTOR

// TimerA0 interrupt vector call
#pragma vector = TIMERA0_VECTOR
__interrupt void TIMERA0_HANDLER(void) 
{
#ifdef COMPILED_ONEMS_CTL	
	OneMilliSecondEventHandler();
#endif
}

#else
	#error "interrupt.c: TimerA0 not available!"
#endif

#if defined TIMERA1_VECTOR

// TimerA1 interrupt vector call
#pragma vector = TIMERA1_VECTOR
__interrupt void TIMERA1_HANDLER(void) 
{
#ifdef COMPILED_TENMS_CTL
	TenMilliSecondEventHandler();
#endif
}

#else
	#error "interrupt.c: TimerA1 not available!"
#endif


// Additional interrupt vector callbacks to be defined here as working progress

//*****************************************************************************
//
// Purpose: Inline function to set the IO enable interrupt bits.
// Argument: int_id - interrupt ID identifier
// 					 setting - (DISABLE_INT) disable specified interrupt bit  
//							 - (ENABLE_IN) enable specified interrupt bit
// Return: None
//
//*****************************************************************************

static inline void set_IO_interrupt(uint8_t int_id, uint8_t setting) 
{
	uint16_t base_address;

	if(int_id < IO_INT_7) 
	{
		base_address = PORT1_IE_REG_ADDR;
	}
	else 
	{
		base_address = PORT2_IE_REG_ADDR;
	}

	//Write to IO interrupt enable hardware register
	if(setting == ENABLE_INT) 
	{
		HWREG8(base_address) |= (1 << int_id);
	}
	else 
	{
		HWREG8(base_address) &= ~(1 << int_id);
	}
}

//*****************************************************************************
// Function: INT__Enable(uint8_t int_id)
// Purpose: Interrupt enable for various peripherals are to be done by this function. 
// Argument: int_id - interrupt ID identifier
// Return: None
//
//*****************************************************************************

void INT__Enable(uint8_t int_id) 
{
	uint8_t temp = 0;

	//All IO interrupt ID can be mapped to one
	if(int_id <= IO_INT_13) 
	{
		temp = int_id;
		int_id = IO_INT;
	}

	switch(int_id) 
	{
		case IO_INT:
			set_IO_interrupt(temp, ENABLE_INT);
			break;
		case TIMERA_INT:
			HWREG16(TIMERA_TACTL_REG_ADDR) |= TIMERA_TAIE_MASK;
			break;
		case TIMERA_CC0_INT:
			HWREG16(TIMERA_TACCTL0_REG_ADDR) |= TIMERA_CCIE_MASK;
			break;
		case TIMERA_CC1_INT:
			HWREG16(TIMERA_TACCTL1_REG_ADDR) |= TIMERA_CCIE_MASK;
			break;	 
		case TIMERA_CC2_INT:
			HWREG16(TIMERA_TACCTL2_REG_ADDR) |= TIMERA_CCIE_MASK;
			break;
		default:
			LIBUTIL__LogError(INT__INVALID_INTERRUPT_ID);
	}
}

//*****************************************************************************
// Function: INT__Disable(uint8_t int_id)
// Purpose: Interrupt disable for various peripherals are to be done by this function. 
// Argument: int_id - interrupt ID identifier
// Return: None
//
//*****************************************************************************

void INT__Disable(uint8_t int_id) 
{
	uint8_t temp = 0;

	//All IO interrupt ID can be mapped to one
	if(int_id <= IO_INT_13) 
	{
		temp = int_id;
		int_id = IO_INT;
	}

	switch(int_id) 
	{
		case IO_INT:
			set_IO_interrupt(temp, DISABLE_INT);
			break;
		case TIMERA_INT:
			HWREG16(TIMERA_TACTL_REG_ADDR) &= ~TIMERA_TAIE_MASK;
			break;
		case TIMERA_CC0_INT:
			HWREG16(TIMERA_TACCTL0_REG_ADDR) &= ~TIMERA_CCIE_MASK;
			break;
		case TIMERA_CC1_INT:
			HWREG16(TIMERA_TACCTL1_REG_ADDR) &= ~TIMERA_CCIE_MASK;
			break;	 
		case TIMERA_CC2_INT:
			HWREG16(TIMERA_TACCTL2_REG_ADDR) &= ~TIMERA_CCIE_MASK;
			break;	
		default:
			LIBUTIL__LogError(INT__INVALID_INTERRUPT_ID);
	}
}

//*****************************************************************************
// Function: INT__EnableInterrupts(void)
// Purpose: Enable interrupt generation
// Argument: None
// Return: None
//
//*****************************************************************************

void INT__EnableInterrupts(void) 
{
	_enable_interrupts();		//Write to CPU status register to enable general interrupts
}

//*****************************************************************************
// Function: INT__DisableInterrupts(void)
// Purpose: Disable interrupt generation
// Argument: None
// Return: None
//
//*****************************************************************************

void INT__DisableInterrupts(void) 
{
	_disable_interrupts();		//Write to CPU status register to enable general interrupts
}

