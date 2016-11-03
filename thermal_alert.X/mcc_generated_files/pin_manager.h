/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB® Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB® Code Configurator - v2.25.2
        Device            :  PIC16F1718
        Version           :  1.01
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LCD_DB4 aliases
#define LCD_DB4_TRIS               TRISA0
#define LCD_DB4_LAT                LATA0
#define LCD_DB4_PORT               RA0
#define LCD_DB4_WPU                WPUA0
#define LCD_DB4_ANS                ANSA0
#define LCD_DB4_SetHigh()    do { LATA0 = 1; } while(0)
#define LCD_DB4_SetLow()   do { LATA0 = 0; } while(0)
#define LCD_DB4_Toggle()   do { LATA0 = ~LATA0; } while(0)
#define LCD_DB4_GetValue()         RA0
#define LCD_DB4_SetDigitalInput()    do { TRISA0 = 1; } while(0)
#define LCD_DB4_SetDigitalOutput()   do { TRISA0 = 0; } while(0)

#define LCD_DB4_SetPullup()    do { WPUA0 = 1; } while(0)
#define LCD_DB4_ResetPullup()   do { WPUA0 = 0; } while(0)
#define LCD_DB4_SetAnalogMode()   do { ANSA0 = 1; } while(0)
#define LCD_DB4_SetDigitalMode()   do { ANSA0 = 0; } while(0)
// get/set LCD_DB5 aliases
#define LCD_DB5_TRIS               TRISA1
#define LCD_DB5_LAT                LATA1
#define LCD_DB5_PORT               RA1
#define LCD_DB5_WPU                WPUA1
#define LCD_DB5_ANS                ANSA1
#define LCD_DB5_SetHigh()    do { LATA1 = 1; } while(0)
#define LCD_DB5_SetLow()   do { LATA1 = 0; } while(0)
#define LCD_DB5_Toggle()   do { LATA1 = ~LATA1; } while(0)
#define LCD_DB5_GetValue()         RA1
#define LCD_DB5_SetDigitalInput()    do { TRISA1 = 1; } while(0)
#define LCD_DB5_SetDigitalOutput()   do { TRISA1 = 0; } while(0)

#define LCD_DB5_SetPullup()    do { WPUA1 = 1; } while(0)
#define LCD_DB5_ResetPullup()   do { WPUA1 = 0; } while(0)
#define LCD_DB5_SetAnalogMode()   do { ANSA1 = 1; } while(0)
#define LCD_DB5_SetDigitalMode()   do { ANSA1 = 0; } while(0)
// get/set LCD_DB6 aliases
#define LCD_DB6_TRIS               TRISA2
#define LCD_DB6_LAT                LATA2
#define LCD_DB6_PORT               RA2
#define LCD_DB6_WPU                WPUA2
#define LCD_DB6_ANS                ANSA2
#define LCD_DB6_SetHigh()    do { LATA2 = 1; } while(0)
#define LCD_DB6_SetLow()   do { LATA2 = 0; } while(0)
#define LCD_DB6_Toggle()   do { LATA2 = ~LATA2; } while(0)
#define LCD_DB6_GetValue()         RA2
#define LCD_DB6_SetDigitalInput()    do { TRISA2 = 1; } while(0)
#define LCD_DB6_SetDigitalOutput()   do { TRISA2 = 0; } while(0)

#define LCD_DB6_SetPullup()    do { WPUA2 = 1; } while(0)
#define LCD_DB6_ResetPullup()   do { WPUA2 = 0; } while(0)
#define LCD_DB6_SetAnalogMode()   do { ANSA2 = 1; } while(0)
#define LCD_DB6_SetDigitalMode()   do { ANSA2 = 0; } while(0)
// get/set LCD_DB7 aliases
#define LCD_DB7_TRIS               TRISA3
#define LCD_DB7_LAT                LATA3
#define LCD_DB7_PORT               RA3
#define LCD_DB7_WPU                WPUA3
#define LCD_DB7_ANS                ANSA3
#define LCD_DB7_SetHigh()    do { LATA3 = 1; } while(0)
#define LCD_DB7_SetLow()   do { LATA3 = 0; } while(0)
#define LCD_DB7_Toggle()   do { LATA3 = ~LATA3; } while(0)
#define LCD_DB7_GetValue()         RA3
#define LCD_DB7_SetDigitalInput()    do { TRISA3 = 1; } while(0)
#define LCD_DB7_SetDigitalOutput()   do { TRISA3 = 0; } while(0)

