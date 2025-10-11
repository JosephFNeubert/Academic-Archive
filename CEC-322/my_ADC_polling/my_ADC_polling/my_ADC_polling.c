//*****************************************************************************
//
// uart_echo.c - Example for reading data from and writing data to the UART in
//               an interrupt driven fashion.
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

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/adc.h"
#include "driverlib/rom.h"
#include "grlib/grlib.h"
#include "drivers/cfal96x64x16.h"

#define floodDelay 1000000
#define LEDDelay 750000
#define splashScreenDelay 8000000 
#define ADCBarUpdateDelay 4000

bool running = true;
bool LEDToggled = false;

bool ADCToggled1 = false;
bool ADCToggled2 = false;
bool ADCToggled3 = false;
bool ADCToggled4 = false;
bool ADCToggled5 = false;
bool ADCToggled6 = false;

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>UART Echo (uart_echo)</h1>
//!
//! This example application utilizes the UART to echo text.  The first UART
//! (connected to the USB debug virtual serial port on the evaluation board)
//! will be configured in 115,200 baud, 8-n-1 mode.  All characters received on
//! the UART are transmitted back to the UART.
//
//*****************************************************************************

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
    ROM_UARTIntClear(UART0_BASE, ui32Status);

    //
    // Loop while there are characters in the receive FIFO.
    //
    while(ROM_UARTCharsAvail(UART0_BASE))
    {
        //
        // Read the next character from the UART and write it back to the UART.
        //
        ROM_UARTCharPutNonBlocking(UART0_BASE,
                                   ROM_UARTCharGetNonBlocking(UART0_BASE));
    }
}

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

// Global elements
tContext sContext;
tRectangle sRect;
volatile uint32_t ui32Loop;

// ADC Values for 3 Channels
uint32_t ui32ADCValue1;
uint32_t ui32ADCValue2;
uint32_t ui32ADCValue3;

// My function prototypes
void process_menu (int32_t c);

