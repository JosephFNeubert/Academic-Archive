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

volatile uint32_t ui32Loop;

// Global integers for interrupt timer counts
// Timer0 called once per second and displays number of times Timer1 ISRs are called
// Timer1 is variable frequency
uint32_t req; // Timer1 interrupts requested per second
uint32_t srv; // Timer1 interrupts serviced per second
uint32_t newTimerLoad; // New timer load value
// uint32_t timer1ExecutionCount; // Counter for all times timer1 executes its ISR; reset to zero by timer0 ISR
// char timerS[8];

// Buffers for OLED Values
char buffer1[8];
char buffer2[8];
char buffer3[4];

// Global Toggles
bool showADC = false;
bool runningCount = false;

// ADC Reading Global Variable
uint32_t ui32ADCValue;

// Process Menu Function Prototype
void process_menu(char c);

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
// The interrupt handler for the first timer interrupt.
//
//*****************************************************************************
void
Timer0IntHandler(void)
{
    //
    // Clear the timer interrupt.
    //
    ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    ROM_IntMasterDisable();
    
    // ISR-0
    ADCProcessorTrigger(ADC0_BASE, 0);
    ADCSequenceDataGet(ADC0_BASE, 0, &ui32ADCValue);
    
    if (runningCount) 
    {
      req = ui32ADCValue / 10 + 1;
    }
    else 
    {
      req = ui32ADCValue * 100 + 1;
    }
    newTimerLoad = SysCtlClockGet() / req;
    if (TimerLoadGet(TIMER1_BASE, TIMER_A) != newTimerLoad) 
    {
      TimerIntDisable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
      TimerLoadSet(TIMER1_BASE, TIMER_A, newTimerLoad);
      TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    }
    
    GrContextForegroundSet(&g_sContext, ClrWhite);
    sprintf(buffer1, "%d      ", req);
    sprintf(buffer2, "%d      ", srv);
    sprintf(buffer3, "%d      ", ui32ADCValue);
    GrStringDraw(&g_sContext, buffer1, -1, GrContextDpyWidthGet(&g_sContext) / 2, 15, 1);
    GrStringDraw(&g_sContext, buffer2, -1, GrContextDpyWidthGet(&g_sContext) / 2, 35, 1);
    if (showADC) 
    {
      GrStringDraw(&g_sContext, buffer3, -1, GrContextDpyWidthGet(&g_sContext) / 2, 55, 1);
    }
    srv = 0;
    
    ROM_IntMasterEnable();
}

