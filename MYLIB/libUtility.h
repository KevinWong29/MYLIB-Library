// *****************************************************************************
// *  File: libUtility.h
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

#ifndef __LIBUTILITY_H_
#define __LIBUTILITY_H_

#include <stdint.h>
#include <stdbool.h>

#define COMPILED_LIBUTIL_CTL

//*****************************************************************************
//
// Library utility constants defined here
// 
//*****************************************************************************

#define LIBUTIL__MAX_ERROR_LOGGED       5

//*****************************************************************************
//
// Generic error codes defined here, driver specific codes defined elsewhere
// 
//*****************************************************************************

#define TRUE    1
#define FALSE   0

//*****************************************************************************
//
// Function prototypes defined here
// 
//*****************************************************************************

static void LogError(uint16_t ErrorCode);
static void RemoveError(uint8_t ErrorCode);
static void InitErrorHandling(void);
uint8_t LIBUTIL__GetNumErrors(void);
void LIBUTIL__ClearError(uint8_t ErrorCode);
void LIBUTIL__Init(void);
void LIBUTIL__LogError(uint16_t ErrorCode);


#endif //__LIBUTILITY_H_