#define LCD_DB7_SetPullup()    do { WPUA3 = 1; } while(0)
#define LCD_DB7_ResetPullup()   do { WPUA3 = 0; } while(0)
#define LCD_DB7_SetAnalogMode()   do { ANSA3 = 1; } while(0)
#define LCD_DB7_SetDigitalMode()   do { ANSA3 = 0; } while(0)
// get/set LCDE aliases
#define LCDE_TRIS               TRISA4
#define LCDE_LAT                LATA4
#define LCDE_PORT               RA4
#define LCDE_WPU                WPUA4
#define LCDE_ANS                ANSA4
#define LCDE_SetHigh()    do { LATA4 = 1; } while(0)
#define LCDE_SetLow()   do { LATA4 = 0; } while(0)
#define LCDE_Toggle()   do { LATA4 = ~LATA4; } while(0)
#define LCDE_GetValue()         RA4
#define LCDE_SetDigitalInput()    do { TRISA4 = 1; } while(0)
#define LCDE_SetDigitalOutput()   do { TRISA4 = 0; } while(0)

#define LCDE_SetPullup()    do { WPUA4 = 1; } while(0)
#define LCDE_ResetPullup()   do { WPUA4 = 0; } while(0)
#define LCDE_SetAnalogMode()   do { ANSA4 = 1; } while(0)
#define LCDE_SetDigitalMode()   do { ANSA4 = 0; } while(0)
// get/set OW aliases
#define OW_TRIS               TRISA5
#define OW_LAT                LATA5
#define OW_PORT               RA5
#define OW_WPU                WPUA5
#define OW_ANS                ANSA5
#define OW_SetHigh()    do { LATA5 = 1; } while(0)
#define OW_SetLow()   do { LATA5 = 0; } while(0)
#define OW_Toggle()   do { LATA5 = ~LATA5; } while(0)
#define OW_GetValue()         RA5
#define OW_SetDigitalInput()    do { TRISA5 = 1; } while(0)
#define OW_SetDigitalOutput()   do { TRISA5 = 0; } while(0)

#define OW_SetPullup()    do { WPUA5 = 1; } while(0)
#define OW_ResetPullup()   do { WPUA5 = 0; } while(0)
#define OW_SetAnalogMode()   do { ANSA5 = 1; } while(0)
#define OW_SetDigitalMode()   do { ANSA5 = 0; } while(0)
// get/set BTNUp aliases
#define BTNUp_TRIS               TRISB0
#define BTNUp_LAT                LATB0
#define BTNUp_PORT               RB0
#define BTNUp_WPU                WPUB0
#define BTNUp_ANS                ANSB0
#define BTNUp_SetHigh()    do { LATB0 = 1; } while(0)
#define BTNUp_SetLow()   do { LATB0 = 0; } while(0)
#define BTNUp_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define BTNUp_GetValue()         RB0
#define BTNUp_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define BTNUp_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define BTNUp_SetPullup()    do { WPUB0 = 1; } while(0)
#define BTNUp_ResetPullup()   do { WPUB0 = 0; } while(0)
#define BTNUp_SetAnalogMode()   do { ANSB0 = 1; } while(0)
#define BTNUp_SetDigitalMode()   do { ANSB0 = 0; } while(0)
// get/set PWM3OUT aliases
#define PWM3OUT_TRIS               TRISB1
#define PWM3OUT_LAT                LATB1
#define PWM3OUT_PORT               RB1
#define PWM3OUT_WPU                WPUB1
#define PWM3OUT_ANS                ANSB1
#define PWM3OUT_SetHigh()    do { LATB1 = 1; } while(0)
#define PWM3OUT_SetLow()   do { LATB1 = 0; } while(0)
#define PWM3OUT_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define PWM3OUT_GetValue()         RB1
#define PWM3OUT_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define PWM3OUT_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define PWM3OUT_SetPullup()    do { WPUB1 = 1; } while(0)
#define PWM3OUT_ResetPullup()   do { WPUB1 = 0; } while(0)
#define PWM3OUT_SetAnalogMode()   do { ANSB1 = 1; } while(0)
#define PWM3OUT_SetDigitalMode()   do { ANSB1 = 0; } while(0)
// get/set LCDRW aliases
#define LCDRW_TRIS               TRISB2
#define LCDRW_LAT                LATB2
#define LCDRW_PORT               RB2
#define LCDRW_WPU                WPUB2
#define LCDRW_ANS                ANSB2
#define LCDRW_SetHigh()    do { LATB2 = 1; } while(0)
#define LCDRW_SetLow()   do { LATB2 = 0; } while(0)
#define LCDRW_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define LCDRW_GetValue()         RB2
#define LCDRW_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define LCDRW_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define LCDRW_SetPullup()    do { WPUB2 = 1; } while(0)
#define LCDRW_ResetPullup()   do { WPUB2 = 0; } while(0)
#define LCDRW_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define LCDRW_SetDigitalMode()   do { ANSB2 = 0; } while(0)
// get/set LCDRS aliases
#define LCDRS_TRIS               TRISB3
#define LCDRS_LAT                LATB3
#define LCDRS_PORT               RB3
#define LCDRS_WPU                WPUB3
#define LCDRS_ANS                ANSB3
#define LCDRS_SetHigh()    do { LATB3 = 1; } while(0)
#define LCDRS_SetLow()   do { LATB3 = 0; } while(0)
#define LCDRS_Toggle()   do { LATB3 = ~LATB3; } while(0)
#define LCDRS_GetValue()         RB3
#define LCDRS_SetDigitalInput()    do { TRISB3 = 1; } while(0)
#define LCDRS_SetDigitalOutput()   do { TRISB3 = 0; } while(0)

