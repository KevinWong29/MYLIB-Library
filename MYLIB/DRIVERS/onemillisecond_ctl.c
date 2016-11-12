// *****************************************************************************
// *  File: onemillisecond_ctl.c
// *
// *  Purpose:                                                                         
// *  This file defines the various functions for the ten millisecond timer driver. 
// *  
// *  
// * 
// *  By: Kevin Wong
// *  Revision 1.0
// *  Date: 3/10/2016 
// *
// *
// *
// *****************************************************************************

#include "onemillisecond_ctl.h"
#include "interrupt.h"

// Public variables defined here
uint16_t OneMsSoftTimer[ONEMS__NUM_SOFT_TIMERS];

// Private variables defined here 

#if (ONEMS__NUM_SOFT_TIMERS < ONEMS__MAX_SOFT_TIMERS)

//*****************************************************************************
// Purpose: Reset all software timers 
// Argument: None
// Return: None
//
//*****************************************************************************

static void ResetSoftTimer(void)
{
    uint8_t index;

    for(index = 0; index < ONEMS__NUM_SOFT_TIMERS; index++)
    {
        OneMsSoftTimer[index] = 0;
    }    
}

//*****************************************************************************
// Purpose: Warm start the timer peripheral
// Argument: None
// Return: None
//
//*****************************************************************************

static void StartTimer(void)
{
    HWREG16(TIMERA_TACTL_REG_ADDR) |= ONEMS__TIMER_MODE_CONFIG; //Put the timer into stop mode
    INT__Enable(TIMERA_CC0_INT);
}

//*****************************************************************************
// Purpose: Stop the timer peripheral
// Argument: None
// Return: None
//
//*****************************************************************************

static void StopTimer(void)
{
    INT__Disable(TIMERA_CC0_INT);
    HWREG16(TIMERA_TACTL_REG_ADDR) &= ~(ONEMS__TIMER_MODE_CONFIG); //Put the timer into stop mode
}

//*****************************************************************************
// Purpose: Calculate timer compare value and set the counter. A compare value
//          must be recalculated to determine the next counter value for which
//          the next interrupt must occur.
// Argument: None
// Return: None
//
//*****************************************************************************

static inline void SetCompareValue(void)
{
    uint16_t currentValue = HWREG16(TIMERA_TACCR0_REG_ADDR);

    //The new compare value is the sum of the current value and the base compare value.
    //Determine if the summation of the base compare value exceeds the timer counter range.
    if((0xFFFF - currentValue) > ONEMS__TIMER_COMPARE_VALUE)
    {
        HWREG16(TIMERA_TACCR0_REG_ADDR) = currentValue + ONEMS__TIMER_COMPARE_VALUE;
    }    
    else
    {
        //Calculate the compare value when the counter loops back
        HWREG16(TIMERA_TACCR0_REG_ADDR) = (ONEMS__TIMER_COMPARE_VALUE - (0xFFFF - currentValue));
    }    
}

//*****************************************************************************
// Purpose: This function resets and initiates timer to default configurations.
// Argument: None
// Return: None
//
//*****************************************************************************

void ONEMS__Reset(void) 
{
    //Reset and configure the Timer A peripheral to continuous compare mode
    //Timer A peripheral configuration done else where in hardware initialisation
    //HWREG16(TIMERA_TACTL_REG_ADDR) = ONEMS__TACTL_STARTUP_CONFIG;
    HWREG16(TIMERA_TACCTL0_REG_ADDR) = ONEMS__TACCTL_STARTUP_CONFIG;
    HWREG16(TIMERA_TACCTL0_REG_ADDR) &= ~TIMERA_CCIFG_MASK;

    //Load counter compare value to compare and generate interrupt
    HWREG16(TIMERA_TACCR0_REG_ADDR) = ONEMS__TIMER_COMPARE_VALUE;

    //Initialise software timers
    ResetSoftTimer();

    //Enable capture and compare interrupts
    INT__Enable(TIMERA_CC0_INT);
}

//*****************************************************************************
// Purpose: This function allows for basic control of the timer peripheral
// Argument: 
// Return: None
//
//*****************************************************************************

void ONEMS__Control(uint16_t *timerInterfaceBuffer)
{
    INT__Disable(TIMERA_CC0_INT);
    switch(timerInterfaceBuffer[ONEMS__CONFIG_SETTING_IDX])
    {
        case ONEMS__TIMER_START:
            StartTimer();
            break;

        case ONEMS__TIMER_STOP:
            StopTimer();
            break;

        default:
            LIBUTIL__LogError(ONEMS__INVALID_CONTROL_SETTING);
    }    
    INT__Enable(TIMERA_CC0_INT);
}

//*****************************************************************************
// Purpose: Perform a read of the specified software timer and return its
//          value in the interface buffer.
// Argument: timerInterfaceBuffer - [1] Soft timer ID
//                                  [2] Soft timer counter value (return)
// Return: None
//
//*****************************************************************************

void ONEMS__Read(uint16_t *timerInterfaceBuffer)
{
    if(timerInterfaceBuffer[ONEMS__TIMER_ID_IDX] < ONEMS__NUM_SOFT_TIMERS)
    {
        timerInterfaceBuffer[ONEMS__TIMER_COUNTER] = OneMsSoftTimer[timerInterfaceBuffer[ONEMS__TIMER_ID_IDX]];
    }    
    else
    {
        LIBUTIL__LogError(ONEMS__INVALID_TIMER_READ);
    }    
}

//*****************************************************************************
// Purpose: Software timers can be registered via calling this function, 
//          a unique timer 
// Argument: timerInterfaceBuffer - [1] Soft timer ID
//                                  [2] Soft timer counter value (write)
// Return: None
//
//*****************************************************************************

void ONEMS__Write(uint16_t *timerInterfaceBuffer)
{

    if(timerInterfaceBuffer[ONEMS__TIMER_ID_IDX] < ONEMS__NUM_SOFT_TIMERS)
    {
        OneMsSoftTimer[timerInterfaceBuffer[ONEMS__TIMER_ID_IDX]] = timerInterfaceBuffer[ONEMS__TIMER_COUNTER];
    }    
    else
    {
        LIBUTIL__LogError(ONEMS__INVALID_TIMER_WRITE);
    }

}

//*****************************************************************************
// Purpose: This is the tenmillisecond timer interrupt event handler.
// Argument: None
// Return: None
//
//*****************************************************************************

void OneMilliSecondEventHandler(void) 
{
    SetCompareValue();

    //Periodic task calls to be added here

    //Decrement the software timers
    if(ONEMS__NUM_SOFT_TIMERS > 0)
    {
        uint8_t index;
        for(index = 0; index < ONEMS__NUM_SOFT_TIMERS; index++)
        {
            //Decrement any soft timer that is non-zero
            if(OneMsSoftTimer[index] > 0)
            {
                OneMsSoftTimer[index]--;
            } 
        }    
    }    

    HWREG16(TIMERA_TACCTL0_REG_ADDR) &= ~TIMERA_CCIFG_MASK; //Clear capture compare flag  
}

#else
    #error "onemillisecond_ctl.c: Max number of soft timers exceeded!"
#endif //
