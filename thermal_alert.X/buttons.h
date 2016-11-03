#ifndef BUTTONS_H
#define	BUTTONS_H

#include "mcc.h"

#include <stdbool.h>

bool ButtonUp_IsPressed();

bool ButtonDown_IsPressed();

bool ButtonSet_IsPressed();

/**
 * Gomb lenoymásakor meghívandó függvény típus.
 */
typedef void (*ButtonPressCallback)(void);

/**
 * Gomb felengedésekor meghívandó függvény típus.
 * @param wasLongPress  Hosszú nyomvatartás előzte-e meg a felengedést.
 */
typedef void (*ButtonReleaseCallback)(bool wasLongPress);

// A "Fel" gomb eseménykezelő callback függvényei
extern ButtonPressCallback     ButtonUp_PressCB;
extern ButtonReleaseCallback   ButtonUp_ReleaseCB;
extern ButtonPressCallback     ButtonUp_LongPressCB;

// A "Le" gomb eseménykezelő callback függvényei
extern ButtonPressCallback     ButtonDown_PressCB;
extern ButtonReleaseCallback   ButtonDown_ReleaseCB;
extern ButtonPressCallback     ButtonDown_LongPressCB;

// Az "Ok" gomb eseménykezelő callback függvényei
extern ButtonPressCallback     ButtonSet_PressCB;
extern ButtonReleaseCallback   ButtonSet_ReleaseCB;
extern ButtonPressCallback     ButtonSet_LongPressCB;

/**
 * A gombok állapotát lekérdező és kezelő függvény.
 * Alapból nem nyújt pergésmentesítést, ezért érdemes két hívás közt néhány (10) ms-t várni.
 */
void handleButtons();

#endif	/* BUTTONS_H */

