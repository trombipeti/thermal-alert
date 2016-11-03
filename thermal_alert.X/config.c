#include "config.h"

#include <stdbool.h>

#include "mcc.h"
#include "25AA040A.h"

#define UPLIMIT_STARTADDR       0x00

#define BOTTOMLIMIT_STARTADDR   0x04

int16_t UpIntLimitRT = 0;
int16_t UpFractLimitRT = 0;
int16_t BottomIntLimitRT = 0;
int16_t BottomFractLimitRT = 0;

//-----------------------------------------------------------------------------
void Config_InitRTValues()
{
    Config_GetUpLimit(&UpIntLimitRT, &UpFractLimitRT);
    Config_GetBottomLimit(&BottomIntLimitRT, &BottomFractLimitRT);
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
bool Config_SetUpLimit(int16_t intLimit, int16_t fractLimit)
{
    bool success = false;
    if( (intLimit < CONFIG_LIMIT_MAX ||
        (intLimit == CONFIG_LIMIT_MAX && fractLimit == 0)) &&
        (intLimit > BottomIntLimitRT ||
        (intLimit == BottomIntLimitRT && fractLimit > BottomFractLimitRT)))
    {
        // LSB first írjuk be
        UpIntLimitRT = intLimit;
        UpFractLimitRT = fractLimit;

        uint8_t writeData[4];
        writeData[0] = intLimit & 0xFF;
        writeData[1] = intLimit >> 8;
        writeData[2] = fractLimit & 0xFF;
        writeData[3] = fractLimit >> 8;
        EEPROM_25AA040A_WriteBuffer(UPLIMIT_STARTADDR, writeData, 4);
        
        success = true;
    }
    return success;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
bool Config_SetBottomLimit(int16_t intLimit, int16_t fractLimit)
{
    bool success = false;
    if( (intLimit > CONFIG_LIMIT_MIN ||
        (intLimit == CONFIG_LIMIT_MIN && fractLimit > 0)) &&
        (intLimit < UpIntLimitRT ||
        (intLimit == UpIntLimitRT && fractLimit < UpFractLimitRT)))
    {
        // LSB first írjuk be    
        BottomIntLimitRT = intLimit;
        BottomFractLimitRT = fractLimit;

        uint8_t writeData[4];
        writeData[0] = intLimit & 0xFF;
        writeData[1] = intLimit >> 8;
        writeData[2] = fractLimit & 0xFF;
        writeData[3] = fractLimit >> 8;
        EEPROM_25AA040A_WriteBuffer(BOTTOMLIMIT_STARTADDR, writeData, 4);
        
        success = true;
    }
    return success;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void Config_GetUpLimit(int16_t* p_intLimit, int16_t* p_fractLimit)
{
    uint8_t bufData[4];
    EEPROM_25AA040A_ReadToBuffer(UPLIMIT_STARTADDR, bufData, 4);
    
    // LSB first van az eepromban
    *p_intLimit   = (int16_t)bufData[0] | (int16_t)(bufData[1] << 8);
    *p_fractLimit = (int16_t)bufData[2] | (int16_t)(bufData[3] << 8);
    
    UpIntLimitRT = *p_intLimit;
    UpFractLimitRT = *p_fractLimit;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void Config_GetBottomLimit(int16_t* p_intLimit, int16_t* p_fractLimit)
{
    uint8_t bufData[4];
    EEPROM_25AA040A_ReadToBuffer(BOTTOMLIMIT_STARTADDR, bufData, 4);
    
    // LSB first van az eepromban
    *p_intLimit   = (int16_t)bufData[0] | (int16_t)(bufData[1] << 8);
    *p_fractLimit = (int16_t)bufData[2] | (int16_t)(bufData[3] << 8);
    
    BottomIntLimitRT = *p_intLimit;
    BottomFractLimitRT = *p_fractLimit;
}
//-----------------------------------------------------------------------------
