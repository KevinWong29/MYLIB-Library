// *****************************************************************************
// *  File: gpio.c
// *
// *  Purpose:                                                                         
// *  Basic GPIO driver and wrapper functions are defined here in this module.
// *
// *  By: Kevin Wong
// *  Revision 1.0
// *  Date: 27/08/2016  
// *
// *
// *
// *****************************************************************************

#include "gpio.h"
#include "main.h"

#if defined(__MSP430_HAS_PORT1_R__) || defined(__MSP430_HAS_PORT2_R__) || \
    defined(__MSP430_HAS_PORTA_R__)

static const uint16_t GPIO_Port_To_Base[] = {
    0x00,
#if defined(__MSP430_HAS_PORT1_R__)
    MSP430_PORT1_ADDR,
#else
    0xFFFF,
#endif
#if defined(__MSP430_HAS_PORT2_R__)
    MSP430_PORT2_ADDR,
#else
    0xFFFF,
#endif
#if defined(__MSP430_HAS_PORT3_R__)
    MSP430_PORT3_ADDR,
#else
    0xFFFF,
#endif
#if defined(__MSP430_HAS_PORT4_R__)
    MSP430_PORT4_ADDR,
#else
    0xFFFF,
#endif
#if defined(__MSP430_HAS_PORT5_R__)
    MSP430_PORT5_ADDR,
#else
    0xFFFF,
#endif
#if defined(__MSP430_HAS_PORT6_R__)
    MSP430_PORT6_ADDR,
#else
    0xFFFF,
#endif
#if defined(__MSP430_HAS_PORT7_R__)
    MSP430_PORT7_ADDR,
#else
    0xFFFF,
#endif
#if defined(__MSP430_HAS_PORT8_R__)
    MSP430_PORT8_ADDR,
#else
    0xFFFF,
#endif
    (MAX_NUM_PORTS + 1)  //Array size stored here
};

#else
    #error "gpio.c: Device IO ports not avaailable!"
#endif

//*****************************************************************************
// Purpose: Inline function to map generic IO pin id to specific device port and pin.
// Argument: Generic IO ID
// Return: io_port (struct)
//         port - Device port mapped with generic pin ID
//         pin - Device pin mapped to generic pin ID
//
//*****************************************************************************

static inline Port_t map_id_to_port(uint8_t generic_pin_id) 
{
    Port_t io_port;

    //Derive port from pin ID
    io_port.port = (uint8_t)(generic_pin_id/MAX_NUM_PIN) + 1;

    //Derive pin from pin ID
    io_port.pin = generic_pin_id - (MAX_NUM_PIN*(io_port.port-1));

    return io_port;
}

//*****************************************************************************
// Purpose: This function configures the specified pin as output.
// Argument: port - Device port for which pin resides
//           pin - Device pin for which to set
// Return: None
//
//*****************************************************************************

static void setOutputPin(uint8_t port, uint8_t pin) 
{
    uint8_t index;
    uint16_t base_address;
  
    //Check port and pin validity
    if(port <= MAX_NUM_PORTS) 
    {
        if(pin <= MAX_NUM_PIN) 
        {
            index = port;
            base_address = GPIO_Port_To_Base[index];
      
            //Configure register
            if(base_address != 0xFFFF) 
            {
                HWREG16(base_address + OFS_PDIR) |= (1 << pin);
            }
        }
    }
}

//*****************************************************************************
//
// Purpose: This function configures the specified pin as input.
// Argument: port - Device port for which pin resides
//           pin - Device pin for which to set
// Return: None
//
//*****************************************************************************

static void setInputPin(uint8_t port, uint8_t pin) 
{
    uint8_t index;
    uint16_t base_address;

    //Check port and pin validity
    if((port <= MAX_NUM_PORTS) && (port > 0)) 
    {
        if((pin <= MAX_NUM_PIN) && (pin > 0)) 
        {
            index = port;
      
            base_address = GPIO_Port_To_Base[index];
      
            //Configure register
            if(base_address != 0xFFFF) 
            {
                HWREG16(base_address + OFS_PDIR) &= ~(1 << pin);
            }
        }
    }
}

//*****************************************************************************
//
// Purpose: This function configures the specified pin internal resistor pull
//          configurations.
// Argument: port - Device port for which pin resides
//           pin - Device pin for which to set
//           gpio_config - set value
//                         ENABLE_PULL - Enable pull resistor
//                         DISABLE_PULL - Disable pull resistors
// Return: None
//
//*****************************************************************************