//*****************************************************************************
//
// This example demonstrates how to send a string of data to the UART.
//
//*****************************************************************************
int
main(void)
{
    //
    // Enable lazy stacking for interrupt handlers.  This allows floating-point
    // instructions to be used within interrupt handlers, but at the expense of
    // extra stack usage.
    //
    FPULazyStackingEnable();

    //
    // Set the clocking to run directly from the crystal.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                       SYSCTL_XTAL_16MHZ);
    
    // Enable, check, and configure LED (PG2)
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOG);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOG)) {}
    GPIOPinTypeGPIOOutput (GPIO_PORTG_BASE, GPIO_PIN_2);
    
    // Enable, check, and configure ADC port and pins
    SysCtlPeripheralEnable (SYSCTL_PERIPH_ADC0);       
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)) {}
    SysCtlPeripheralEnable (SYSCTL_PERIPH_GPIOD);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)) {}
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_2);  // AIN-13
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_3);  // AIN-12
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_4);  // AIN-7
    
    // Retrieve values from the 3 analog input channels. Create a single ADC sequence.
    // Channel 1
    ADCSequenceDisable (ADC0_BASE, 0);
    ADCSequenceConfigure (ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure (ADC0_BASE, 0, 0, ADC_CTL_CH13 | ADC_CTL_END);
    ADCSequenceEnable (ADC0_BASE, 0);
    // Channel 2
    ADCSequenceDisable (ADC0_BASE, 1);
    ADCSequenceConfigure (ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure (ADC0_BASE, 1, 0, ADC_CTL_CH12 | ADC_CTL_END);
    ADCSequenceEnable (ADC0_BASE, 1);
    // Channel 3
    ADCSequenceDisable (ADC0_BASE, 2);
    ADCSequenceConfigure (ADC0_BASE, 2, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure (ADC0_BASE, 2, 0, ADC_CTL_CH7 | ADC_CTL_END);
    ADCSequenceEnable (ADC0_BASE, 2);
    
    //
    // Initialize the display driver.
    //
    CFAL96x64x16Init();

    //
    // Initialize the graphics context.
    //
    GrContextInit(&sContext, &g_sCFAL96x64x16);

    // Display initial splash screen
    sRect.i16XMin = 0;
    sRect.i16YMin = 0;
    sRect.i16XMax = GrContextDpyWidthGet(&sContext);
    sRect.i16YMax = GrContextDpyHeightGet(&sContext);
    GrContextForegroundSet(&sContext, ClrDarkBlue);
    GrRectFill(&sContext, &sRect);
    GrContextForegroundSet(&sContext, ClrWhite);
    GrContextFontSet(&sContext, g_psFontFixed6x8);
    GrStringDrawCentered(&sContext, "Lab 3: ADC", -1,
                         GrContextDpyWidthGet(&sContext) / 2, 20, 0);
    GrStringDrawCentered(&sContext, "Joseph Neubert", -1,
                         GrContextDpyWidthGet(&sContext) / 2, 30, 0);
    for (ui32Loop = 0; ui32Loop < splashScreenDelay; ui32Loop++) {}
    GrContextForegroundSet(&sContext, ClrBlack);
    GrRectFill(&sContext, &sRect);
    
    //
    // Fill the top part of the screen with blue to create the banner.
    //
    sRect.i16XMin = 0;
    sRect.i16YMin = 0;
    sRect.i16XMax = GrContextDpyWidthGet(&sContext) - 1;
    sRect.i16YMax = 9;
    GrContextForegroundSet(&sContext, ClrDarkBlue);
    GrRectFill(&sContext, &sRect);

    //
    // Change foreground for white text.
    //
    GrContextForegroundSet(&sContext, ClrWhite);

    //
    // Put the application name in the middle of the banner.
    //
    GrContextFontSet(&sContext, g_psFontFixed6x8);
    GrStringDrawCentered(&sContext, "Neubert ADC", -1,
                         GrContextDpyWidthGet(&sContext) / 2, 4, 0);

    //
    // Initialize the display and write some instructions.
    //
    GrStringDrawCentered(&sContext, "Connect a", -1,
                         GrContextDpyWidthGet(&sContext) / 2, 20, false);
    GrStringDrawCentered(&sContext, "terminal", -1,
                         GrContextDpyWidthGet(&sContext) / 2, 30, false);
    GrStringDrawCentered(&sContext, "to UART0.", -1,
                         GrContextDpyWidthGet(&sContext) / 2, 40, false);
    GrStringDrawCentered(&sContext, "115200,N,8,1", -1,
                         GrContextDpyWidthGet(&sContext) / 2, 50, false);
    for (ui32Loop = 0; ui32Loop < splashScreenDelay; ui32Loop++) {}
    sRect.i16XMin = 0;
    sRect.i16YMin = 0;
    sRect.i16XMax = GrContextDpyWidthGet(&sContext);
    sRect.i16YMax = GrContextDpyHeightGet(&sContext);
    GrContextForegroundSet(&sContext, ClrBlack);
    GrRectFill(&sContext, &sRect);

    //
    // Enable the peripherals used by this example.
    //
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    
    //
    // Enable processor interrupts. (DISABLED)
    //
    // IntMasterEnable();
    
    //
    // Set GPIO A0 and A1 as UART pins.
    //
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    //
    // Configure the UART for 115,200, 8-N-1 operation.
    //
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));
    
    //
    // Enable the UART interrupt. (DISABLED)
    //
    // IntEnable(INT_UART0);
    // UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);

    //
    // Prompt for text to be entered. (DISABLED)
    //
    // UARTSend((uint8_t *)"Enter text: ", 12);
    
    // Prompt Menu
    UARTSend ((uint8_t *)"\r\nMENU\r\n", 8);
    UARTSend ((uint8_t *)"Show Slpash Screen - S\r\n", 26);
    UARTSend ((uint8_t *)"Print Menu - M\r\n", 18);
    UARTSend ((uint8_t *)"Quit Program - Q\r\n", 20);
    UARTSend ((uint8_t *)"Toggle LED - L\r\n", 18);
    UARTSend ((uint8_t *)"Clear Terminal - C\r\n", 22);
    UARTSend ((uint8_t *)"ADC Measurements - 1-2, 3-4, 5-6\r\n", 36);
    UARTSend ((uint8_t *)"Show ADC number and bar graph respectively for\r\n", 50);
    UARTSend ((uint8_t *)"ADC 1, 2, and 3 respectively\r\n", 32); 
    UARTSend ((uint8_t *)"SELECTION: ", 11);
    
    // Track number of characters in the terminal
    int32_t gNumCharRecv = 0;

    //
    // Loop forever echoing data through the UART.
    //
    while(running)
    { 
      // If statement series for different toggles set by process_menu()
      if (LEDToggled) 
      {
        for (ui32Loop = 0; ui32Loop < LEDDelay; ui32Loop++) {}
        GPIOPinWrite (GPIO_PORTG_BASE, GPIO_PIN_2, GPIO_PIN_2);
        for (ui32Loop = 0; ui32Loop < LEDDelay; ui32Loop++) {}
        GPIOPinWrite (GPIO_PORTG_BASE, GPIO_PIN_2, 0);
      }
      
      //
      // ADC Displays
      //
      // ADC-1
      if (ADCToggled1) 
      { 
        char buffer [15];
        ADCProcessorTrigger (ADC0_BASE, 0);
        ADCSequenceDataGet (ADC0_BASE, 0, &ui32ADCValue1);
        GrContextForegroundSet(&sContext, ClrWhite);
        sprintf (buffer, "  PD2: %d  ", ui32ADCValue1);
        GrStringDrawCentered(&sContext, buffer, -1,
                             GrContextDpyWidthGet(&sContext) / 2, 15, 1);
      }
      if (ADCToggled2) 
      {
        ADCProcessorTrigger (ADC0_BASE, 0);
        ADCSequenceDataGet (ADC0_BASE, 0, &ui32ADCValue1);
        sRect.i16XMin = 0;
        sRect.i16YMin = 0;
        double xMaxDouble = ((double)ui32ADCValue1 / 4095) * GrContextDpyWidthGet(&sContext);
        sRect.i16XMax = (int16_t) xMaxDouble;
        sRect.i16YMax = 20;
        GrContextForegroundSet(&sContext, ClrYellow);
        GrRectFill(&sContext, &sRect);
        for (ui32Loop = 0; ui32Loop < ADCBarUpdateDelay; ui32Loop++) {}
        sRect.i16XMin = 0;
        sRect.i16YMin = 0;
        sRect.i16XMax = GrContextDpyWidthGet(&sContext);
        sRect.i16YMax = 20;
        GrContextForegroundSet(&sContext, ClrBlack);
        GrRectFill(&sContext, &sRect);
      }
      
      // ADC-2
      if (ADCToggled3) 
      {
        char buffer [15];
        ADCProcessorTrigger (ADC0_BASE, 1);
        ADCSequenceDataGet (ADC0_BASE, 1, &ui32ADCValue2);
        GrContextForegroundSet(&sContext, ClrWhite);
        sprintf (buffer, "  PD3: %d  ", ui32ADCValue2);
        GrStringDrawCentered(&sContext, buffer, -1,
                             GrContextDpyWidthGet(&sContext) / 2, 35, 1);
      }
      if (ADCToggled4) 
      {
        ADCProcessorTrigger (ADC0_BASE, 1);
        ADCSequenceDataGet (ADC0_BASE, 1, &ui32ADCValue2);
        sRect.i16XMin = 0;
        sRect.i16YMin = 20;
        double xMaxDouble = ((double)ui32ADCValue2 / 4095) * GrContextDpyWidthGet(&sContext);
        sRect.i16XMax = (int16_t) xMaxDouble;
        sRect.i16YMax = 40;
        GrContextForegroundSet(&sContext, ClrRed);
        GrRectFill(&sContext, &sRect);
        for (ui32Loop = 0; ui32Loop < ADCBarUpdateDelay; ui32Loop++) {}
        sRect.i16XMin = 0;
        sRect.i16YMin = 20;
        sRect.i16XMax = GrContextDpyWidthGet(&sContext);
        sRect.i16YMax = 40;
        GrContextForegroundSet(&sContext, ClrBlack);
        GrRectFill(&sContext, &sRect);
      }
      
      // ADC-3
      if (ADCToggled5) 
      {
        char buffer [15];
        ADCProcessorTrigger (ADC0_BASE, 2);
        ADCSequenceDataGet (ADC0_BASE, 2, &ui32ADCValue3);
        GrContextForegroundSet(&sContext, ClrWhite);
        sprintf (buffer, "  PD4: %d  ", ui32ADCValue3);
        GrStringDrawCentered(&sContext, buffer, -1,
                             GrContextDpyWidthGet(&sContext) / 2, 55, 1);
      }
      if (ADCToggled6) 
      {
        ADCProcessorTrigger (ADC0_BASE, 2);
        ADCSequenceDataGet (ADC0_BASE, 2, &ui32ADCValue3);
        sRect.i16XMin = 0;
        sRect.i16YMin = 40;
        double xMaxDouble = ((double)ui32ADCValue3 / 4095) * GrContextDpyWidthGet(&sContext);
        sRect.i16XMax = (int16_t) xMaxDouble;
        sRect.i16YMax = 60;
        GrContextForegroundSet(&sContext, ClrBlue);
        GrRectFill(&sContext, &sRect);
        for (ui32Loop = 0; ui32Loop < ADCBarUpdateDelay; ui32Loop++) {}
        sRect.i16XMin = 0;
        sRect.i16YMin = 40;
        sRect.i16XMax = GrContextDpyWidthGet(&sContext);
        sRect.i16YMax = 60;
        GrContextForegroundSet(&sContext, ClrBlack);
        GrRectFill(&sContext, &sRect);
      }
      
      // UART Input
      int32_t local_char;
      while (UARTCharsAvail (UART0_BASE)) 
      {
        local_char = UARTCharGetNonBlocking (UART0_BASE);
        
        if (local_char != -1) 
        {
          gNumCharRecv++;
          process_menu (local_char);
        }
      }
    }
  }

