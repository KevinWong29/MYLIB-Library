// *****************************************************************************
// *  File: libUtility.c
// *
// *  Purpose:                                                                         
// *  General low level library utility functions and facilities are defined here. 
// *  
// *  By: Kevin Wong
// *  Revision 1.0
// *  Date: 30/10/2016 
// *
// *
// *
// *****************************************************************************

#include "libUtility.h"

// Private variables defined here

uint16_t ErrorLogBuffer_ro[LIBUTIL__MAX_ERROR_LOGGED];
uint8_t LogWriteIndex;
uint8_t LogNumErrors;
uint8_t LibErrorFlag;

//*****************************************************************************
// Purpose: Log error code into the error log buffer, if the buffer is full
//          the oldest error in the log will be overwritten.
// Argument: None
// Return: None
//
//*****************************************************************************

static void LogError(uint16_t ErrorCode)
{
    uint8_t index;
    uint8_t replica = FALSE;

    //Check that the same error code has not been logged
    for(index = 0; index < LIBUTIL__MAX_ERROR_LOGGED; index++)
    {
        if(ErrorLogBuffer_ro[index] == ErrorCode)
        {
            replica = TRUE;
        }
    }   

    if(replica != TRUE)
    {
        ErrorLogBuffer_ro[LogWriteIndex] = ErrorCode;
        
        LogWriteIndex++; //Increment log write index, any existing error will be overwritten

        //Handle the circular log buffer
        if(LogWriteIndex >= LIBUTIL__MAX_ERROR_LOGGED)
        {
            LogWriteIndex = 0;
        }    

        if(LogNumErrors < LIBUTIL__MAX_ERROR_LOGGED)
        {
            LogNumErrors++;
        }   

        LibErrorFlag = 1;
    } 

}

//*****************************************************************************
// Purpose: Remove specified error code from the error log buffer
// Argument: None
// Return: None
//
//*****************************************************************************

static void RemoveError(uint8_t ErrorCode)
{
    uint8_t index;

    for(index = 0; index < LIBUTIL__MAX_ERROR_LOGGED; index++)
    {
        if(ErrorLogBuffer_ro[index] == ErrorCode)
        {
            ErrorLogBuffer_ro[index] = 0;
            LogNumErrors--;

            if(LogNumErrors == 0)
            {
                LibErrorFlag = 0;
            }    
        }    
    }    
}

//*****************************************************************************
// Purpose: Initialise the error logging function utility
// Argument: None
// Return: None
//
//*****************************************************************************

static void InitErrorHandling(void)
{
    uint8_t index;

    // Initialise the log buffer
    for(index = 0; index < LIBUTIL__MAX_ERROR_LOGGED; index++)
    {
        ErrorLogBuffer_ro[index] = 0;
    }   

    LibErrorFlag = 0; // Clear the error flag
    LogWriteIndex = 0; // Set write index to start of log buffer
    LogNumErrors = 0;
}

//*****************************************************************************
// Purpose: Returns the number of errors logged in the error log
// Argument: None
// Return: Number of errors logged
//
//*****************************************************************************

uint8_t LIBUTIL__GetNumErrors(void)
{
    return LogNumErrors;
}

//*****************************************************************************
// Purpose: Clear the specified error from the log
// Argument: None
// Return: None
//
//*****************************************************************************

void LIBUTIL__ClearError(uint8_t ErrorCode)
{
    RemoveError(ErrorCode);
}

//*****************************************************************************
// Purpose: Initialise the library utility
// Argument: None
// Return: None
//
//*****************************************************************************

void LIBUTIL__Init(void)
{
    InitErrorHandling();
}


//*****************************************************************************
// Purpose: Log error code into the error log buffer, if the buffer is full
//          the oldest error in the log will be overwritten.
// Argument: Error code
// Return: None
//
//*****************************************************************************

void LIBUTIL__LogError(uint16_t ErrorCode)
{
    LogError(ErrorCode);
}



