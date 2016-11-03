#ifndef DS18B20_H
#define	DS18B20_H

#include "mcc.h"
#include "1wire.h"

typedef enum
{
    DS18B20_Command_SkipRom = 0xCC,
    DS18B20_Command_Convert_T = 0x44,
    DS18B20_Command_ReadScratchpad = 0xBE,
    DS18B20_Command_WriteScratchpad = 0x4E,
    DS18B20_Command_CopyScratchpad = 0x48
} DS18B20_Command;

typedef enum 
{
    DS18B20_Resolution_9bit  = 0x0,
    DS18B20_Resolution_10bit = 0x1,
    DS18B20_Resolution_11bit = 0x2,
    DS18B20_Resolution_12bit = 0x3        
} DS18B20_Resolution;

/**
 * Inicializálja a DS18B20 szenzor 1-wire kommunikációját.
 * Először küld egy "reset" jelet, és megvárja, hogy az eszköz visszaküldje a "presence" jelet.
 * 
 * @return Sikerült-e az inicializáció (akkor sikeres, ha visszajön a "presence" jel).
 */
bool DS18B20_ResetAndDetect();

/**
 * Elindítja a hőmérséklet konverziót a szenzoron.
 * 
 * Az adat felbontásától függően a konverzió akár 750ms ideig is tarthat.
 * Ennyi időt kell várni a hőmérséklet értékek kiolvasása előtt.
 */
void DS18B20_StartConversion();

/**
 * Kiolvassa a szenzor regiszteréből a konverzió után ott található értéket.
 * 
 * A helyes működéshez meg kell hívni a DS18B20_StartConversion() függvényt, majd
 * megvárni, hogy befejeződjön a konverzió (max 750ms lehet).
 * 
 * @return A kiolvasott hőmérséklet értéke NYERSEN. Felbontástól függ a pontosság.
 */
int16_t DS18B20_ReadRawTemperature();

/**
 * Kiolvassa a hőmérő felbontás beállítását.
 * 
 * @return Hány bites felbontással üzemel a hőmérő.
 */
DS18B20_Resolution DS18B20_ReadResolution();

/**
 * Beállítja a felbontást a hőmérőn. (9-12 bit lehet).
 * 
 * @param res   A felbontás értéke, DS18B20_Resolution enum tagja.
 */
void DS18B20_SetResolution(DS18B20_Resolution res);

#endif	/* DS18B20_H */
