#ifndef _25AA040A_H_
#define	_25AA040A_H_

#include "mcc.h"


#define EEPROM_25AA040A_LASTADDRESS 0x1FF   // 512 bájtos, utolsó cím: 511

/**
 * Kiolvas egy bájtot az EEPROM adott címéről.
 * 
 * @param address 9 bites cím, ahonnan az adatot szeretnénk olvasni.
 * 
 * @return A kiolvasott bájt.
 */
uint8_t EEPROM_25AA040A_ReadByte(uint16_t address);

/**
 * Több bájtot olvas egy pufferbe az EEPROM adott címétől kezdve.
 * 
 * @param address A kiolvasandó adatok kezdőcíme (9 bites).
 * 
 * @param dst   A kiolvasott adatok erre a memóriaterületre lesznek másolva. 
 * 
 * @param dataLength A kiolvasandó bájtok száma.
 *                   Amennyiben address+dataLength > 512 (ennyi bájtos az EEPROM),
 *                   akkor a túlcsorduló rész a 0-s címtől folytatódóan lesz kiolvasva.
 */
void EEPROM_25AA040A_ReadToBuffer(uint16_t address, uint8_t* dst, uint16_t dataLength);

/**
 * A megadott címre írja a kapott bájtot.
 * 
 * @param address   9 bites cím, ahova írni szeretnénk.
 * 
 * @param data      A beírandó bájt.
 */
void EEPROM_25AA040A_WriteByte(uint16_t address, uint8_t data);

/**
 * A megadott címtől kezdve dataLength bájtot ír az EEPROM-ba. A beírás laponként történik.
 * 
 * @param address       A kezdőcím, ahonnan kezdve írjuk a bájtokat. Az EEPROM végétől legalább
 *                      dataLength bájttal visszább kell legyen.
 * 
 * @param data          Az írandó adatok pointere.
 * @param dataLength    Az írandó bájtok száma, maximum 512 - address.
 */
void EEPROM_25AA040A_WriteBuffer(uint16_t address, uint8_t* data, uint8_t dataLength);

/**
 * A soros port kimenetre olvassa az EEPROM teljes tartalmát.
 */
void EEPROM_25AA040A_Dump();


#endif	/* _25AA040A_H_ */