static inline void setPinPull(uint8_t port, uint8_t pin, uint8_t gpio_config) 
{
    uint16_t base_address = GPIO_Port_To_Base[port];

    if(base_address != 0xFFFF) 
    {
        if(gpio_config == ENABLE_PULL) 
        {

            //Enable pin pull resistor register
            HWREG16(base_address + OFS_PREN) |= (1 << pin);
        }
        else if(gpio_config == DISABLE_PULL) 
        {

            //Disable pin pull resistor register
            HWREG16(base_address + OFS_PREN) &= ~(1 << pin);
        }
    }
    else 
    {
        LIBUTIL__LogError(GPIO_INVALID_PORT_ACCESS);
    } 
}


//*****************************************************************************
//
// Purpose: Reset and initialises the GPIO registers.
// Argument None
// Return: None
//
//*****************************************************************************

void GPIO_reset(void) 
{
    uint16_t base_address;
    uint8_t index;

    for(index = 0; index < MSP_PORT_AVAILABLE; index++) 
    {
        base_address = GPIO_Port_To_Base[index];

        //Set all pin status and state to input as per pin reset state
        HWREG16(base_address + OFS_PDIR) = 0;

        //Set all pin output values to LOW
        HWREG16(base_address + OFS_POUT) = 0;

        //Set all pin status and state to have internal pull resistors disabled
        HWREG16(base_address + OFS_PREN) = 0;
    }
}

//*****************************************************************************
//
// Purpose: This function configures the specified pin direction and internal
// pull resistors.
// Argument: gpio_pin_id - Generic IO ID
//           gpio_config - Configuration to configure
// Return: None
//
//*****************************************************************************

void GPIO_configurePin(uint8_t gpio_pin_id, uint8_t gpio_config) 
{
    Port_t io_port;

    if((gpio_pin_id < TOTAL_PIN) && (gpio_config <= DISABLE_PULL)) 
    {

        //Decode required device port and pin
        io_port = map_id_to_port(gpio_pin_id);

        switch(gpio_config) 
        {

            case SET_AS_OUTPUT:
                setOutputPin(io_port.port, io_port.pin);
                break;

            case SET_AS_INPUT:
                setInputPin(io_port.port, io_port.pin);
                break;

            case ENABLE_PULL:
                setPinPull(io_port.port, io_port.pin, ENABLE_PULL);
                break;

            case DISABLE_PULL:
                setPinPull(io_port.port, io_port.pin, DISABLE_PULL);
                break;

            default:
                LIBUTIL__LogError(GPIO_INVALID_CONFIG_ARGUMENT);
        }
    }
    else 
    {
        LIBUTIL__LogError(GPIO_INVALID_CONFIG_ARGUMENT);
    }
}

//*****************************************************************************
//
// Purpose: This function writes digital value to specified pin.
// Argument: gpio_pin_id - Generic IO ID
//           output_value - logical value specified to be set to output
//                          (LOGIC_HIGHH) - output HIGH
//                          (LOGIC_LOW) - output LOW
// Return: None
//
//*****************************************************************************

void GPIO_pinWrite(uint8_t gpio_pin_id, uint8_t output_value) 
{
    Port_t io_port;

    if(gpio_pin_id <= GPIO_IOID13) 
    {
        //Decode required device port and pin
        io_port = map_id_to_port(gpio_pin_id);

        if(output_value == LOGIC_HIGH) 
        {
            HWREG16(GPIO_Port_To_Base[io_port.port] + OFS_POUT) |= (1 << io_port.pin);
        }
        else if(output_value == LOGIC_LOW) 
        {
            HWREG16(GPIO_Port_To_Base[io_port.port] + OFS_POUT) &= ~(1 << io_port.pin);
        }
    }
    else 
    {
        //Do nothing
    }
}

//*****************************************************************************
//
// Purpose: This function reads digital value from specified pin.
// Argument: gpio_pin_id - Generic IO ID
// Return: Pin input logical value as a byte, a zero for LOW and none zero
// for a HIGH. THis byte can be bit tested to determine the pin
//
//*****************************************************************************

uint8_t GPIO_pinRead(uint8_t gpio_pin_id) 
{
    Port_t io_port;
    uint8_t pin_val = 0;

    if(gpio_pin_id <= GPIO_IOID13) 
    {
        //Decode required device port and pin
        io_port = map_id_to_port(gpio_pin_id);

        pin_val = HWREG16(GPIO_Port_To_Base[io_port.port] + OFS_PIN) & (1 << io_port.pin);
    }
    else 
    {
        //Do nothing
    }

    return pin_val;
}

