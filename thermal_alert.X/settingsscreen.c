#include "settingsscreen.h"

#include "buttons.h"
#include "mcc.h"
#include "menuscreen.h"
#include "lcd.h"
#include "led.h"
#include "config.h"

ButtonReleaseCallback     prevUpReleaseCB;
ButtonReleaseCallback     prevDownReleaseCB;
ButtonReleaseCallback   prevSetReleaseCB;
ButtonPressCallback     prevSetLongPressCB;

uint8_t curRow = 0;

int curUpIntLimit = 0;
int curUpFractLimit = 0;
int curBottomIntLimit = 0;
int curBottomFractLimit = 0;

int oldUpIntLimit = 0;
int oldUpFractLimit = 0;
int oldBottomIntLimit = 0;
int oldBottomFractLimit = 0;

//-----------------------------------------------------------------------------
void _SettingsScreen_UpRelease(bool wasLongPress)
{
    if(!wasLongPress)
    {
        // Attól függően, hogy melyik sorban vagyunk, növeljük a limit értéket.

        // A hőmérő 85 fokig bírja 0.5 fokos pontossággal
        if(curRow == 0 && curUpIntLimit < 85)
        {
            curUpFractLimit += 5;
            if(curUpFractLimit == 10)
            {
                curUpIntLimit += 1;
                curUpFractLimit = 0;
            }
        }
        // Az alsó határt a felső alatt tartjuk
        else if( curRow == 1 &&
                (curBottomIntLimit < curUpIntLimit || curBottomFractLimit < curUpFractLimit))
        {
             curBottomFractLimit += 5;
            if(curBottomFractLimit == 10)
            {
                curBottomIntLimit += 1;
                curBottomFractLimit = 0;
            }
        }
        SettingsScreen_Display();
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void _SettingsScreen_DownRelease(bool wasLongPress)
{
    if(!wasLongPress)
    {
        // Attól függően, hogy melyik sorban vagyunk, csökkentjük a limit értéket.

        // A felső limit mindig az alsó felett maradjon
        if(curRow == 0 && (curBottomIntLimit < curUpIntLimit || curBottomFractLimit < curUpFractLimit))
        {
            if(curUpFractLimit == 0)
            {
                curUpFractLimit = 5;
                curUpIntLimit -= 1;
            }
            else
            {
                curUpFractLimit = 0;
            }
        }
        // A hőmérő -10 fokig bírja 0.5 fokos pontossággal
        else if( curRow == 1 && curBottomIntLimit > -10)
        {
            if(curBottomFractLimit == 0)
            {
                curBottomFractLimit = 5;
                curBottomIntLimit -= 1;
            }
            else
            {
                curBottomFractLimit = 0;
            }
        }
        SettingsScreen_Display();
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void _SettingsScreen_SetRelease(bool isFromLongPress)
{
    if(!isFromLongPress)
    {
        curRow = (curRow == 0 ? 1 : 0);
        SettingsScreen_Display();
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void _SettingsScreen_SetLongPress()
{
    FlashLed100ms();
    LeaveSettingsScreen();
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void SettingsScreen_Init()
{
    MenuScreen_Clear();
    
    prevUpReleaseCB     = ButtonUp_ReleaseCB;
    prevDownReleaseCB   = ButtonDown_ReleaseCB;
    prevSetReleaseCB    = ButtonSet_ReleaseCB;
    prevSetLongPressCB  = ButtonSet_LongPressCB;
    
    ButtonUp_ReleaseCB    = _SettingsScreen_UpRelease;
    ButtonDown_ReleaseCB  = _SettingsScreen_DownRelease;
    ButtonSet_ReleaseCB   = _SettingsScreen_SetRelease;
    ButtonSet_LongPressCB = _SettingsScreen_SetLongPress;
    
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void SettingsScreen_Display()
{
    MenuScreen_Clear();
    LCDWriteStringXY(MENU_START_X, curRow, "*");
    LCDWriteStringXY(MENU_START_X + 1, 0, "U ");
    LCDWriteStringXY(MENU_START_X + 1, 1, "B ");
    
    int upInt = curUpIntLimit;
    int bottomInt = curBottomIntLimit;
    
    // Az előjelet ki kell rakni kézzel, az LCD lib sajnos előjel esetén jobbra tolja a digiteket,
    // ami pedig már nem férne ki a kijelzőre.
    if(curUpIntLimit < 0)
    {
        upInt = -upInt;
        LCDWriteStringXY(MENU_START_X + 3, 0, "-");
    }
    if(curBottomIntLimit < 0)
    {
        bottomInt = -bottomInt;
        LCDWriteStringXY(MENU_START_X + 3, 1, "-");
    }
    
    LCDWriteIntXY(MENU_START_X + 4, 0, upInt, 2);
    LCDWriteIntXY(MENU_START_X + 4, 1, bottomInt, 2);
    
    LCDWriteStringXY(MENU_START_X + 6, 0, ".");
    LCDWriteStringXY(MENU_START_X + 6, 1, ".");
    
    LCDWriteIntXY(MENU_START_X + 7, 0, curUpFractLimit, 1);
    LCDWriteIntXY(MENU_START_X + 7, 1, curBottomFractLimit, 1);
    LCDWriteStringXY(MENU_START_X + 8, 0, "C");
    LCDWriteStringXY(MENU_START_X + 8, 1, "C");
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void LeaveSettingsScreen()
{
    if( oldUpIntLimit != curUpIntLimit ||
        oldUpFractLimit != curUpFractLimit)
    {
        Config_SetUpLimit(curUpIntLimit, curUpFractLimit);
    }
    
    if( oldBottomIntLimit != curBottomIntLimit ||
        oldBottomFractLimit != curBottomFractLimit)
    {
        Config_SetBottomLimit(curBottomIntLimit, curBottomFractLimit);
    }
    
    ButtonUp_ReleaseCB = prevUpReleaseCB;
    ButtonDown_ReleaseCB = prevDownReleaseCB;
    ButtonSet_ReleaseCB = prevSetReleaseCB;
    ButtonSet_LongPressCB = prevSetLongPressCB;
    
//    MenuScreen_Display();
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void ChangeToSettingsScreen(void* param)
{
    SettingsScreen_Init();
    
    Config_GetUpLimit(&curUpIntLimit, &curUpFractLimit);
    oldUpIntLimit = curUpIntLimit;
    oldUpFractLimit = curUpFractLimit;

    Config_GetBottomLimit(&curBottomIntLimit, &curBottomFractLimit);
    oldBottomIntLimit = curBottomIntLimit;
    oldBottomFractLimit = curBottomFractLimit;
    
    SettingsScreen_Display();
}
//-----------------------------------------------------------------------------