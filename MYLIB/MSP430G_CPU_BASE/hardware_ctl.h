// ******************************************************************************
// *  File: hardware_ctl.h
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
 
#ifndef __HARDWARE_CTL__
#define __HARDWARE_CTL__

#include "libUtility.h"

//*****************************************************************************
//
// Include device specific header file
//
//*****************************************************************************
#include "msp430g2231.h" //Device specific header file defined here

#define COMPILED_HARDWARE_CTL

//*****************************************************************************
//
// MSP Port base address defined here, port availability defined in device
// header file.
//
//*****************************************************************************

#define MSP_PORT_AVAILABLE 0

#ifdef __MSP430_HAS_PORT1_R__   //Check for Port availability
#define MSP430_PORT1_ADDR 0x0020  //Port base address
#undef  MSP_PORT_AVAILABLE
#define MSP_PORT_AVAILABLE 1
#endif

#ifdef __MSP430_HAS_PORT2_R__
#define MSP430_PORT2_ADDR 0x0028
#undef  MSP_PORT_AVAILABLE
#define MSP_PORT_AVAILABLE 2
#endif

#ifdef __MSP430_HAS_PORT3_R__
#define MSP430_PORT3_ADDR 0x0018
#undef  MSP_PORT_AVAILABLE
#define MSP_PORT_AVAILABLE 3
#endif

#ifdef __MSP430_HAS_PORT4_R__
#define MSP430_PORT4_ADDR 0x001c
#undef  MSP_PORT_AVAILABLE
#define MSP_PORT_AVAILABLE 4
#endif

#ifdef __MSP430_HAS_PORT5_R__
#define MSP430_PORT5_ADDR 0x0030
#undef  MSP_PORT_AVAILABLE
#define MSP_PORT_AVAILABLE 5
#endif

#ifdef __MSP430_HAS_PORT6_R__
#define MSP430_PORT6_ADDR 0x0034
#undef  MSP_PORT_AVAILABLE
#define MSP_PORT_AVAILABLE 6
#endif

#ifdef __MSP430_HAS_PORT7_R__
#define MSP430_PORT7_ADDR 0x0038
#undef  MSP_PORT_AVAILABLE
#define MSP_PORT_AVAILABLE 7
#endif

#ifdef __MSP430_HAS_PORT8_R__
#define MSP430_PORT8_ADDR 0x0039
#undef  MSP_PORT_AVAILABLE
#define MSP_PORT_AVAILABLE 8
#endif

//*****************************************************************************
//
// Clock control register base addresses, offset and constants defined here.
//
//*****************************************************************************

//Clock module register addresses
#define DCO_CONTROL_REG_ADDR                 (0x0056)
#define BCS_CONTROL_REG1_ADDR                (0x0057)
#define BCS_CONTROL_REG2_ADDR                (0x0058)
#define BCS_CONTROL_REG3_ADDR                (0x0053)
#define SFR_INTERRUPT_EN_REG_ADDR            (0x0000)
#define SFR_INTERRUPT_FLAG_REG_ADDR          (0x0002)

//Clock frequency calibration data addresses
#define CAL_DCOCTL_1MHZ                      CALDCO_1MHZ  //DCO calibration for 1MHz
#define CAL_BCSCTL1_1MHZ                     CALBC1_1MHZ  //BCSCTL1 calibration for 1MHz

//XT2S source enable
#define XT2S_OFF                             0x80         //Default is off

//LFXT1 mode selection
#define XTS_LOW_FREQUENCY                    0x00         //Low frequency mode
#define XTS_HIGH_FREQUENCY                   0x40         //High frequency mode

//ACLK clock division selection
#define ACLK_DIVIDE_1                        0x00
#define ACLK_DIVIDE_2                        0x10
#define ACLK_DIVIDE_4                        0x20
#define ACLK_DIVIDE_8                        0x30

//MCLK clock source selection
#define MCLK_SOURCE_DEFAULT                  0x00         //Chip default
#define MCLK_SOURCE_DCOCLK                   MCLK_SOURCE_DEFAULT
#define MCLK_SOURCE_XT2CLK                   0x80
#define MCLK_SOURCE_LFXT1CLK                 0xC0

//MCLK clock division selection
#define MCLK_DIVIDE_1                        0x00         //Chip default
#define MCLK_DIVIDE_2                        0x10
#define MCLK_DIVIDE_4                        0x80
#define MCLK_DIVIDE_8                        0xC0

//SMCLK clock source selection
#define SMCLK_SOURCE_DCOCLK                  0x00         //Chip default
#define SMCLK_SOURCE_XT2CLK                  0x08

//SMCLK clock division selection
#define SMCLK_DIVIDE_1                       0x00         //Chip default
#define SMCLK_DIVIDE_2                       0x02
#define SMCLK_DIVIDE_4                       0x04
#define SMCLK_DIVIDE_8                       0x06

//XT2S Frequency range selection
#define XT2S_RANGE_1MHZ                      0x00         //0.4 to 1-MHz crystal or resonator (Chip default)
#define XT2S_RANGE_3MHZ                      0x40         //1.0 to 3-MHz crystal or resonator
#define XT2S_RANGE_16MHZ                     0x80         //3.0 to 16-MHz crystal or resonator
#define XT2S_RANGE_DIGITAL_SRC               0xC0         //Digital external 0.4- to 16-MHz clock source

