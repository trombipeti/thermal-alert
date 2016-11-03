/**
  TMR4 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    tmr4.c

  @Summary
    This is the generated driver implementation file for the TMR4 driver using MPLAB® Code Configurator

  @Description
    This source file provides APIs for TMR4.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC16F1718
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 v1.34
        MPLAB             :  MPLAB X v2.35 or v3.00
 */

/*
Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 */

/**
  Section: Included Files
 */

#include <xc.h>
#include <stdint.h>
#include "tmr4.h"

/**
  Section: TMR4 APIs
 */

volatile uint16_t TMR4_MsCntr = 0;
volatile uint32_t TMR4_SecCntr = 0;

void TMR4_Initialize(void)
{
    // Set TMR4 to the options selected in the User Interface

    // TMR4ON off; T4CKPS 1:1; T4OUTPS 1:16; 
    T4CON = 0x78;

    // PR4 249; 
    PR4 = 0xF9;

    // TMR4 0x0; 
    TMR4 = 0x00;

    // Clearing IF flag before enabling the interrupt.
    PIR2bits.TMR4IF = 0;

    // Enabling TMR4 interrupt.
    PIE2bits.TMR4IE = 1;

    // Start TMR4
    TMR4_StartTimer();
}

void TMR4_StartTimer(void)
{
    // Start the Timer by writing to TMRxON bit
    T4CONbits.TMR4ON = 1;
}

void TMR4_StopTimer(void)
{
    // Stop the Timer by writing to TMRxON bit
    T4CONbits.TMR4ON = 0;
}

uint8_t TMR4_ReadTimer(void)
{
    uint8_t readVal;

    readVal = TMR4;

    return readVal;
}

void TMR4_WriteTimer(uint8_t timerVal)
{
    // Write to the Timer4 register
    TMR4 = timerVal;
}

void TMR4_LoadPeriodRegister(uint8_t periodVal)
{
    PR4 = periodVal;
}

uint16_t TMR4_GetMs()
{
    return TMR4_MsCntr;
}

uint32_t TMR4_GetSec()
{
    return TMR4_SecCntr;
}

void TMR4_ISR(void)
{
    // clear the TMR4 interrupt flag
    PIR2bits.TMR4IF = 0;

    // add your TMR4 interrupt custom code
    TMR4_MsCntr++;
    if(TMR4_MsCntr >= 1000)
    {
        TMR4_SecCntr++;
        TMR4_MsCntr = 0;
    }
    
}

/**
  End of File
 */