//*****************************************************************************
//
// The interrupt handler for the second timer interrupt.
//
//*****************************************************************************
void
Timer1IntHandler(void)
{
    // Depending on startup_ewarm.c, will either run Assembly code or the code below
    //
    // Clear the timer interrupt.
    //
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    
    
    // ISR-1
    srv++;
    
    //
    // NOT NEEDED FOR LAB 5
    //
    //if (runningCount) 
    //{
      //ROM_IntMasterDisable();
      //timer1ExecutionCount = srv;
      //sprintf(timerS, "%d   ", timer1ExecutionCount);
      //GrStringDraw(&g_sContext, timerS, -1, GrContextDpyWidthGet(&g_sContext) / 2, 55, 1);
      //ROM_IntMasterEnable();
    //}
    
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
    //SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    
    // 80 MHz
    SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);
    
    //
    // Initialize the display driver.
    //
    CFAL96x64x16Init();

    //
    // Initialize the graphics context and find the middle X coordinate.
    //
    GrContextInit(&g_sContext, &g_sCFAL96x64x16);
    
    // Enable, check, and configure PG2 for LED
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOG)) {}
    GPIOPinTypeGPIOOutput (GPIO_PORTG_BASE, GPIO_PIN_2);
    
    // Enable and configure UART
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)) {}
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));
    
    // Enable and configure ADC
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD)) {}
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_2);
    ADCSequenceDisable (ADC0_BASE, 0);
    ADCSequenceConfigure (ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure (ADC0_BASE, 0, 0, ADC_CTL_CH13 | ADC_CTL_END); // AIN-13 is PD2
    ADCSequenceEnable (ADC0_BASE, 0);
    
    // Display initial splash screen
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
    GrStringDrawCentered(&g_sContext, "Lab 5: ASM ISR", -1,
                         GrContextDpyWidthGet(&g_sContext) / 2, 20, 0);
    GrStringDrawCentered(&g_sContext, "Joseph Neubert", -1,
                         GrContextDpyWidthGet(&g_sContext) / 2, 30, 0);
    GrStringDrawCentered(&g_sContext, sysClockRate, -1, 
                         GrContextDpyWidthGet(&g_sContext) / 2, 40, 0);
    for (ui32Loop = 0; ui32Loop < splashScreenDelay; ui32Loop++) {}
    GrContextForegroundSet(&g_sContext, ClrBlack);
    GrRectFill(&g_sContext, &sRect);

    //
    // Change foreground for white text.
    //
    GrContextForegroundSet(&g_sContext, ClrWhite);

    //
    // Initialize timer status display.
    //
    GrContextFontSet(&g_sContext, g_psFontFixed6x8);

    //
    // Enable the peripherals used by this example.
    //
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

    //
    // Enable processor interrupts.
    //
    IntMasterEnable();

    //
    // Configure the two 32-bit periodic timers.
    //
    ROM_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    ROM_TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    ROM_TimerLoadSet(TIMER0_BASE, TIMER_A, ROM_SysCtlClockGet());
    ROM_TimerLoadSet(TIMER1_BASE, TIMER_A, ROM_SysCtlClockGet() / 2);

    //
    // Setup the interrupts for the timer timeouts.
    //
    ROM_IntEnable(INT_TIMER0A);
    ROM_IntEnable(INT_TIMER1A);
    ROM_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    ROM_TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Enable the timers.
    //
    ROM_TimerEnable(TIMER0_BASE, TIMER_A);
    ROM_TimerEnable(TIMER1_BASE, TIMER_A);
    
    // Draw Text to Persist on OLED
    GrStringDraw(&g_sContext, "REQ: ", -1, 5, 15, 1);
    GrStringDraw(&g_sContext, "SRV: ", -1, 5, 35, 1);
    GrStringDraw(&g_sContext, "ADC: ", -1, 5, 55, 1);
    
    // UART Start Menu
    UARTSend ((uint8_t *)"\r\nMENU\r\n", 8);
    UARTSend ((uint8_t *)"Show Slpash Screen - S\r\n", 26);
    UARTSend ((uint8_t *)"Print Menu - M\r\n", 18);
    UARTSend ((uint8_t *)"Enable Running Count - C\r\n", 28);
    UARTSend ((uint8_t *)"Show ADC Value - A\r\n", 22);

    //
    // Loop forever while the timers run.
    //
    while(1)
    {
      // UART Input
      int32_t local_char;
      while (UARTCharsAvail(UART0_BASE)) 
      {
        local_char = UARTCharGetNonBlocking(UART0_BASE);
        
        if (local_char != -1) 
        {
          process_menu(local_char);
        }
      }
      
      for (ui32Loop = 0; ui32Loop < LEDDelay; ui32Loop++) {}
      GPIOPinWrite (GPIO_PORTG_BASE, GPIO_PIN_2, GPIO_PIN_2);
      for (ui32Loop = 0; ui32Loop < LEDDelay; ui32Loop++) {}
      GPIOPinWrite (GPIO_PORTG_BASE, GPIO_PIN_2, 0);
    }
}

void process_menu(char c) 
{
  if (c == 'M') 
  {
    UARTSend ((uint8_t *)"\r\nMENU\r\n", 8);
    UARTSend ((uint8_t *)"Show Slpash Screen - S\r\n", 26);
    UARTSend ((uint8_t *)"Print Menu - M\r\n", 18);
    UARTSend ((uint8_t *)"Enable Running Count - C\r\n", 28);
    UARTSend ((uint8_t *)"Show ADC Value - A\r\n", 22);
  }
  
  if (c == 'S') 
  {
    IntMasterDisable();
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
    GrStringDrawCentered(&g_sContext, "Lab 5: ASM ISR", -1,
                         GrContextDpyWidthGet(&g_sContext) / 2, 20, 0);
    GrStringDrawCentered(&g_sContext, "Joseph Neubert", -1,
                         GrContextDpyWidthGet(&g_sContext) / 2, 30, 0);
    GrStringDrawCentered(&g_sContext, sysClockRate, -1, 
                         GrContextDpyWidthGet(&g_sContext) / 2, 40, 0);
    for (ui32Loop = 0; ui32Loop < splashScreenDelay; ui32Loop++) {}
    GrContextForegroundSet(&g_sContext, ClrBlack);
    GrRectFill(&g_sContext, &sRect);
    GrContextForegroundSet(&g_sContext, ClrWhite);
    GrStringDraw(&g_sContext, "REQ: ", -1, 5, 15, 1);
    GrStringDraw(&g_sContext, "SRV: ", -1, 5, 35, 1);
    GrStringDraw(&g_sContext, "ADC: ", -1, 5, 55, 1);
    IntMasterEnable();
  }
  
    if (c == 'C') 
  {
    runningCount = !runningCount;
  }
  
  if (c == 'A') 
  {
    showADC = !showADC;
  }
}