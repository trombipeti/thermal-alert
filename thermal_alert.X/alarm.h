#ifndef ALARM_H
#define	ALARM_H

#include <stdbool.h>

#include "temperature.h"
#include "systime.h"

#define ABOVE_UPLIMIT(i, f)     ((i) > UpIntLimitRT || ((i) == UpIntLimitRT && (f) > UpFractLimitRT))
#define BELOW_BOTTOMLIMIT(i, f) ((i) < BottomIntLimitRT || ((i) == BottomIntLimitRT && (f) < BottomFractLimitRT))

void Alarm_Init();

/**
 * Riasztás fennálását adja meg.
 * 
 * @return  Riasztási állapot áll-e fent (a hőmérséklet átlépte valamelyik korlátot).
 */
bool IsAlarm();

/**
 * Megadja a legutolsó riasztási esemény idejét.
 * 
 * @param dst
 */
SysTime GetLastAlarmTime();

/**
 * Riasztási esemény beállta után ezt a függényt kell meghívni ahhoz, hogy abbamaradjon a riasztás.
 */
void ACKAlarm();

/**
 * Periodikusan futtatndó függvény ("taszk") a riasztási események figyelésére és kezelésére.
 */
void checkAlarm();

/**
 * A soros port kimenetére írja az EEPROM-ba mentett események listáját.
 */
void printAllAlarmEvents();

/**
 * Törli az összes tárolt riasztási eseményt az EEPROM-ból.
 */
void clearAllAlarmEvents();

#endif	/* ALARM_H */

