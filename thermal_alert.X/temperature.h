#ifndef TEMPERATURE_H
#define	TEMPERATURE_H

#include "mcc.h"

extern int16_t CurrentTemperatureRaw;

// A mért környezeti hőmérséklet egész része.
extern int16_t CurTempInt;

// A mért környezeti hőmérséklet tört része.
extern uint8_t CurTempFract;

/**
 * Inicializálja a hőmérőt, beállítja rajta a 9 bites felbontást (0.5°C pontosság)
 */
void TempSensor_Init();

/**
 * Periodikusan meghívandó függvény, amely a hőmérséklet beolvasását, valamint az adatok szűrését végzi.
 */
void updateTemperature();

#endif	/* TEMPERATURE_H */

