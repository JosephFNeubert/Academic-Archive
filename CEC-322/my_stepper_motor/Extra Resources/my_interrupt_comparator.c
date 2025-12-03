//*****************************************************************************
//
// timers.c - Timers example.
//
// Copyright (c) 2011-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the DK-TM4C123G Firmware Package.
//
//*****************************************************************************

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/rom.h"
#include "grlib/grlib.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/adc.h"
#include "driverlib/comp.h"
#include "drivers/cfal96x64x16.h"

#define LEDDelay 750000
#define splashScreenDelay 8000000 

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Timer (timers)</h1>
//!
//! This example application demonstrates the use of the timers to generate
//! periodic interrupts.  One timer is set up to interrupt once per second and
//! the other to interrupt twice per second; each interrupt handler will toggle
//! its own indicator on the display.
//
//*****************************************************************************

//*****************************************************************************
//
// Flags that contain the current value of the interrupt indicator as displayed
// on the CSTN display.
//
//*****************************************************************************
uint32_t g_ui32Flags;

//*****************************************************************************
//
// Graphics context used to show text on the CSTN display.
//
//*****************************************************************************
tContext g_sContext;
tRectangle sRect;

// Global Variables
volatile uint32_t ui32Loop;
uint32_t buttonCount;
uint32_t voltCrossingsCount;
char buffer[16];

// ADC Reading Global Variable
uint32_t ui32ADCValue;

// Process Menu Function Prototype
void process_menu(char c);

// Show Splash Screen Prototype
void show_splash_screen();

// Print UART Menu Prototype
void UART_send_menu();

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

//*****************************************************************************
//
// Send a string to the UART.
//
//*****************************************************************************
void
UARTSend(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--)
    {
        //
        // Write the next character to the UART.
        //
        UARTCharPut(UART0_BASE, *pui8Buffer++);
    }
}

//*****************************************************************************
//
// The UART interrupt handler.
//
//*****************************************************************************
void
UARTIntHandler(void)
{
    uint32_t ui32Status;

    //
    // Get the interrrupt status.
    //
    ui32Status = ROM_UARTIntStatus(UART0_BASE, true);

    //
    // Clear the asserted interrupts.
    //
    UARTIntClear(UART0_BASE, ui32Status);
    
    int32_t local_char;
    while (UARTCharsAvail(UART0_BASE)) 
    {
      local_char = UARTCharGetNonBlocking(UART0_BASE);
        
      if (local_char != -1) 
      {
        process_menu(local_char);
      }
   }
}

//*****************************************************************************
//
// The GPIO Base M interrupt handler (push buttons).
//
//*****************************************************************************
void
GPIOMIntHandler(void) 
{
  // Get interrupt status and clear asserted interrupt
  uint32_t ui32Status;
  ui32Status = GPIOIntStatus(GPIO_PORTM_BASE, true);
  GPIOIntClear(GPIO_PORTM_BASE, ui32Status);
  
  buttonCount++;
  IntMasterDisable();
  GrContextForegroundSet(&g_sContext, ClrWhite);
  sprintf(buffer, "   C: %d   ", buttonCount);
  GrStringDrawCentered(&g_sContext, buffer, -1, GrContextDpyWidthGet(&g_sContext) / 2, GrContextDpyHeightGet(&g_sContext) / 8, 1);
  
  if (GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_0) == 0)
  {
    GrStringDrawCentered(&g_sContext, "  Up  ", -1, GrContextDpyWidthGet(&g_sContext) / 2, GrContextDpyHeightGet(&g_sContext) / 4, 1);
  }
  if (GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_1) == 0) 
  {
    GrStringDrawCentered(&g_sContext, " Down ", -1, GrContextDpyWidthGet(&g_sContext) / 2, GrContextDpyHeightGet(&g_sContext) / 4, 1);
  }
  if (GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_2) == 0) 
  {
    GrStringDrawCentered(&g_sContext, " Left ", -1, GrContextDpyWidthGet(&g_sContext) / 2, GrContextDpyHeightGet(&g_sContext) / 4, 1);
  }
  if (GPIOPinRead(GPIO_PORTM_BASE, GPIO_PIN_3) == 0) 
  {
    GrStringDrawCentered(&g_sContext, " Right", -1, GrContextDpyWidthGet(&g_sContext) / 2, GrContextDpyHeightGet(&g_sContext) / 4, 1);
  }
  IntMasterEnable();
}

