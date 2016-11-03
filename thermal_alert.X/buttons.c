#include "buttons.h"

#include "macros.h"
#include "mcc.h"
#include "systime.h"

#define BTN_PRESSED     0
#define BTN_RELEASED    1

#define BTN_LONGPRESS_MS    1000

bool _ButtonUpPressed = false;
bool _ButtonDownPressed = false;
bool _ButtonSetPressed = false;

SysTime _ButtonUp_LastChangeTime = SysTime_NULL;
SysTime _ButtonDown_LastChangeTime = SysTime_NULL;
SysTime _ButtonSet_LastChangeTime = SysTime_NULL;

ButtonPressCallback     ButtonUp_PressCB      = NULL;
ButtonReleaseCallback   ButtonUp_ReleaseCB    = NULL;
ButtonPressCallback     ButtonUp_LongPressCB  = NULL;

ButtonPressCallback     ButtonDown_PressCB      = NULL;
ButtonReleaseCallback   ButtonDown_ReleaseCB    = NULL;
ButtonPressCallback     ButtonDown_LongPressCB  = NULL;

ButtonPressCallback     ButtonSet_PressCB      = NULL;
ButtonReleaseCallback   ButtonSet_ReleaseCB    = NULL;
ButtonPressCallback     ButtonSet_LongPressCB  = NULL;

//-----------------------------------------------------------------------------
bool ButtonDown_IsPressed()
{
    return _ButtonDownPressed;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
bool ButtonUp_IsPressed()
{
    return _ButtonUpPressed;
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
bool ButtonSet_IsPressed()
{
    return _ButtonSetPressed;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void handleButtons()
{
    static uint8_t prevUpState = BTN_RELEASED;
    static uint8_t prevDownState = BTN_RELEASED;
    static uint8_t prevSetState = BTN_RELEASED;
    
    static bool upInLongPress = false;
    static bool downInLongPress = false;
    static bool setInLongPress = false;

    static bool upLongPressFired = false;
    static bool downLongPressFired = false;
    static bool setLongPressFired = false;
    
    uint8_t downState, upState, setState;

    downState = BTNDown_GetValue();
    upState = BTNUp_GetValue();
    setState = BTNs_GetValue();
    
    SysTime now = SysTime_GetNow();

    ///////////////////////////////////////////////////////////////////////////////////
    // Felfele gomb felfutó/lefutó él detektálása
    if (upState == BTN_PRESSED && prevUpState == BTN_RELEASED)
    {
        CALLBACK(ButtonUp_PressCB);
        _ButtonUpPressed = true;
    }
    else if(upState == BTN_RELEASED && prevUpState == BTN_PRESSED)
    {
        CALLBACK_PARAM(ButtonUp_ReleaseCB, upInLongPress);
        _ButtonUpPressed = false;
    }
    // Változás esetén időzítő nullázása
    if(prevUpState != upState)
    {
        _ButtonUp_LastChangeTime = SysTime_GetNow();
        upLongPressFired = false;
    }
    // "Hosszú" ideje nyomva van-e a gomb
    upInLongPress   = (_ButtonUpPressed && 
                        SysTime_DiffMs(&_ButtonUp_LastChangeTime, &now)   >= BTN_LONGPRESS_MS);
    if(upInLongPress && !upLongPressFired)
    {
        upLongPressFired = true;
        CALLBACK(ButtonUp_LongPressCB);
    }
    prevUpState = upState;
    
    ///////////////////////////////////////////////////////////////////////////////////
    // Lefele gombra ugyanaz
    if (downState == BTN_PRESSED && prevDownState == BTN_RELEASED)
    {
        CALLBACK(ButtonDown_PressCB);
        _ButtonDownPressed = true;
    }
    else if(downState == BTN_RELEASED && prevDownState == BTN_PRESSED)
    {
        CALLBACK_PARAM(ButtonDown_ReleaseCB, downInLongPress);
        _ButtonDownPressed = false;
    }
    if(prevDownState != downState)
    {
        _ButtonDown_LastChangeTime = SysTime_GetNow();
        downLongPressFired = false;
    }
    downInLongPress = (_ButtonDownPressed && 
                        SysTime_DiffMs(&_ButtonDown_LastChangeTime, &now) >= BTN_LONGPRESS_MS);
    if(downInLongPress && !downLongPressFired)
    {
        downLongPressFired = true;
        CALLBACK(ButtonDown_LongPressCB);
    }
    prevDownState = downState;
    
    ///////////////////////////////////////////////////////////////////////////////////
    // Set gomb
    if (setState == BTN_PRESSED && prevSetState == BTN_RELEASED)
    {
        CALLBACK(ButtonSet_PressCB);
        _ButtonSetPressed = true;
    }
    else if(setState == BTN_RELEASED && prevSetState == BTN_PRESSED)
    {
        CALLBACK_PARAM(ButtonSet_ReleaseCB, setInLongPress);
        _ButtonSetPressed = false;
    }
    if(prevSetState != setState)
    {
        _ButtonSet_LastChangeTime = SysTime_GetNow();
        setLongPressFired = false;
    }
    setInLongPress  = (_ButtonSetPressed && 
                        SysTime_DiffMs(&_ButtonSet_LastChangeTime, &now)  >= BTN_LONGPRESS_MS);
    if(setInLongPress && !setLongPressFired)
    {
        setLongPressFired = true;
        CALLBACK(ButtonSet_LongPressCB);
    }
    prevSetState = setState;
}
//-----------------------------------------------------------------------------