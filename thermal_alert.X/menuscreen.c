#include "menuscreen.h"

#include <string.h>

#include "buttons.h"
#include "led.h"
#include "lcd.h"
#include "macros.h"
#include "mcc.h"
#include "settingsscreen.h"

#define MENU_MAX_ITEMS  10

int8_t _Menu_SelectedItem = 0;
int8_t _Menu_MaxValidIndex = 0;

#define MENU_ADDRESS_CYCLIC(i) ( ( (i) + _Menu_MaxValidIndex + 1) % (_Menu_MaxValidIndex + 1))

typedef enum
{
    DIR_UP,
    DIR_DOWN
} MenuMoveDir;

MenuMoveDir menuDir = DIR_UP;

typedef struct
{
    /**
     * Érvényes-e ez az elem. Ha MENU_MAX_ITEMS számú elemnél kevesebbet szeretnénk
     * megjeleníteni, akkor egy olyat kell betenni lezárónak, ahol ez a tag false értékű.
     */
    bool        IsValid;
    
    /** A kijelzőn megjelenítendő szöveg */
    const char  String[MENU_LINE_WIDTH];
    
    /** A menüpont kiválasztásakor lefuttatandó függvény. */
    void        (*Callback)(void*);
} MenuItem;

MenuItem MainMenu[MENU_MAX_ITEMS] = {
    { true, "Settings", ChangeToSettingsScreen},
    { true, "Light", LCD_ToggleBacklight},
    { false, "", NULL}
};

//-----------------------------------------------------------------------------
void _MenuScreen_MoveUp(bool wasLongPress)
{
    if(!wasLongPress)
    {
        menuDir = DIR_UP;
        uint8_t oldSelected = _Menu_SelectedItem;
        if(_Menu_SelectedItem == 0)
        {
            _Menu_SelectedItem = _Menu_MaxValidIndex;
        }
        else
        {
            _Menu_SelectedItem = (_Menu_SelectedItem - 1);
        }
        if( !MainMenu[_Menu_SelectedItem].IsValid)
        {
            _Menu_SelectedItem = oldSelected;
        }
        MenuScreen_Display();
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void _MenuScreen_MoveDown(bool wasLongPress)
{
    if(!wasLongPress)
    {
        menuDir = DIR_DOWN;
        uint8_t oldSelected = _Menu_SelectedItem;
        if(_Menu_SelectedItem == _Menu_MaxValidIndex)
        {
            _Menu_SelectedItem = 0;
        }
        else
        {
            _Menu_SelectedItem = (_Menu_SelectedItem + 1);
        }
        if( !MainMenu[_Menu_SelectedItem].IsValid)
        {
            _Menu_SelectedItem = oldSelected;
        }
        MenuScreen_Display();
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void _MenuScreen_SetRelease(bool isFromLongPress)
{
    if(!isFromLongPress)
    {
        CALLBACK_PARAM(MainMenu[_Menu_SelectedItem].Callback, NULL);
    }
    else
    {
        // Ha long press volt, akkor valami más helyről jöttünk valószínűleg vissza
        MenuScreen_Display();
    }
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void MenuScreen_Clear()
{
    static char allSpace[MENU_LINE_WIDTH] = {0};
    if(allSpace[0] == 0)
    {
        size_t i;
        for(i = 0;i<MENU_LINE_WIDTH;++i)
        {
            allSpace[i] = ' ';
        }
    }
    LCDWriteStringXY(MENU_START_X, 0, allSpace);
    LCDWriteStringXY(MENU_START_X, 1, allSpace);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void MenuScreen_Init()
{
    _Menu_SelectedItem = 0;
    uint8_t i;
    _Menu_MaxValidIndex = MENU_MAX_ITEMS - 1;
    for(i = 0;i<MENU_MAX_ITEMS;++i)
    {
        if( !MainMenu[i].IsValid && i > 0)
        {
            _Menu_MaxValidIndex = i - 1;
            break;
        }
    }
    
    ButtonUp_ReleaseCB = _MenuScreen_MoveUp;
    ButtonDown_ReleaseCB = _MenuScreen_MoveDown;
    ButtonSet_ReleaseCB = _MenuScreen_SetRelease;
    
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void MenuScreen_Display()
{   
    MenuScreen_Clear();
    
//    LCDWriteIntXY(0, 1, _Menu_SelectedItem, 2);
//    LCDWriteIntXY(3, 1, MENU_ADDRESS_CYCLIC(_Menu_SelectedItem - 1), 2);
    
    if(menuDir == DIR_UP)
    {
        LCDWriteStringXY(MENU_START_X, 0, "*");
        LCDWriteStringXY(MENU_START_X, 1, " ");
        LCDWriteStringXY(MENU_START_X + 1, 0, MainMenu[MENU_ADDRESS_CYCLIC(_Menu_SelectedItem)].String);
        LCDWriteStringXY(MENU_START_X + 1, 1, MainMenu[MENU_ADDRESS_CYCLIC(_Menu_SelectedItem + 1)].String);
    }
    else if(menuDir == DIR_DOWN)
    {
        LCDWriteStringXY(MENU_START_X, 0, " ");
        LCDWriteStringXY(MENU_START_X, 1, "*");
        LCDWriteStringXY(MENU_START_X + 1, 0, MainMenu[MENU_ADDRESS_CYCLIC(_Menu_SelectedItem - 1)].String);
        LCDWriteStringXY(MENU_START_X + 1, 1, MainMenu[MENU_ADDRESS_CYCLIC(_Menu_SelectedItem)].String);
    }
}
//-----------------------------------------------------------------------------

