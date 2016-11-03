#include "systime.h"

#include <stdlib.h>

#include "mcc.h"

//-----------------------------------------------------------------------------
SysTime SysTime_GetNow()
{
    SysTime result;
    result.Sec = TMR4_GetSec();
    result.Ms = TMR4_GetMs();
    
    return result;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
uint32_t SysTime_DiffMs(const SysTime* firstTime, const SysTime* secondTime)
{
    return ((uint32_t)secondTime->Ms - (uint32_t)firstTime->Ms) + (secondTime->Sec - firstTime->Sec) * 1000;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
SysTime SysTime_Diff(const SysTime* firstTime, const SysTime* secondTime, SysTime* dst)
{
    SysTime result;
    uint32_t msDiff = (uint32_t) labs(SysTime_DiffMs(firstTime, secondTime));
    result.Sec = msDiff / 1000;
    result.Ms = (uint16_t)(msDiff - result.Sec);
    return result;
}
//-----------------------------------------------------------------------------
