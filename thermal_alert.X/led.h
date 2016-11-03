#ifndef COMMON_H
#define	COMMON_H

#include <stdint.h>

/**
 * 100 ms-re felvillantja a LED-et, majd kikapcsolja. Blokkoló függvény.
 */
void FlashLed100ms();

void FlashLedCallback(void* param);

#endif	/* COMMON_H */