void process_menu (int32_t c) 
{  
  if (c == 'S') 
  {
    sRect.i16XMin = 0;
    sRect.i16YMin = 0;
    sRect.i16XMax = GrContextDpyWidthGet(&sContext);
    sRect.i16YMax = GrContextDpyHeightGet(&sContext);
    GrContextForegroundSet(&sContext, ClrDarkBlue);
    GrRectFill(&sContext, &sRect);
    GrContextForegroundSet(&sContext, ClrWhite);
    GrContextFontSet(&sContext, g_psFontFixed6x8);
    GrStringDrawCentered(&sContext, "Lab 3: ADC", -1,
                         GrContextDpyWidthGet(&sContext) / 2, 20, 0);
    GrStringDrawCentered(&sContext, "Joseph Neubert", -1,
                         GrContextDpyWidthGet(&sContext) / 2, 30, 0);
    for (ui32Loop = 0; ui32Loop < splashScreenDelay; ui32Loop++) {}
    GrContextForegroundSet(&sContext, ClrBlack);
    GrRectFill(&sContext, &sRect);
  }
  
  if (c == 'L') 
  {
    LEDToggled = !LEDToggled;
  }
  
  if (c == 'M') 
  {
    UARTSend ((uint8_t *)"\r\nMENU\r\n", 8);
    UARTSend ((uint8_t *)"Show Slpash Screen - S\r\n", 26);
    UARTSend ((uint8_t *)"Print Menu - M\r\n", 18);
    UARTSend ((uint8_t *)"Quit Program - Q\r\n", 20);
    UARTSend ((uint8_t *)"Toggle LED - L\r\n", 18);
    UARTSend ((uint8_t *)"Clear Terminal - C\r\n", 22);
    UARTSend ((uint8_t *)"ADC Measurements - 1-2, 3-4, 5-6\r\n", 36);
    UARTSend ((uint8_t *)"Show ADC number and bar graph respectively for\r\n", 50);
    UARTSend ((uint8_t *)"ADC 1, 2, and 3 respectively\r\n", 32); 
    UARTSend ((uint8_t *)"SELECTION: ", 11);
  }
  
  if (c == 'Q') 
  {
    running = false;
  }
  
  if (c == 'C') 
  {
    UARTSend ("\x0c", 4);
  }
  
  if (c == '1') 
  {
    ADCToggled1 = !ADCToggled1;
    sRect.i16XMin = 0;
    sRect.i16YMin = 0;
    sRect.i16XMax = GrContextDpyWidthGet(&sContext);
    sRect.i16YMax = 20;
    GrContextForegroundSet(&sContext, ClrBlack);
    GrRectFill(&sContext, &sRect);
  }
  
  if (c == '2') 
  {
    // NOTE: Potentiometer range is 0 - 4095
    ADCToggled2 = !ADCToggled2;
    sRect.i16XMin = 0;
    sRect.i16YMin = 0;
    sRect.i16XMax = GrContextDpyWidthGet(&sContext);
    sRect.i16YMax = 20;
    GrContextForegroundSet(&sContext, ClrBlack);
    GrRectFill(&sContext, &sRect);
  }
  
  if (c == '3') 
  {
    ADCToggled3 = !ADCToggled3;
    sRect.i16XMin = 0;
    sRect.i16YMin = 20;
    sRect.i16XMax = GrContextDpyWidthGet(&sContext);
    sRect.i16YMax = 40;
    GrContextForegroundSet(&sContext, ClrBlack);
    GrRectFill(&sContext, &sRect);
  }
  
  if (c == '4') 
  {
    ADCToggled4 = !ADCToggled4;
    sRect.i16XMin = 0;
    sRect.i16YMin = 20;
    sRect.i16XMax = GrContextDpyWidthGet(&sContext);
    sRect.i16YMax = 40;
    GrContextForegroundSet(&sContext, ClrBlack);
    GrRectFill(&sContext, &sRect);
  }
  
  if (c == '5') 
  {
    ADCToggled5 = !ADCToggled5;
    sRect.i16XMin = 0;
    sRect.i16YMin = 40;
    sRect.i16XMax = GrContextDpyWidthGet(&sContext);
    sRect.i16YMax = 60;
    GrContextForegroundSet(&sContext, ClrBlack);
    GrRectFill(&sContext, &sRect);
  }
  
  if (c == '6') 
  {
    ADCToggled6 = !ADCToggled6;
    sRect.i16XMin = 0;
    sRect.i16YMin = 40;
    sRect.i16XMax = GrContextDpyWidthGet(&sContext);
    sRect.i16YMax = 60;
    GrContextForegroundSet(&sContext, ClrBlack);
    GrRectFill(&sContext, &sRect);
  }
}