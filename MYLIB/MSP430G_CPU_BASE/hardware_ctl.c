// ******************************************************************************
// *  File: hardware_ctl.c
// *
// *  Purpose:                                                                         
// *  Peripheral register base addresses for the Texas Instrument MSP430G2x21 series           
// *  are defined here in this header file. All peripheral pin name definitions        
// *  defined here. Pin allocations can be redefined here depending on application. 
// *
// *  By: Kevin Wong
// *  Revision 1.0
// *  Date: 27/08/2016  
// *
// *
// *
// *****************************************************************************

#include "hardware_ctl.h"
#include <stdint.h>

//*****************************************************************************
// Function: HW__InitialiseClock(void)
// Purpose: Initialise deivce clock configuration on start up.
// Argument: None
// Return: None
//
//*****************************************************************************

void HW__InitialiseSystem(void)
{
    WDTCTL = WDTPW | WDTHOLD;   //Disable watchdog, utility not fully implemented

    //Configure the DCOCTL and BCSCTL clock registers, load clock factory calibration
    //MSP430G2x21 only has 1MHz factory calibration settings defined
    HWREG16(DCO_CONTROL_REG_ADDR) = DCOCTL_STARTUP_CONFIG;
    HWREG16(BCS_CONTROL_REG1_ADDR) = BCSCTL1_STARTUP_CONFIG;
    HWREG16(BCS_CONTROL_REG2_ADDR) = BCSCTL2_STARTUP_CONFIG;
    HWREG16(BCS_CONTROL_REG3_ADDR) = BCSCTL3_STARTUP_CONFIG;

    LIBUTIL__Init(); 

    //Check for clock fault, this only applies if external clock or low power source is used
    while(HWREG16(BCS_CONTROL_REG3_ADDR) & (XT2S_FAULT_MASK + LFXT1_FAULT_MASK))
    {
        //TO DO need to produce debug indication when there is a clock fault
        // Logging the error here will not suffice!
        LIBUTIL__LogError(HW__EXT_CLOCK_FAULT);
    }    
}

//*****************************************************************************
// Function: HW__EnterLowpower(void)
// Purpose: Put device into low power mode
// Argument: None
// Return: None
//
//*****************************************************************************

void HW__EnterLowpower(void)
{
    _bis_SR_register(LPM0);    //Write to CPU status register
}

//*****************************************************************************
// Function: HW__EnterDeepSleep(void)
// Purpose: Put device into the lowest power setting
// Argument: None
// Return: None
//
//*****************************************************************************

void HW__EnterDeepSleep(void)
{
    _bis_SR_register(LPM4);    //Write to CPU status register
}
