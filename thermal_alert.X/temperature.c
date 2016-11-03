#include "temperature.h"

#include "DS18B20.h"
#include "lcd.h"
#include "mcc.h"
#include "systime.h"

int16_t CurrentTemperatureRaw = 0;
int16_t CurTempInt = 0;
uint8_t CurTempFract = 0;

//-----------------------------------------------------------------------------
void TempSensor_Init()
{
    bool OW_Ok = DS18B20_ResetAndDetect();
    if (OW_Ok)
    {
        printf("Temp sensor OK\r\n");
        DS18B20_SetResolution(DS18B20_Resolution_9bit);
    }
    else
    {
        printf("Temp sensor FAIL\r\n");
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void updateTemperature()
{
    // Statikus állapottároló változók

    // Éppen dolgozik a hőmérő
    static bool TempCheckInProgress = false;

    // A hőmérőn a mérés indításakor az idő
    static SysTime MeasStart = 0;

    static int RunCount = 0;

    ///////////// Innentől fut le minden egyes meghíváskor
    uint16_t curTime = SysTime_GetNow();
    if (TempCheckInProgress)
    {
        // Max. 750ms-et kell várni a hőmérőre, mi pedig nem sietünk sehova
        if (SysTime_DiffMs(&MeasStart, &curTime) > 750)
        {
            TempCheckInProgress = false;
            int16_t data = DS18B20_ReadRawTemperature();

            // A 3 elsőnek mért mintát még nem szűrjük, hogy gyorsan betaláljon a helyére a szűrő
            if (RunCount < 3)
            {
                ++RunCount;
                CurrentTemperatureRaw = data;
            }
            else
            {
                // Ez igazából egy diszkrét aluláteresztő szűrő, amelynek a mindenkori
                // mintavételezési idő az időállandója.
                CurrentTemperatureRaw = data / 2 + CurrentTemperatureRaw / 2;
            }
            
            // 0.5°C-os pontosság, vagyis az utolsó bit jelenti a fél fokot
            CurTempInt = CurrentTemperatureRaw / 2;
            CurTempFract = 5 * (CurrentTemperatureRaw & 0x01);


            LCDWriteIntXY(0, 0, CurTempInt, 2);
            LCDWriteStringXY(2, 0, ".");
            LCDWriteIntXY(3, 0, CurTempFract, 1);
            LCDGotoXY(4, 0);
            LCDData(0x00); // A ° jel a 0-s karakterre van mappelve
            LCDGotoXY(5, 0);
            LCDData('C');

            //            LCDWriteStringXY(0, 1, "Raw: ");
            //            LCDWriteIntXY(5, 1, data, 5);
            //            LCDWriteStringXY(10, 1, ",");
            //            int res = (int)DS18B20_ReadResolution();
            //            LCDWriteIntXY(13, 1, res + 9, 2);
        }
    }

    // Kb. 5 mp-enként mintavételezünk, nem cél a tökéletes pontosság
    if (SysTime_DiffMs(&MeasStart, &curTime) >= 5000 && !TempCheckInProgress)
    {

        DS18B20_StartConversion();
        TempCheckInProgress = true;
        MeasStart = SysTime_GetNow();
    }
}
//-----------------------------------------------------------------------------