//*****************************************************************************
//
// The comparator interrupt handler.
//
//*****************************************************************************
void
ComparatorIntHandler(void) 
{
  // Clear interrupt status
  ComparatorIntClear(COMP_BASE, 0);
  
  voltCrossingsCount++;
  sprintf(buffer, "Comp: %d", voltCrossingsCount);
  IntMasterDisable();
  GrContextForegroundSet(&g_sContext, ClrWhite);
  GrStringDrawCentered(&g_sContext, buffer, -1, GrContextDpyWidthGet(&g_sContext) / 2, GrContextDpyHeightGet(&g_sContext) / 2, 1);
  if (ComparatorValueGet(COMP_BASE, 0) == true) 
  {
    GrStringDrawCentered(&g_sContext, " Bright ", -1, GrContextDpyWidthGet(&g_sContext) / 2, (int)(GrContextDpyHeightGet(&g_sContext) / 1.5), 1);
  }
  else if (ComparatorValueGet(COMP_BASE, 0) == false)
  {
    GrStringDrawCentered(&g_sContext, " Dark ", -1, GrContextDpyWidthGet(&g_sContext) / 2, (int)(GrContextDpyHeightGet(&g_sContext) / 1.5), 1);
  }
  IntMasterEnable();
}

//*****************************************************************************
//
// This example application demonstrates the use of the timers to generate
// periodic interrupts.
//
//*****************************************************************************
int
main(void)
{
    IntMasterDisable();
   
    //
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    ROM_FPULazyStackingEnable();

    //
    // Set the clocking to run directly from the crystal.
    // COMMENT OUT AND USE ONE CLOCK OR THE OTHER
    //
    // 16 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    
    // 80 MHz
    //SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    
    //
    // Initialize the display driver.
    //
    CFAL96x64x16Init();

    //
    // Initialize the graphics context and find the middle X coordinate.
    //
    GrContextInit(&g_sContext, &g_sCFAL96x64x16);
    
    // Enable, check, and configure PG2 for LED.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOG)) {}
    GPIOPinTypeGPIOOutput (GPIO_PORTG_BASE, GPIO_PIN_2);
    
    // Enable and configure ADC.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)) {}
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_2);
    ADCSequenceDisable (ADC0_BASE, 0);
    ADCSequenceConfigure (ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure (ADC0_BASE, 0, 0, ADC_CTL_CH13 | ADC_CTL_END); // AIN-13 is PD2
    ADCSequenceEnable (ADC0_BASE, 0);
    
    // Enable, check, and configure PM0, PM1, PM2, PM3 for up, down, left, and right push buttons.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM)) {}
    GPIOPinTypeGPIOInput(GPIO_PORTM_BASE, GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTM_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPinTypeGPIOInput(GPIO_PORTM_BASE, GPIO_PIN_1);
    GPIOPadConfigSet(GPIO_PORTM_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPinTypeGPIOInput(GPIO_PORTM_BASE, GPIO_PIN_2);
    GPIOPadConfigSet(GPIO_PORTM_BASE, GPIO_PIN_2, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    GPIOPinTypeGPIOInput(GPIO_PORTM_BASE, GPIO_PIN_3);
    GPIOPadConfigSet(GPIO_PORTM_BASE, GPIO_PIN_3, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    
    // Enable, check, and configure PC6 and PC7 for the analog comparator. PC7 is reference voltage, PC6
    SysCtlPeripheralEnable(SYSCTL_PERIPH_COMP0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_COMP0)) {}
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOC)) {}
    GPIOPinTypeComparator(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);
    ComparatorConfigure(COMP_BASE, 0, COMP_TRIG_NONE | COMP_INT_BOTH | COMP_ASRCP_PIN0 | COMP_OUTPUT_NORMAL);
    
    // Display initial splash screen
    show_splash_screen();

    //
    // Change foreground for white text.
    //
    GrContextForegroundSet(&g_sContext, ClrWhite);

    //
    // Initialize timer status display.
    //
    GrContextFontSet(&g_sContext, g_psFontFixed6x8);

    //
    // Enable processor interrupts.
    //
    IntMasterEnable();

    // Enable and configure UART
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) {}
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));

    //
    // Setup and enable the interrupts in NVIC and peripherals.
    //
    // UART Interrupts
    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    
    // GPIO Button Interrupts
    IntEnable(INT_GPIOM);
    GPIOIntTypeSet(GPIO_PORTM_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3, GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTM_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    
    // Comparator Interrupts
    IntEnable(INT_COMP0);
    //ComparatorIntEnable(COMP_BASE, 0);
    
    //
    // Dynamically register ISR functions.
    //
    UARTIntRegister(UART0_BASE, UARTIntHandler);
    GPIOIntRegister(GPIO_PORTM_BASE, GPIOMIntHandler);
    ComparatorIntRegister(COMP_BASE, 0, ComparatorIntHandler);
    
    //
    // UART Start Menu
    //
    UART_send_menu();

    //
    // Application code (loops forever)
    //
    while(1)
    { 
      // Blinking LED heartbeat
      for (ui32Loop = 0; ui32Loop < LEDDelay; ui32Loop++) {}
      GPIOPinWrite (GPIO_PORTG_BASE, GPIO_PIN_2, GPIO_PIN_2);
      for (ui32Loop = 0; ui32Loop < LEDDelay; ui32Loop++) {}
      GPIOPinWrite (GPIO_PORTG_BASE, GPIO_PIN_2, 0);
    }
}

