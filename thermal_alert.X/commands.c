#include "commands.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "mcc.h"

#include "25AA040A.h"
#include "temperature.h"
#include "config.h"
#include "macros.h"
#include "alarm.h"

//-----------------------------------------------------------------------------
bool processCommand(char const* buf)
{
    bool success = false;
    if (strncmp(buf, "greet", 5) == 0)
    {
        printf("Hello world!\r\n");
    }
    else if (strncmp(buf, "temp", 4) == 0)
    {
        printf("Temperature: %d.%d C\r\n", CurTempInt, CurTempFract);
    }
    else if ( (*buf == 'u' || *buf == 'b') &&
              strncmp(buf + 1, "limit", 5) == 0)
    {
        int16_t curIntLimit, curFractLimit;
        
        int16_t intLimit = 0;
        int16_t fractLimit = 0;
        
        // [ u | b ]limit<space>['-' | <számjegy>][, <számjegy>+]
        if (strlen(buf) > 8 && buf[6] == ' ' && (isdigit(buf[7]) || buf[7] == '-'))
        {
            bool saveOk = false;
            char* intEnd;
            intLimit = (int) strtol(buf + 7, &intEnd, 10);
            fractLimit = 0;
            if (*intEnd == '.' && *(intEnd + 1) != '\0')
            {
                fractLimit = (int) strtol(intEnd + 1, NULL, 10);
            }
            if(*buf == 'u')
            {
                saveOk = Config_SetUpLimit(intLimit, fractLimit);
                printf("Up limit ");
            }
            else if(*buf == 'b')
            {
                saveOk = Config_SetBottomLimit(intLimit, fractLimit);
                printf("Bottom limit ");
            }
            if(saveOk)
            {
                printf("%d.%d C set\r\n", intLimit, fractLimit);
            }
            else
            {
                printf("invalid\r\n");
            }
        }
        else
        {
            if(*buf == 'u')
            {
                Config_GetUpLimit(&curIntLimit, &curFractLimit);
                printf("Up limit: ");
            }
            else if(*buf == 'b')
            {
                Config_GetBottomLimit(&curIntLimit, &curFractLimit);
                printf("Bottom limit: ");
            }
            printf("%d.%d C\r\n", curIntLimit, curFractLimit);
        }
    }
    else if(strncmp(buf, "events", 6) == 0)
    {
        printAllAlarmEvents();
    }
    else if(strncmp(buf, "clrevents", 9) == 0)
    {
        printf("Clearing all events\r\n");
        clearAllAlarmEvents();
    }
    else if(strncmp(buf, "dump", 4) == 0)
    {
        EEPROM_25AA040A_Dump();
    }
    else
    {
        printf("Unknown cmd: ");
        printf("%s\r\n", buf);
        success = false;
    }
    return success;
}
//-----------------------------------------------------------------------------