#include "alarm.h"

#include <xc.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "mcc.h"
#include "temperature.h"
#include "systime.h"
#include "25AA040A.h"
#include "lcd.h"

/** Riasztásban vagyunk-e */
volatile bool alarmOn = false;

/** A legutóbbi riasztás nyugtázva volt-e */
bool alarmAckd = false;

/** A legutóbbi riasztási esemény beálltának ideje */
SysTime lastAlarmTime = SysTime_NULL;

/** Mikor kapcsoltuk be legutoljára a buzzert riasztáshoz */
SysTime lastBuzStartTime = SysTime_NULL;

/** A riasztások részleteinek kezdőcíme az EEPROMban.
 * Az első bájt a számláló, utána jönnek sorban az események részletei. */
#define EVENTS_EEPROM_STARTADDR 0x0F

uint8_t SavedEventCounter = 0;

typedef __pack struct
{
    SysTime     Time;
    int16_t     TempInt;
    int16_t     TempFract;
    int16_t     LimitInt;
    int16_t     LimitFract;
    bool        Acknowledged;
    uint8_t     Pad;    // Így lesz egy EEPROM page a mérete
} AlarmEvent;

//-----------------------------------------------------------------------------
void _AlarmEvent_IncreaseSavedCounter()
{
    SavedEventCounter += 1;
    EEPROM_25AA040A_WriteByte(EVENTS_EEPROM_STARTADDR, SavedEventCounter);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void _AlarmEvent_SaveToAddress(uint16_t address, AlarmEvent* e)
{
    EEPROM_25AA040A_WriteBuffer(address, (uint8_t*)e, sizeof(AlarmEvent));
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void _saveAlarmEvent(AlarmEvent* e)
{
    _AlarmEvent_IncreaseSavedCounter();
    __delay_ms(5);
    printf("Saving alarm\r\n");
    printf("%lu.%u %d.%d C (%d.%d C)\r\n", e->Time.Sec, e->Time.Ms, e->TempInt, e->TempFract,
                                           e->LimitInt, e->LimitFract);
    _AlarmEvent_SaveToAddress(EVENTS_EEPROM_STARTADDR + 1 +
                              (SavedEventCounter - 1) * sizeof(AlarmEvent), e);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void _ACKLastSavedEvent()
{
    AlarmEvent newEvent;
    EEPROM_25AA040A_ReadToBuffer( EVENTS_EEPROM_STARTADDR + 1 +
                                 (SavedEventCounter - 1) * sizeof(AlarmEvent),
                                 (uint8_t*)&newEvent, sizeof(AlarmEvent));
    newEvent.Acknowledged = true;
    _AlarmEvent_SaveToAddress( EVENTS_EEPROM_STARTADDR + 1 +
                              (SavedEventCounter - 1) * sizeof(AlarmEvent), &newEvent);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void Alarm_Init()
{
    SavedEventCounter = EEPROM_25AA040A_ReadByte(EVENTS_EEPROM_STARTADDR);
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
bool IsAlarm()
{
    return alarmOn;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
SysTime GetLastAlarmTime()
{
    return lastAlarmTime;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void ACKAlarm()
{
    if (alarmOn && !alarmAckd)
    {
        printf("Alarm ACK'd\r\n");
        //                      ALARM
        LCDWriteStringXY(0, 1, "     ");
        alarmAckd = true;
        _ACKLastSavedEvent();
        if(BUZ_GetValue())
        {
            BUZ_SetLow();
        }
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void checkAlarm()
{
    bool alarmJustChanged = false;
    bool aboveUp = ABOVE_UPLIMIT(CurTempInt, CurTempFract);
    bool belowBottom = BELOW_BOTTOMLIMIT(CurTempInt, CurTempFract);
    if(!alarmOn && !alarmAckd)
    {
        if(aboveUp)
        {
            alarmJustChanged = true;
        }
        else if(belowBottom)
        {
            alarmJustChanged = true;
        }
    }
    
    if (alarmJustChanged)
    {
        BUZ_SetHigh();
        LED1_SetHigh();
        printf("ALARM: %d.%d C\r\n", CurTempInt, CurTempFract);
        LCDWriteStringXY(0,1, "ALARM");
        alarmOn = true;
        lastAlarmTime = SysTime_GetNow();
        
        AlarmEvent e;
        e.Time = lastAlarmTime;
        e.Acknowledged = false;
        e.TempInt = CurTempInt;
        e.TempFract = CurTempFract;
        if(aboveUp)
        {
            e.LimitInt = UpIntLimitRT;
            e.LimitFract = UpFractLimitRT;
        }
        else
        {
            e.LimitInt = BottomIntLimitRT;
            e.LimitFract = BottomFractLimitRT;
        }
        _saveAlarmEvent(&e);
    }

    if (!aboveUp && !belowBottom)
    {
        if (alarmOn)
        {
            BUZ_SetLow();
            LED1_SetLow();
            printf("ALARM OFF\r\n");
            //                      ALARM
            LCDWriteStringXY(0, 1, "     ");
        }
        alarmOn = false;
        alarmAckd = false;
    }
    
    SysTime curTime = SysTime_GetNow();
    if(alarmOn && !alarmAckd && ((curTime.Sec - lastBuzStartTime.Sec) > 30))
    {
        BUZ_SetHigh();
        lastBuzStartTime = curTime;
    }
    
    if(BUZ_GetValue() || LED1_GetValue())
    {
        uint32_t buzOnTime = SysTime_DiffMs(&lastBuzStartTime, &curTime);
        if (buzOnTime > 1000UL)
        {
            printf("Buz off\r\n");
            BUZ_SetLow();
            LED1_SetLow();
        }
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void printAllAlarmEvents()
{
    AlarmEvent evt;
    uint8_t i;
    printf("Alarm count: %u\r\n", (uint16_t)(SavedEventCounter & 0xFF));
    for(i = 0;i < SavedEventCounter; ++i)
    {
        EEPROM_25AA040A_ReadToBuffer(EVENTS_EEPROM_STARTADDR + 1 + i * sizeof(AlarmEvent),
                                     (uint8_t*)&evt, sizeof(AlarmEvent));
        printf("ALARM %d @ %lu.%u:\r\n", (int)i, evt.Time.Sec, evt.Time.Ms);
        printf("Temperature: %d.%d C, limit: %d.%d C\r\n", evt.TempInt, evt.TempFract, evt.LimitInt, evt.LimitFract);
        printf("%s\r\n", (evt.Acknowledged ? "Acknowledged" : "NOT acknowledged"));
        printf("\r\n");
    }
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
void clearAllAlarmEvents()
{
    AlarmEvent nullEvt;
    memset((void*)&nullEvt, 0, sizeof(AlarmEvent));
    uint8_t i;
    for(i = 0;i < SavedEventCounter; ++i)
    {
        EEPROM_25AA040A_WriteBuffer(EVENTS_EEPROM_STARTADDR + 1 + i * sizeof(AlarmEvent),
                                    (uint8_t*)&nullEvt, sizeof(AlarmEvent));
    }
    EEPROM_25AA040A_WriteByte(EVENTS_EEPROM_STARTADDR, 0);
    SavedEventCounter = 0;
}
//-----------------------------------------------------------------------------