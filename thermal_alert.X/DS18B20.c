#include "DS18B20.h"

//-----------------------------------------------------------------------------
bool DS18B20_ResetAndDetect()
{
    bool present = OW_reset_pulse();
    return (present == CLEAR);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void DS18B20_StartConversion()
{
    INTERRUPT_GlobalInterruptDisable();
    
    OW_reset_pulse();
    OW_write_byte(DS18B20_Command_SkipRom);
    OW_write_byte(DS18B20_Command_Convert_T);
    
    INTERRUPT_GlobalInterruptEnable();
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
int16_t DS18B20_ReadRawTemperature()
{
    int16_t result = 0;
    
    INTERRUPT_GlobalInterruptDisable();
    OW_reset_pulse();
    OW_write_byte(DS18B20_Command_SkipRom);
    OW_write_byte(DS18B20_Command_ReadScratchpad);
    
    int8_t lowbyte = OW_read_byte();
    int8_t hibyte = OW_read_byte();
    OW_reset_pulse();
    INTERRUPT_GlobalInterruptEnable();
    
    result = (int16_t)(hibyte << 8) | lowbyte;
    
    
    return result;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
DS18B20_Resolution DS18B20_ReadResolution()
{
    uint8_t result = 0;
    uint8_t resultBytes[9];
    int i;
    
    INTERRUPT_GlobalInterruptDisable();
    OW_reset_pulse();
    OW_write_byte(DS18B20_Command_SkipRom);
    OW_write_byte(DS18B20_Command_ReadScratchpad);
    
    for(i = 0;i<9;++i)
    {
        resultBytes[i] = OW_read_byte();
    }
    OW_reset_pulse();
    INTERRUPT_GlobalInterruptEnable();

    result = resultBytes[4];
    
    // 5-6. bit érdekel minket
    result >>= 5;
    result &= 0b11;
    
    return (DS18B20_Resolution)result;
    
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void DS18B20_SetResolution(DS18B20_Resolution res)
{
    uint8_t configData = 0x00;// (uint8_t)(res << 5);
    
    INTERRUPT_GlobalInterruptDisable();
    OW_reset_pulse();
    OW_write_byte(DS18B20_Command_SkipRom);
    OW_write_byte(DS18B20_Command_WriteScratchpad);
    
    // Th és Tl regiszterek, a riasztáshoz használtak, most nincs rájuk szükség, lehet bármi
    OW_write_byte(0);
    OW_write_byte(0);
    
    OW_write_byte(configData);
    
    OW_reset_pulse();
    OW_write_byte(DS18B20_Command_SkipRom);
    OW_write_byte(DS18B20_Command_CopyScratchpad);
    INTERRUPT_GlobalInterruptEnable();
    
}
//-----------------------------------------------------------------------------
