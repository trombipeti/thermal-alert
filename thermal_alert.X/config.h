#ifndef CONFIG_H
#define	CONFIG_H

#include "mcc.h"

/** 
 * A beállítható legmagasabb küszöbérték.
 * Ennél magasabb hőmérsékleten már nem működik jól a használt hőmérő.
 */
#define CONFIG_LIMIT_MAX     85

/**
 * A beállítható legalacsonyabb küszöbérték.
 * Ennél alacsonyabb hőméréskleten már nem működik jól a használt hőmérő.
 */
#define CONFIG_LIMIT_MIN    -10

/** A felső riasztási határ egész része.
 * Amennyiben a Config_... függvényeket használjuk az EEPROM-ba mentésre, */
extern int16_t UpIntLimitRT;
/** A felső riasztási határ tört része */
extern int16_t UpFractLimitRT;
/** Az alsó riasztási határ egész része */
extern int16_t BottomIntLimitRT;
/** Az alsó riasztási határ tört része */
extern int16_t BottomFractLimitRT;

/**
 * Kiolvassa az EEPROM-ból a RAM-ban levő változókba a beállított határértékeket.
 * Indulás után egyszer meghívandó függvény.
 */
void Config_InitRTValues();

/**
 * Beállítja és az EEPROM-ba menti a felső határértékeket.
 * @param intLimit      A felső határérték egészrésze.
 * @param fractLimit    A felső határérték törtrésze.
 */
bool Config_SetUpLimit(int16_t intLimit, int16_t fractLimit);

/**
 * Beállítja és az EEPROM-ba menti az alsó határértékeket.
 * @param intLimit      Az alsó határérték egészrésze.
 * @param fractLimit    Az alsó határérték törtrésze.
 */
bool Config_SetBottomLimit(int16_t intLimit, int16_t fractLimit);

/**
 * A paraméterként kapott pointerekbe másolja az aktuális felső határértéket.
 * 
 * @param p_intLimit   A felső határérték egészrészét ide másolja a függvény.
 * @param p_fractLimit A felső határérték törtrészét ide másolja a függvény.
 */
void Config_GetUpLimit(int16_t* p_intLimit, int16_t* p_fractLimit);

/**
 * A paraméterként kapott pointerekbe másolja az aktuális alsó határértéket.
 * 
 * @param p_intLimit   Az alsó határérték egészrészét ide másolja a függvény.
 * @param p_fractLimit Az alsó határérték törtrészét ide másolja a függvény.
 */
void Config_GetBottomLimit(int16_t* p_intLimit, int16_t* p_fractLimit);

#endif	/* CONFIG_H */

