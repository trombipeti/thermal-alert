/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB® Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
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

#include <pic.h>
#include <xc.h>

#include <string.h>
#include <stdlib.h>

#include "alarm.h"
#include "buttons.h"
#include "mcc.h"
#include "eusart.h"
#include "DS18B20.h"
#include "lcd.h"
#include "tests.h"
#include "25AA040A.h"
#include "menuscreen.h"
#include "commands.h"
#include "temperature.h"
#include "systime.h"
#include "config.h"
#include "alarm.h"


//-----------------------------------------------------------------------------
void initDrivers()
{

    PWM3_LoadDutyValue(0);    
    
    LCDInit(LS_NONE);
    LCDClear();
    
    TempSensor_Init();

    //    BUZ_SetHigh();
    //    __delay_ms(20);
    BUZ_SetLow();
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

// Puffer az input tárolásához.
char buf[16] = {0};

void handleUARTInput()
{
    static uint8_t i = 0;

    bool hadNL = false;
    while (eusartRxCount > 0)
    {
        char c = getch();
        putch(c);
        if (c == '\r')
        {
            putch('\n');
            hadNL = true;
            break;
        }
        else
        {
            buf[i++] = c;
        }
    }
    if (hadNL)
    {
        processCommand(buf);
        i = 0;
        memset(buf, 0, sizeof (buf));
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    //    WDTCONbits.WDTPS = 0b01001; // 512ms interval for watchdog
    WDTCONbits.WDTPS = 0b01100; // 4s interval for watchdog

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    initDrivers();
    Config_InitRTValues();
    Alarm_Init();
    
    ButtonUp_LongPressCB = LCD_ToggleBacklight;
    ButtonSet_LongPressCB = ACKAlarm;

    printf("Boot OK\r\n");
    printf("Built on: " __DATE__ " " __TIME__ "\r\n");
    
    MenuScreen_Init();
    MenuScreen_Display();
    
    SysTime prevTime = SysTime_GetNow();

    while(eusartRxCount > 0)
    {
        getch();
    }
    
    
    SysTime lastAlarmTime = SysTime_NULL;
    uint32_t alarmSec;
    
    while (1)
    {
        SysTime curTime = SysTime_GetNow();
        
        // A pergésmentesítés eléréséhez csak 10ms-enként nézzük meg a gombok állapotát
        uint32_t diffMs = SysTime_DiffMs(&prevTime, &curTime); 
        if(diffMs > 10)
        {
            prevTime = curTime;
            handleButtons();
        }

        handleUARTInput();

        updateTemperature();
        
        if(curTime.Sec > 10)
        {
            checkAlarm();
        }
        CLRWDT();
    }
}
//-----------------------------------------------------------------------------