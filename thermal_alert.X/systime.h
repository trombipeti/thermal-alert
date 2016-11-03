#ifndef TIME_H
#define	TIME_H

#include <stdint.h>

typedef struct _SysTime
{
    volatile uint32_t    Sec;
    volatile uint16_t    Ms;
} SysTime; /** Rendszeridő mérésére használt struktúra. Milliszekundum pontosságú. */

#define SysTime_NULL    { 0, 0 }

/** 
 * A TMR4 által számolt értékek alapján megadja a rendszer indulása óta eltelt időt.
 */
SysTime SysTime_GetNow();

/**
 * Megadja a két időpont közt eltelt időt milliszekundumban.
 * 
 * @param firstTime     Az idő, amitől kezdve eltel időt szeretnénk megtudni.
 * @param secondTime    Az idő, ameddig az eltelt időt szeretnénk megtudni. Későbbi időpont kell
 *                      legyen, mint firstTime, különben rosszul működik a függvény.
 * @return              A firstTime és a secondTime idők közt eltelt idő, milliszekundumban.
 */
uint32_t SysTime_DiffMs(const SysTime* firstTime, const SysTime* secondTime);

/**
 * A két megadott időpont közt eltelt idő mértékét adja meg.
 * 
 * @param firstTime     Az első idő, ettől kezdve számolja a függvény az eltelt időt.
 * @param secondTime    A második idő, idáig számolja a függvény az eltelt időt.
 *                      Csak akkor működik jól a függvény, ha későbbi, mint a firstTime.
 * @return  A két időpont közt eltelt idő.
 */
SysTime SysTime_Diff(const SysTime* firstTime, const SysTime* secondTime);

#endif	/* TIME_H */

