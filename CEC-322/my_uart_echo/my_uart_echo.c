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
#include "driverlib/rom.h"
#include "grlib/grlib.h"
#include "drivers/cfal96x64x16.h"

#define floodDelay 1000000
#define LEDDelay 750000

bool running = true;
bool floodToggled = false;
bool LEDToggled = false;
bool loopCountToggled = false;
bool buttonPressToggled = false;

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

// Drawing variables made global
tContext sContext;
tRectangle sRect;

// My function prototypes
void process_menu (int32_t c);
void show_loop_count (int t);
void show_button_pressed (int32_t local_char, int32_t num_chars);

//*****************************************************************************
//
// This example demonstrates how to send a string of data to the UART.
//
//*****************************************************************************
int
main(void)
{
    volatile uint32_t ui32Loop;

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

    //
    // Initialize the display driver.
    //
    CFAL96x64x16Init();

    //
    // Initialize the graphics context.
    //
    GrContextInit(&sContext, &g_sCFAL96x64x16);

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
    GrStringDrawCentered(&sContext, "Neubert UART", -1,
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
    UARTSend ((uint8_t *)"Print Menu - M\r\n", 18);
    UARTSend ((uint8_t *)"Quit Program - Q\r\n", 20);
    UARTSend ((uint8_t *)"Toggle Flood - F\r\n", 20);
    UARTSend ((uint8_t *)"Toggle LED - L\r\n", 18);
    UARTSend ((uint8_t *)"Toggle Loop Count Display OLED - O\r\n", 38);
    UARTSend ((uint8_t *)"Toggle recv/xmit Display - U\r\n", 32);
    UARTSend ((uint8_t *)"Clear Terminal - C\r\n", 22);
    UARTSend ((uint8_t *)"SELECTION: ", 11);
    
    // Track number of characters in the terminal
    int32_t gNumCharRecv = 0;

    //
    // Loop forever echoing data through the UART.
    //
    int loopCount = 0;
    bool firstLoopCountToggled = false;
    while(running)
    {
      if (floodToggled) 
      {
        for (ui32Loop = 0; ui32Loop < floodDelay; ui32Loop++) {}
        UARTCharPutNonBlocking (UART0_BASE, 'A');
      }
      
      if (LEDToggled) 
      {
        for (ui32Loop = 0; ui32Loop < LEDDelay; ui32Loop++) {}
        GPIOPinWrite (GPIO_PORTG_BASE, GPIO_PIN_2, GPIO_PIN_2);
        for (ui32Loop = 0; ui32Loop < LEDDelay; ui32Loop++) {}
        GPIOPinWrite (GPIO_PORTG_BASE, GPIO_PIN_2, 0);
      }
      
      if (loopCountToggled) 
      {
        if (!firstLoopCountToggled) 
        {
          sRect.i16XMin = 0;
          sRect.i16YMin = 0;
          sRect.i16XMax = GrContextDpyWidthGet(&sContext) - 1;
          sRect.i16YMax = 9;
          GrContextForegroundSet(&sContext, ClrDarkBlue);
          GrRectFill(&sContext, &sRect);
          firstLoopCountToggled = true;
        }
        show_loop_count (loopCount);
      }
      
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
      
      if (buttonPressToggled) 
      {
        GrContextForegroundSet(&sContext, ClrDarkBlue);
        show_button_pressed (local_char, gNumCharRecv);
        buttonPressToggled = !buttonPressToggled;
      }
      loopCount++;
    }
  }

void process_menu (int32_t c) 
{
  if (c == 'F') 
  {
    floodToggled = !floodToggled;
  }
  
  if (c == 'L') 
  {
    LEDToggled = !LEDToggled;
  }
  
  if (c == 'M') 
  {
    UARTSend ((uint8_t *)"\r\nMENU\r\n", 8);
    UARTSend ((uint8_t *)"Print Menu - M\r\n", 18);
    UARTSend ((uint8_t *)"Quit Program - Q\r\n", 20);
    UARTSend ((uint8_t *)"Toggle Flood - F\r\n", 20);
    UARTSend ((uint8_t *)"Toggle LED - L\r\n", 18);
    UARTSend ((uint8_t *)"Toggle Loop Count Display OLED - O\r\n", 38);
    UARTSend ((uint8_t *)"Toggle recv/xmit Display - U\r\n", 32);
    UARTSend ((uint8_t *)"Clear Terminal - C\r\n", 22);
    UARTSend ((uint8_t *)"SELECTION: ", 11);
  }
  
  if (c == 'Q') 
  {
    running = false;
  }
  
  if (c == 'U') 
  {
    buttonPressToggled = !buttonPressToggled;
  }
  
  if (c == 'O') 
  {
    loopCountToggled = !loopCountToggled;
  }
  
  if (c == 'C') 
  {
    UARTSend ("\x0c", 4);
  }
}

void show_loop_count (int t) 
{
  char buffer[10];
  sprintf (buffer, "%d", t);
  GrContextFontSet(&sContext, g_psFontFixed6x8);
  GrStringDrawCentered (&sContext, buffer, -1, GrContextDpyWidthGet(&sContext) / 2, 4, true);
}

void show_button_pressed (int32_t local_char, int32_t num_chars) 
{
  char buffer1[1];
  char buffer2[3];
  sprintf (buffer1, "%d", local_char);
  sprintf (buffer2, "%d", num_chars);
  GrContextFontSet(&sContext, g_psFontFixed6x8);
  GrStringDrawCentered(&sContext, "Last Key Input:", -1,
                         GrContextDpyWidthGet(&sContext) / 2, 20, true);
  GrStringDrawCentered(&sContext, buffer1, -1,
                         GrContextDpyWidthGet(&sContext) / 2, 30, true);
  GrStringDrawCentered(&sContext, "Total Keys:", -1,
                         GrContextDpyWidthGet(&sContext) / 2, 40, true);
  GrStringDrawCentered(&sContext, buffer2, -1,
                         GrContextDpyWidthGet(&sContext) / 2, 50, true);
} 