//*****************************************************************************
//
// Purpose: GPIO interrupt event handler for port 1.
// Argument: None
// Return: None
//
//*****************************************************************************

void GPIO_Port1_Event_Handler(void) 
{
    uint8_t interrupt_flg = 0;

    interrupt_flg = HWREG8(GPIO_Port_To_Base[1] + OFS_IFG) & 0xFF;  //Copy the content the ports interrupt flag register

    //Determine the interrupt source pin and perform required task for that pin
    //also check that the associated pin has interrupt enable
    if((interrupt_flg & GPIO_IFG0) && (HWREG8(GPIO_Port_To_Base[1] + OFS_IE) & GPIO_IFG0)) 
    {
        //Do something
    }

    if((interrupt_flg & GPIO_IFG1) && (HWREG8(GPIO_Port_To_Base[1] + OFS_IE) & GPIO_IFG1)) 
    {
        //Do something
    }

    if((interrupt_flg & GPIO_IFG2) && (HWREG8(GPIO_Port_To_Base[1] + OFS_IE) & GPIO_IFG2)) 
    {
        //Do something
    }

    if((interrupt_flg & GPIO_IFG3) && (HWREG8(GPIO_Port_To_Base[1] + OFS_IE) & GPIO_IFG3)) 
    {
        //Do something
    }

    if((interrupt_flg & GPIO_IFG4) && (HWREG8(GPIO_Port_To_Base[1] + OFS_IE) & GPIO_IFG4)) 
    {
        //Do something
    }

    if((interrupt_flg & GPIO_IFG5) && (HWREG8(GPIO_Port_To_Base[1] + OFS_IE) & GPIO_IFG5)) 
    {
        //Do something
    }

    if((interrupt_flg & GPIO_IFG6) && (HWREG8(GPIO_Port_To_Base[1] + OFS_IE) & GPIO_IFG6)) 
    {
        //Do something
    }

    if((interrupt_flg & GPIO_IFG7) && (HWREG8(GPIO_Port_To_Base[1] + OFS_IE) & GPIO_IFG7)) 
    {
        //Do something
    }

    HWREG8(GPIO_Port_To_Base[1] + OFS_IFG) &= 0x00;  //Clear the interrupt flag, all interrupts have been handled
}

//*****************************************************************************
//
// Purpose: GPIO interrupt event handler for port 2.
// Argument: None
// Return: None
//
//*****************************************************************************

void GPIO_Port2_Event_Handler(void) 
{
    uint8_t interrupt_flg = 0;

    interrupt_flg = HWREG8(GPIO_Port_To_Base[2] + OFS_IFG) & 0xFF;  //Copy the content the ports interrupt flag register

    //Determine the interrupt source pin and perform required task for that pin
    //also check that the associated pin has interrupt enable
    if((interrupt_flg & GPIO_IFG0) && (HWREG8(GPIO_Port_To_Base[2] + OFS_IE) & GPIO_IFG0)) 
    {
        //Do something
    }

    if((interrupt_flg & GPIO_IFG1) && (HWREG8(GPIO_Port_To_Base[2] + OFS_IE) & GPIO_IFG1)) 
    {
        //Do something
    }

    if((interrupt_flg & GPIO_IFG2) && (HWREG8(GPIO_Port_To_Base[2] + OFS_IE) & GPIO_IFG2)) 
    {
        //Do something
    }

    if((interrupt_flg & GPIO_IFG3) && (HWREG8(GPIO_Port_To_Base[2] + OFS_IE) & GPIO_IFG3)) 
    {
        //Do something
    }

    if((interrupt_flg & GPIO_IFG4) && (HWREG8(GPIO_Port_To_Base[2] + OFS_IE) & GPIO_IFG4)) 
    {
        //Do something
    }

    if((interrupt_flg & GPIO_IFG5) && (HWREG8(GPIO_Port_To_Base[2] + OFS_IE) & GPIO_IFG5)) 
    {
        //Do something
    }

    if((interrupt_flg & GPIO_IFG6) && (HWREG8(GPIO_Port_To_Base[2] + OFS_IE) & GPIO_IFG6)) 
    {
        //Do something
    }

    if((interrupt_flg & GPIO_IFG7) && (HWREG8(GPIO_Port_To_Base[2] + OFS_IE) & GPIO_IFG7)) 
    {
        //Do something
    }

    HWREG8(GPIO_Port_To_Base[2] + OFS_IFG) &= 0x00;  //Clear the interrupt flag, all interrupts have been handled
}


