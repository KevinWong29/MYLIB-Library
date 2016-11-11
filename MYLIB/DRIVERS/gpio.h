// *****************************************************************************
// *  File: gpio.h
// *
// *  Purpose:                                                                         
// *  GPIO driver header file, constants and driver configurations defined here.   
// *
// *  By: Kevin Wong
// *  Revision 1.0 
// *  Date: 27/08/2016  
// *
// *
// *
// *****************************************************************************
 
#ifndef _GPIO_H_
#define _GPIO_H_

#include "hardware_ctl.h"
#include "libUtility.h"
#include <stdint.h>
#include <stdbool.h>

#define COMPILED_GPIO_CTL

//*****************************************************************************
//
// Generic constants defined here. 
// 
//
//*****************************************************************************

#define MAX_NUM_PORTS   8  //Maximum number of definable ports possible
#define MAX_NUM_PIN     8  //Maximum number of available IO pins per port
#define TOTAL_PORT      MSP_PORT_AVAILABLE  //Total available ports for device
#define TOTAL_PIN		(TOTAL_PORT * MAX_NUM_PIN)  //Total number of available pins for device
#define LOGIC_HIGH		1
#define LOGIC_LOW		0

//*****************************************************************************
//
// GPIO error flags defined here.
// 
//
//*****************************************************************************

#define GPIO_INVALID_CONFIG_ARGUMENT	100
#define GPIO_INVALID_PIN_ID				101
#define GPIO_INVALID_PORT_ACCESS		102

//*****************************************************************************
//
// Port specific constants defined here.
// 
//
//*****************************************************************************

#define OFS_PIN		(0x0000)  //Memory address offset to PxIN register
#define OFS_POUT	(0x0001)  //Memory address offset to PxOUT register
#define OFS_PDIR    (0x0002)  //Memory address offset to PxDIR register
#define OFS_PREN	(0x0007)  //Memory address offset to PxREN register
#define OFS_PSEL_1	(0x0006)  //Memory address offset to PxSEL register
#define OFS_PSEL_2	(0x0004)  //Memory address offset to PxSEL register for port 3 and onwards
#define OFS_IFG		(0x0003)  //Memory address offset to PxIFG register
#define OFS_IE      (0x0005)  //Memory address offset to PxIE register



//GPIO Configuration settings
#define SET_AS_OUTPUT		0  //GPIO config, set pin as output
#define SET_AS_INPUT		1  //GPIO config, set pin as input
#define ENABLE_PULL			2  //GPIO config, enable pin pull resistor
#define DISABLE_PULL		3  //GPIO config, disable pin pull resistor


//*****************************************************************************
//
// MSP pin ID are defined here, use these to select desired pin for gpio 
// functions.
//
//*****************************************************************************

#define MSP_PORT_IO0    (0x01)
#define MSP_PORT_IO1    (0x01 << 1)
#define MSP_PORT_IO2    (0x01 << 2)
#define MSP_PORT_IO3    (0x01 << 3)
#define MSP_PORT_IO4    (0x01 << 4)
#define MSP_PORT_IO5    (0x01 << 5)
#define MSP_PORT_IO6    (0x01 << 6)
#define MSP_PORT_IO7    (0x01 << 7)

//*****************************************************************************
//
// MSP port ID are defined here, use these to select desired port for gpio 
// functions.
//
//*****************************************************************************

#define MSP_PORT1    1
#define MSP_PORT2    2
#define MSP_PORT3    3
#define MSP_PORT4    4
#define MSP_PORT5    5
#define MSP_PORT6    6
#define MSP_PORT7    7
#define MSP_PORT8    8

//*****************************************************************************
//
// Generic pin ID defined here, use these to configure the indivdual pin
// settings.
//
//*****************************************************************************

#define GPIO_IOID0		0
#define GPIO_IOID1		1
#define GPIO_IOID2		2
#define GPIO_IOID3		3
#define GPIO_IOID4		4
#define GPIO_IOID5		5
#define GPIO_IOID6		6
#define GPIO_IOID7		7
#define GPIO_IOID8		8
#define GPIO_IOID9		9
#define GPIO_IOID10		10
#define GPIO_IOID11		11
#define GPIO_IOID12		12
#define GPIO_IOID13		13

#ifdef __MSP430_HAS_PORT3_R__
  	#ifdef __MSP430_HAS_PORT3__
    	#error "gpio.h: GPIO_IOID for port 3 and above not defined yet!"
  	#endif
#endif

//*****************************************************************************
//
// GPIO interrupt flag identifier
//
//*****************************************************************************

#define GPIO_IFG0      (0x01)
#define GPIO_IFG1      (0x01 << 1)
#define GPIO_IFG2      (0x01 << 2)
#define GPIO_IFG3      (0x01 << 3)
#define GPIO_IFG4      (0x01 << 4)
#define GPIO_IFG5      (0x01 << 5)
#define GPIO_IFG6      (0x01 << 6)
#define GPIO_IFG7      (0x01 << 7)


typedef struct {
	uint8_t port;
  	uint8_t pin;
} Port_t;

//*****************************************************************************
//
// Function prototype defined here
// 
//*****************************************************************************

static void setOutputPin(uint8_t port, uint8_t pin);
static void setInputPin(uint8_t port, uint8_t pin);
static inline void setPinPull(uint8_t port, uint8_t pin, uint8_t gpio_config);
void GPIO_reset(void);
void GPIO_configurePin(uint8_t gpio_pin_id, uint8_t gpio_config);
void GPIO_pinWrite(uint8_t gpio_pin_id, uint8_t output_value);
uint8_t GPIO_pinRead(uint8_t gpio_pin_id);
void GPIO_Port1_Event_Handler(void);
void GPIO_Port2_Event_Handler(void);

#endif  //_GPIO_H_
