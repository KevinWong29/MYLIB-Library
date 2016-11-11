// *****************************************************************************
// *  File: tenmillisecond_ctl.h
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

#ifndef _TENMILLISECOND_CTL_H_
#define _TENMILLISECOND_CTL_H_

#include "hardware_ctl.h"
#include "interrupt.h"
#include "libUtility.h"
#include <stdint.h>

#define COMPILED_TENMS_CTL

//*****************************************************************************
//
// Software timers defined and registered here
// 
//*****************************************************************************

enum 
{
    LED_SOFT_TIMER = 0,
    TENMS__NUM_SOFT_TIMERS
};

//*****************************************************************************
//
// Driver configuration constants defined here
// 
//*****************************************************************************

#define TENMS__TIMER_CLOCK_SOURCE_CONFIG      TIMERA_SOURCE_SMCLK
#define TENMS__TIMER_CLOCK_DIVISION_CONFIG    TIMERA_DIVIDE_1
#define TENMS__TIMER_MODE_CONFIG              TIMERA_MODE_CONTINUOUS

//Driver configuration preload values, configure for timer compare mode
#define TENMS__TACTL_STARTUP_CONFIG     (TENMS__TIMER_CLOCK_SOURCE_CONFIG + TENMS__TIMER_CLOCK_DIVISION_CONFIG + TENMS__TIMER_MODE_CONFIG + TIMERA_TACLR_MASK)
#define TENMS__TACCTL_STARTUP_CONFIG    0x0000 //Configure with register default value

//Timer counter value to produce 10ms interrupt intervals
#define TENMS__TIMER_COMPARE_VALUE          10000    //Value calculated for 1MHz system clock

#define TENMS__MAX_SOFT_TIMERS              16

//Timer config type values
#define TENMS__TIMER_START                  0
#define TENMS__TIMER_STOP                   1

//Timer config buffer indexes
#define TENMS__CONFIG_SETTING_IDX           0
#define TENMS__CONFIG_BUFFER_SIZE           1

//Timer read and write buffer indexes
#define TENMS__TIMER_ID_IDX                 0
#define TENMS__TIMER_COUNTER                1
#define TENMS__RW_BUFFER_SIZE               2

#define TENMS__INTERFACE_BUFFER_SIZE        3

#define TENMS__INVALID_TIMER_READ           11
#define TENMS__INVALID_TIMER_WRITE          12
#define TENMS__INVALID_CONTROL_SETTING      13


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

void TENMS__Reset(void);
void TENMS__Control(uint16_t *timerInterfaceBuffer);
void TENMS__Read(uint16_t *timerInterfaceBuffer);
void TENMS__Write(uint16_t *timerInterfaceBuffer);
void TenMilliSecondEventHandler(void);

#endif //_TENMILLISECOND_CTL_H_