//Low-frequency clock select and LFXT1 range select. These bits select between LFXT1 and VLO when XTS =
//0, and select the frequency range for LFXT1 when XTS = 1.
//When XTS = 0:
//00 32768-Hz crystal on LFXT1
//01 Reserved
//10 VLOCLK (Reserved in MSP430F21x1 devices)
//11 Digital external clock source
//When XTS = 1 (Not applicable for MSP430x20xx devices, MSP430G2xx1/2/3)
//00 0.4- to 1-MHz crystal or resonator
//01 1- to 3-MHz crystal or resonator
//10 3- to 16-MHz crystal or resonator
//11 Digital external 0.4- to 16-MHz clock source

#define LFXT1S_RANGE_1MHZ                    0x00
#define LFXT1S_RANGE_3MHZ                    0x10
#define LFXT1S_RANGE_16MHZ                   0x20
#define LFXT1S_RANGE_DIGITAL_SRC             0x30

//XT2S internal clock capacitor config
#define XCAP_1PF                             0x00
#define XCAP_6PF                             0x04
#define XCAP_10PF                            0x08
#define XCAP_12_5PF                          0x0C

//XT2S and LFXT1 clock fault flag mask
#define XT2S_FAULT_MASK                      0x02
#define LFXT1_FAULT_MASK                     0x01

//Clock register configuration defined here, this constant is loaded to the register
//on start up.

#define DCOCTL_STARTUP_CONFIG                CAL_DCOCTL_1MHZ
#define BCSCTL1_STARTUP_CONFIG               (CAL_BCSCTL1_1MHZ + XT2S_OFF + XTS_LOW_FREQUENCY + ACLK_DIVIDE_1)
#define BCSCTL2_STARTUP_CONFIG               (MCLK_SOURCE_DEFAULT + MCLK_DIVIDE_1 + SMCLK_SOURCE_DCOCLK + SMCLK_DIVIDE_1)
#define BCSCTL3_STARTUP_CONFIG               (XT2S_RANGE_1MHZ + LFXT1S_RANGE_1MHZ + XCAP_1PF)

//*****************************************************************************
//
// Timer peripheral control register base addresses, offset and constants 
// defined here.
//
//*****************************************************************************

#define TIMERA_TACTL_REG_ADDR                (0x0160)
#define TIMERA_TAR_REG_ADDR                  (0x0170)
#define TIMERA_TACCTL0_REG_ADDR              (0x0162)
#define TIMERA_TACCR0_REG_ADDR               (0x0172)
#define TIMERA_TACCTL1_REG_ADDR              (0x0164)
#define TIMERA_TACCR1_REG_ADDR               (0x0174)
#define TIMERA_TACCTL2_REG_ADDR              (0x0166)
#define TIMERA_TACCR2_REG_ADDR               (0x0176)
#define TIMERA_TAIV_REG_ADDR                 (0x012E)

//Timer A clock source select
#define TIMERA_SOURCE_TACLK                   0x0000
#define TIMERA_SOURCE_ACLK                    0x0100
#define TIMERA_SOURCE_SMCLK                   0x0200
#define TIMERA_SOURCE_INCLK                   0x0C00

//Timer A clock division
#define TIMERA_DIVIDE_1                       0x0000
#define TIMERA_DIVIDE_2                       0x0040
#define TIMERA_DIVIDE_4                       0x0080
#define TIMERA_DIVIDE_8                       0x0C00

//Timer A operating mode
#define TIMERA_MODE_STOP                      0x0000
#define TIMERA_MODE_UPMODE                    0x0010
#define TIMERA_MODE_CONTINUOUS                0x0020
#define TIMERA_MODE_UPDOWN                    0x0030

//Timer A Capture/Compare modes
#define TIMERA_NO_CAPTURE                     0x0000
#define TIMERA_CAP_RISING                     0x4000
#define TIMERA_CAP_FALLING                    0x8000
#define TIMERA_CAP_ALL                        0xC000

//Timer A capture modes
#define TIMERA_COMPARE_MODE                   0x0000
#define TIMERA_CAPTURE_MODE                   0x0100

//Capture and Compare interrupt enable mask
#define TIMERA_CCIE_MASK                      0x0010

//Capture and Compare interrupt flag mask
#define TIMERA_CCIFG_MASK                     0x0001

//Timer A interrupt enable mask
#define TIMERA_TAIE_MASK                      0x0002

//Timer A interrupt flag mask
#define TIMERA_TAIFG_MASK                     0x0001

//Timer A clear bit mask
#define TIMERA_TACLR_MASK                     0x0004

//*****************************************************************************
//
// Hardware error codes
//
//*****************************************************************************

#define HW__EXT_CLOCK_FAULT                   1

//*****************************************************************************
//
// Macros for hardware memory address access
//
//*****************************************************************************
#define HWREG32(x)                                                              \
    (*((volatile uint32_t *)((uint16_t)x)))
#define HWREG16(x)                                                             \
    (*((volatile uint16_t *)((uint16_t)x)))
#define HWREG8(x)                                                             \
    (*((volatile uint8_t *)((uint16_t)x)))

//*****************************************************************************
//
// Function prototypes defined here
//
//*****************************************************************************

void HW__InitialiseSystem(void);
void HW__EnterLowpower(void);
void HW__EnterDeepSleep(void);

#endif  //__HARDWARE_CTL__
