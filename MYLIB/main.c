// ******************************************************************************
// *  File: main.c
// *
// *  Purpose:                                                                         
// *  This is the main entry point of the application, hardware peripherals and
// *  system data structures are initialised here. The main loop is defined here 
// *  where calls to the application state machine shall be made. 
// *
// *  By: Kevin Wong
// *  Revision 1.0
// *  Date: 23/10/2016  
// *
// *
// *
// *****************************************************************************

#include "main.h"

int main(void) {

    HW__InitialiseSystem();     //Initialise processor main registers and clock
    INT__EnableInterrupts();    //Enable interrupt generation

    TENMS__Reset();             //Intialise ten milliseond timer driver
    ONEMS__Reset(); 
    GPIO_reset();

    //Main application loop
    APPLICATION__Process();  

	return 0;
}
