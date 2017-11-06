#import "wifi.h"

#import "clock.h"
#import "WiFiEsp.h"

int sprintJsonAlarmList(char *str)
{
    str += sprintString(str, "\"alarms\":[");
    for (int i = 0; i < ALARM_COUNT; i++)
    {
        WRITE2STR('"')
        str += sprintAlarm(str, alarms[i]);
        WRITE2STR('"', ',')
    }
    str--;
    WRITE2STR(']', ';')
    return 11 + 11 * ALARM_COUNT; // 10+(1+8+2)*ALARM_COUNT-1+2
}