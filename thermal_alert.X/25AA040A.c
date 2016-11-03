#include "25AA040A.h"

#include <xc.h>

#include "mcc.h"
#include "systime.h"

typedef enum
{
    EEPROM_READ = 0b00000011,
    EEPROM_WRITE = 0b00000010,
    EEPROM_WRDI = 0b00000100,
    EEPROM_WREN = 0b00000110,
    EEPROM_RDSR = 0b00000101,
    EEPROM_WRSR = 0b00000001
} EEPROM_25AA040A_Instruction;

#define EEPROM_OPCODE_WithAddress(opcode, address)  (opcode) | ( ( (address) >> 9) << 3)

//-----------------------------------------------------------------------------

uint8_t _EEPROM_25AA040A_ReadStatus()
{
    uint8_t regVal;
    CS_SetLow();
    SPI_Exchange8bit(EEPROM_RDSR);
    regVal = SPI_Exchange8bit(0);
    CS_SetHigh();
    return regVal;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

bool _EEPROM_25AA040A_WriteEnable()
{
    bool statusOk = false;
    uint8_t statusReg = 0;
    CS_SetLow();
    SPI_Exchange8bit(EEPROM_WREN);
    CS_SetHigh();
    SysTime start = SysTime_GetNow();
    SysTime curTime;
    do
    {
        statusReg = _EEPROM_25AA040A_ReadStatus();
        statusOk = !!(statusReg & 0x02); // a true fixen 1-re van #define-olva...
        curTime = SysTime_GetNow();
    }
    while (!statusOk && SysTime_DiffMs(&start, &curTime) < 100);
//    printf("Status reg: 0x%x \r\n", statusReg);
    return statusOk;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

uint8_t EEPROM_25AA040A_ReadByte(uint16_t address)
{
    uint8_t opcode = EEPROM_OPCODE_WithAddress(EEPROM_READ, address);
    uint8_t result = 0xAA;
    
//    printf("Reading byte from 0x%x\r\n", address);
    
    CS_SetLow();
    SPI_Exchange8bit(opcode);
    result = SPI_Exchange8bit((uint8_t) (address & 0xFF));
    result = SPI_Exchange8bit(0);
    CS_SetHigh();

//    printf("Byte: 0x%x\r\n", result);
    return result;
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void EEPROM_25AA040A_ReadToBuffer(uint16_t address, uint8_t* dst, uint16_t dataLength)
{
    if (dst != NULL)
    {
//        printf("Reading %u bytes from 0x%x\r\n", dataLength, address);
        uint8_t opcode = EEPROM_OPCODE_WithAddress(EEPROM_READ, address);
        uint16_t cntr = 0;
        CS_SetLow();
        SPI_Exchange8bit(opcode);
        SPI_Exchange8bit((uint8_t) (address & 0xFF));

        while (cntr < dataLength)
        {
            *(dst + cntr) = SPI_Exchange8bit(0);
            ++cntr;
        }
        CS_SetHigh();
//        for(cntr = 0;cntr < dataLength; ++cntr)
//        {
//            printf("0x%x ", *(dst + cntr));
//        }
//        printf("\r\n");
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

void EEPROM_25AA040A_WriteByte(uint16_t address, uint8_t data)
{
    uint8_t opcode = EEPROM_OPCODE_WithAddress(EEPROM_WRITE, address);
    
//    printf("Writing byte to 0x%x\r\n", address);
    
    bool WREN_Ok = _EEPROM_25AA040A_WriteEnable();
    if (WREN_Ok)
    {
        CS_SetLow();
        SPI_Exchange8bit(opcode);
        SPI_Exchange8bit((uint8_t) (address & 0xFF));
        SPI_Exchange8bit(data);
        CS_SetHigh();
    }
    else
    {
        printf("EEPROM write failed\r\n");
    }
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void EEPROM_25AA040A_WriteBuffer(uint16_t address, uint8_t* data, uint8_t dataLength)
{
    uint8_t pageCount = dataLength / 16;
    uint8_t lastPageLen = dataLength - pageCount * 16;
//    printf("PageCount, lastPageLen: %u, %u\r\n", pageCount, lastPageLen);
    uint8_t i;
    
    if(address + dataLength > EEPROM_25AA040A_LASTADDRESS)
    {
        printf("EEPROM size smaller than %u\r\n", address + dataLength);
        return;
    }
    
//    printf("Writing %u bytes to 0x%x\r\n", (uint16_t)(dataLength & 0xFF), address);
    
    for (i = 0; i <= pageCount; ++i)
    {
        uint8_t bytesOnPage = 16;
        if (i == pageCount)
        {
            bytesOnPage = lastPageLen;
        }
        if (bytesOnPage > 0)
        {
            // 5*16 ms-t kell várni az előző írás befejezésére
            if(i > 0)
            {
                __delay_ms(5 * 16);
            }
            
            uint16_t pageAddr = address + i * 16;
//            printf("Cur. addr: 0x%x\r\n", pageAddr);
//            uint8_t cntr;
//            for(cntr = 0;cntr<bytesOnPage;++cntr)
//            {
//                printf("0x%x " ,*(data + i * 16 + cntr));
//            }
//            printf("\r\n");
            uint8_t opcode = EEPROM_OPCODE_WithAddress(EEPROM_WRITE, pageAddr);
            bool WREN_Ok = _EEPROM_25AA040A_WriteEnable();
            if (WREN_Ok)
            {
                uint8_t j;

                CS_SetLow();
                SPI_Exchange8bit(opcode);
                SPI_Exchange8bit((uint8_t) (pageAddr & 0xFF));
                for (j = 0; j < bytesOnPage; ++j)
                {
                    SPI_Exchange8bit(*(data + i * 16 + j));
                }
                CS_SetHigh();
            }
            else
            {
                printf("EEPROM write failed\r\n");
            }
        }
    }
    __delay_ms(5);
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void EEPROM_25AA040A_Dump()
{
    CS_SetLow();
    SPI_Exchange8bit(EEPROM_READ);
    SPI_Exchange8bit(0);
    uint16_t i;
    printf("0x000: ");
    for(i = 0;i<=EEPROM_25AA040A_LASTADDRESS;++i)
    {
        uint8_t b = SPI_Exchange8bit(0);
        printf("0x%02x ", (uint16_t)(b & 0xff));
        if(i % 16 == 15 && i != EEPROM_25AA040A_LASTADDRESS) printf("\r\n0x%03x: ", (i + 1));
    }
    CS_SetHigh();
}
//-----------------------------------------------------------------------------