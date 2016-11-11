// *****************************************************************************
// *  File: onemillisecond_ctl.h
// *
// *  Purpose:                                                                         
// *  This is the header file for the ten millisecond timer driver. All constants
// *  and global variables defined here.
// *  
// * 
// *  By: Kevin Wong
// *  Revision 1.0
// *  Date: 3/10/2016 
// *
// *
// *
// *****************************************************************************

#ifndef _ONEMILLISECOND_CTL_H_
#define _ONEMILLISECOND_CTL_H_

#include "hardware_ctl.h"
#include "interrupt.h"
#include "libUtility.h"
#include <stdint.h>

#define COMPILED_ONEMS_CTL

//*****************************************************************************
//
// Software timers defined and registered here
// 
//*****************************************************************************

enum 
{
    ONEMS__NUM_SOFT_TIMERS
};

//*****************************************************************************
//
// Driver configuration constants defined here
// 
//*****************************************************************************

#define ONEMS__TIMER_CLOCK_SOURCE_CONFIG      TIMERA_SOURCE_SMCLK
#define ONEMS__TIMER_CLOCK_DIVISION_CONFIG    TIMERA_DIVIDE_1
#define ONEMS__TIMER_MODE_CONFIG              TIMERA_MODE_CONTINUOUS

//Driver configuration preload values, configure for timer compare mode
#define ONEMS__TACTL_STARTUP_CONFIG     (ONEMS__TIMER_CLOCK_SOURCE_CONFIG + ONEMS__TIMER_CLOCK_DIVISION_CONFIG + ONEMS__TIMER_MODE_CONFIG + TIMERA_TACLR_MASK)
#define ONEMS__TACCTL_STARTUP_CONFIG    0x0000 //Configure with register default value

//Timer counter value to produce 10ms interrupt intervals
#define ONEMS__TIMER_COMPARE_VALUE          10000    //Value calculated for 1MHz system clock

#define ONEMS__MAX_SOFT_TIMERS              16

//Timer config type values
#define ONEMS__TIMER_START                  0
#define ONEMS__TIMER_STOP                   1

//Timer config buffer indexes
#define ONEMS__CONFIG_SETTING_IDX           0
#define ONEMS__CONFIG_BUFFER_SIZE           1

//Timer read and write buffer indexes
#define ONEMS__TIMER_ID_IDX                 0
#define ONEMS__TIMER_COUNTER                1
#define ONEMS__RW_BUFFER_SIZE               2

#define ONEMS__INTERFACE_BUFFER_SIZE        3

#define ONEMS__INVALID_TIMER_READ           11
#define ONEMS__INVALID_TIMER_WRITE          12
#define ONEMS__INVALID_CONTROL_SETTING      13


//*****************************************************************************
//
// Public accessable variables defined here
// 
//*****************************************************************************


//*****************************************************************************
//
// Function prototype defined here
// 
//*****************************************************************************

void ONEMS__Reset(void);
void ONEMS__Control(uint16_t *timerInterfaceBuffer);
void ONEMS__Read(uint16_t *timerInterfaceBuffer);
void ONEMS__Write(uint16_t *timerInterfaceBuffer);
void OneMilliSecondEventHandler(void);

#endif //_ONEMILLISECOND_CTL_H_