#define LCDRS_SetPullup()    do { WPUB3 = 1; } while(0)
#define LCDRS_ResetPullup()   do { WPUB3 = 0; } while(0)
#define LCDRS_SetAnalogMode()   do { ANSB3 = 1; } while(0)
#define LCDRS_SetDigitalMode()   do { ANSB3 = 0; } while(0)
// get/set LED1 aliases
#define LED1_TRIS               TRISB4
#define LED1_LAT                LATB4
#define LED1_PORT               RB4
#define LED1_WPU                WPUB4
#define LED1_ANS                ANSB4
#define LED1_SetHigh()    do { LATB4 = 1; } while(0)
#define LED1_SetLow()   do { LATB4 = 0; } while(0)
#define LED1_Toggle()   do { LATB4 = ~LATB4; } while(0)
#define LED1_GetValue()         RB4
#define LED1_SetDigitalInput()    do { TRISB4 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISB4 = 0; } while(0)

#define LED1_SetPullup()    do { WPUB4 = 1; } while(0)
#define LED1_ResetPullup()   do { WPUB4 = 0; } while(0)
#define LED1_SetAnalogMode()   do { ANSB4 = 1; } while(0)
#define LED1_SetDigitalMode()   do { ANSB4 = 0; } while(0)
// get/set BTNDown aliases
#define BTNDown_TRIS               TRISB5
#define BTNDown_LAT                LATB5
#define BTNDown_PORT               RB5
#define BTNDown_WPU                WPUB5
#define BTNDown_ANS                ANSB5
#define BTNDown_SetHigh()    do { LATB5 = 1; } while(0)
#define BTNDown_SetLow()   do { LATB5 = 0; } while(0)
#define BTNDown_Toggle()   do { LATB5 = ~LATB5; } while(0)
#define BTNDown_GetValue()         RB5
#define BTNDown_SetDigitalInput()    do { TRISB5 = 1; } while(0)
#define BTNDown_SetDigitalOutput()   do { TRISB5 = 0; } while(0)

#define BTNDown_SetPullup()    do { WPUB5 = 1; } while(0)
#define BTNDown_ResetPullup()   do { WPUB5 = 0; } while(0)
#define BTNDown_SetAnalogMode()   do { ANSB5 = 1; } while(0)
#define BTNDown_SetDigitalMode()   do { ANSB5 = 0; } while(0)
// get/set SDO aliases
#define SDO_TRIS               TRISC0
#define SDO_LAT                LATC0
#define SDO_PORT               RC0
#define SDO_WPU                WPUC0
#define SDO_SetHigh()    do { LATC0 = 1; } while(0)
#define SDO_SetLow()   do { LATC0 = 0; } while(0)
#define SDO_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define SDO_GetValue()         RC0
#define SDO_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define SDO_SetDigitalOutput()   do { TRISC0 = 0; } while(0)

#define SDO_SetPullup()    do { WPUC0 = 1; } while(0)
#define SDO_ResetPullup()   do { WPUC0 = 0; } while(0)
// get/set CS aliases
#define CS_TRIS               TRISC1
#define CS_LAT                LATC1
#define CS_PORT               RC1
#define CS_WPU                WPUC1
#define CS_SetHigh()    do { LATC1 = 1; } while(0)
#define CS_SetLow()   do { LATC1 = 0; } while(0)
#define CS_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define CS_GetValue()         RC1
#define CS_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define CS_SetDigitalOutput()   do { TRISC1 = 0; } while(0)

#define CS_SetPullup()    do { WPUC1 = 1; } while(0)
#define CS_ResetPullup()   do { WPUC1 = 0; } while(0)
// get/set BTNs aliases
#define BTNs_TRIS               TRISC2
#define BTNs_LAT                LATC2
#define BTNs_PORT               RC2
#define BTNs_WPU                WPUC2
#define BTNs_ANS                ANSC2
#define BTNs_SetHigh()    do { LATC2 = 1; } while(0)
#define BTNs_SetLow()   do { LATC2 = 0; } while(0)
#define BTNs_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define BTNs_GetValue()         RC2
#define BTNs_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define BTNs_SetDigitalOutput()   do { TRISC2 = 0; } while(0)