//
// Function definitions
//
void process_menu(char c) 
{
  if (c == 'M') 
  {
    UART_send_menu();
  }
  
  if (c == 'S') 
  {
    IntMasterDisable();
    show_splash_screen();
    IntMasterEnable();
  }
}

void show_splash_screen() 
{
  char sysClockRate[16];
  sprintf(sysClockRate, "CLK: %d", SysCtlClockGet());
  sRect.i16XMin = 0;
  sRect.i16YMin = 0;
  sRect.i16XMax = GrContextDpyWidthGet(&g_sContext);
  sRect.i16YMax = GrContextDpyHeightGet(&g_sContext);
  GrContextForegroundSet(&g_sContext, ClrDarkBlue);
  GrRectFill(&g_sContext, &sRect);
  GrContextForegroundSet(&g_sContext, ClrWhite);
  GrContextFontSet(&g_sContext, g_psFontFixed6x8);
  GrStringDrawCentered(&g_sContext, "Lab 6: Compare", -1,
                       GrContextDpyWidthGet(&g_sContext) / 2, 20, 0);
  GrStringDrawCentered(&g_sContext, "Joseph Neubert", -1,
                       GrContextDpyWidthGet(&g_sContext) / 2, 30, 0);
  GrStringDrawCentered(&g_sContext, sysClockRate, -1, 
                       GrContextDpyWidthGet(&g_sContext) / 2, 40, 0);
  for (ui32Loop = 0; ui32Loop < splashScreenDelay; ui32Loop++) {}
  GrContextForegroundSet(&g_sContext, ClrBlack);
  GrRectFill(&g_sContext, &sRect);
}

void UART_send_menu() 
{
  UARTSend ((uint8_t *)"\r\nMENU\r\n", 8);
  UARTSend ((uint8_t *)"Show Slpash Screen - S\r\n", 26);
  UARTSend ((uint8_t *)"Print Menu - M\r\n", 18);
}