#define BTNs_SetPullup()    do { WPUC2 = 1; } while(0)
#define BTNs_ResetPullup()   do { WPUC2 = 0; } while(0)
#define BTNs_SetAnalogMode()   do { ANSC2 = 1; } while(0)
#define BTNs_SetDigitalMode()   do { ANSC2 = 0; } while(0)
// get/set SCK aliases
#define SCK_TRIS               TRISC3
#define SCK_LAT                LATC3
#define SCK_PORT               RC3
#define SCK_WPU                WPUC3
#define SCK_ANS                ANSC3
#define SCK_SetHigh()    do { LATC3 = 1; } while(0)
#define SCK_SetLow()   do { LATC3 = 0; } while(0)
#define SCK_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define SCK_GetValue()         RC3
#define SCK_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define SCK_SetDigitalOutput()   do { TRISC3 = 0; } while(0)

#define SCK_SetPullup()    do { WPUC3 = 1; } while(0)
#define SCK_ResetPullup()   do { WPUC3 = 0; } while(0)
#define SCK_SetAnalogMode()   do { ANSC3 = 1; } while(0)
#define SCK_SetDigitalMode()   do { ANSC3 = 0; } while(0)
// get/set SDI aliases
#define SDI_TRIS               TRISC4
#define SDI_LAT                LATC4
#define SDI_PORT               RC4
#define SDI_WPU                WPUC4
#define SDI_ANS                ANSC4
#define SDI_SetHigh()    do { LATC4 = 1; } while(0)
#define SDI_SetLow()   do { LATC4 = 0; } while(0)
#define SDI_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define SDI_GetValue()         RC4
#define SDI_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define SDI_SetDigitalOutput()   do { TRISC4 = 0; } while(0)

#define SDI_SetPullup()    do { WPUC4 = 1; } while(0)
#define SDI_ResetPullup()   do { WPUC4 = 0; } while(0)
#define SDI_SetAnalogMode()   do { ANSC4 = 1; } while(0)
#define SDI_SetDigitalMode()   do { ANSC4 = 0; } while(0)
// get/set BUZ aliases
#define BUZ_TRIS               TRISC5
#define BUZ_LAT                LATC5
#define BUZ_PORT               RC5
#define BUZ_WPU                WPUC5
#define BUZ_ANS                ANSC5
#define BUZ_SetHigh()  do { LATC5 = 1; } while(0)
#define BUZ_SetLow()   do { LATC5 = 0; } while(0)
#define BUZ_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define BUZ_GetValue()         RC5
#define BUZ_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define BUZ_SetDigitalOutput()   do { TRISC5 = 0; } while(0)

#define BUZ_SetPullup()    do { WPUC5 = 1; } while(0)
#define BUZ_ResetPullup()   do { WPUC5 = 0; } while(0)
#define BUZ_SetAnalogMode()   do { ANSC5 = 1; } while(0)
#define BUZ_SetDigitalMode()   do { ANSC5 = 0; } while(0)
// get/set TX aliases
#define TX_TRIS               TRISC6
#define TX_LAT                LATC6
#define TX_PORT               RC6
#define TX_WPU                WPUC6
#define TX_ANS                ANSC6
#define TX_SetHigh()    do { LATC6 = 1; } while(0)
#define TX_SetLow()   do { LATC6 = 0; } while(0)
#define TX_Toggle()   do { LATC6 = ~LATC6; } while(0)
#define TX_GetValue()         RC6
#define TX_SetDigitalInput()    do { TRISC6 = 1; } while(0)
#define TX_SetDigitalOutput()   do { TRISC6 = 0; } while(0)

#define TX_SetPullup()    do { WPUC6 = 1; } while(0)
#define TX_ResetPullup()   do { WPUC6 = 0; } while(0)
#define TX_SetAnalogMode()   do { ANSC6 = 1; } while(0)
#define TX_SetDigitalMode()   do { ANSC6 = 0; } while(0)
// get/set RX aliases
#define RX_TRIS               TRISC7
#define RX_LAT                LATC7
#define RX_PORT               RC7
#define RX_WPU                WPUC7
#define RX_ANS                ANSC7
#define RX_SetHigh()    do { LATC7 = 1; } while(0)
#define RX_SetLow()   do { LATC7 = 0; } while(0)
#define RX_Toggle()   do { LATC7 = ~LATC7; } while(0)
#define RX_GetValue()         RC7
#define RX_SetDigitalInput()    do { TRISC7 = 1; } while(0)
#define RX_SetDigitalOutput()   do { TRISC7 = 0; } while(0)

#define RX_SetPullup()    do { WPUC7 = 1; } while(0)
#define RX_ResetPullup()   do { WPUC7 = 0; } while(0)
#define RX_SetAnalogMode()   do { ANSC7 = 1; } while(0)
#define RX_SetDigitalMode()   do { ANSC7 = 0; } while(0)

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize(void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
 */