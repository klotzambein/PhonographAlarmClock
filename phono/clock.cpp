#import "clock.h"

#import <Wire.h>
#import "text.h"

bool checkTime(uint8_t hours, uint8_t minutes);

Time currentTime;
uint8_t lastSeconds = 0xFF;

Alarm alarm[ALARM_COUNT];

bool updateClock()
{
    readClock(&currentTime);

    if (currentTime.seconds < lastSeconds)
        return testAlarms();

    lastSeconds = currentTime.seconds;

    return false;
}

void writeToClock(uint8_t addr, const uint8_t *data, uint16_t size)
{
    Wire.beginTransmission(CLOCK_ADDRESS);
    Wire.write(addr);
    Wire.write(data, size);
    Wire.endTransmission();
}

void settupClock(bool enable, Time *time, bool sqwDefault, bool sqwEnable, uint8_t sqwMode)
{
    Wire.beginTransmission(CLOCK_ADDRESS);
    Wire.write(0);
    Wire.write((time->seconds & 0x7F) | (enable ? 0x00 : 0x80));
    Wire.write(time->minutes & 0x7F);
    Wire.write(time->hours & 0x3F);
    Wire.write(time->day & 0x07);
    Wire.write(time->date & 0x3F);
    Wire.write(time->month & 0x1F);
    Wire.write(time->year);
    Wire.write((sqwDefault ? 0x80 : 0x00) | (sqwEnable ? 0x10 : 0x00) | (sqwMode & 0x03));
    Wire.endTransmission();
}

void readClock(Time *time)
{
    Wire.beginTransmission(CLOCK_ADDRESS);
    Wire.write(0);
    Wire.endTransmission();

    Wire.requestFrom(CLOCK_ADDRESS, 7);

    time->seconds = Wire.read() & 0x7F;
    time->minutes = Wire.read() & 0x7F;
    time->hours = Wire.read() & 0x3F;
    time->day = Wire.read() & 0x07;
    time->date = Wire.read() & 0x3F;
    time->month = Wire.read() & 0x1F;
    time->year = Wire.read();
}

void readAlarms()
{
    for (int i = 0; i < ALARM_COUNT; i++)
    {
        Wire.beginTransmission(CLOCK_ADDRESS);
        Wire.write(ALARM_SAVE_OFFSET + (i * sizeof(Alarm)));
        Wire.endTransmission();

        Wire.requestFrom(CLOCK_ADDRESS, sizeof(Alarm));
        uint8_t data[4] = {Wire.read(),
                           Wire.read(),
                           Wire.read(),
                           Wire.read()};

        alarms[i].type = data[0] & 0x03;
        alarms[i].enabled = data[0] & 0x02 >> 1;
        switch (alarms[i].type)
        {
        case 1:
            alarms[i].atTime.hours = data[1];
            alarms[i].atTime.minutes = data[2];
            break;
        case 2:
            alarms[i].atTimeDay.dayMask = data[1];
            alarms[i].atTimeDay.hours = data[2];
            alarms[i].atTimeDay.minutes = data[3];
            break;
        case 3:
            alarms[i].atWifiEvent.eventID = data[1];
            break;
        }
    }
}

int addAlarm(Alarm *alarm)
{
    for (int i = 0; i < ALARM_COUNT; i++)
    {
        if (alarms[i].type == 0)
        {
            alarms[i] = *alarm;
            saveAlarm(i);
            return i;
        }
    }
    return -1;
}

void updateAlarm(int alarm, Alarm *newAlarm)
{
    alarms[alarm] = *newAlarm;
    saveAlarm(alarm);
}

void removeAlarm(int alarm)
{
    alarms[alarm].type = 0;
    saveAlarm(i);
}

void enableAlarm(int alarm)
{
    alarms[alarm].enabled = 1;
    saveAlarm(alarm);
}

void disableAlarm(int alarm)
{
    alarms[alarm].enabled = 0;
    saveAlarm(alarm);
}

bool testAlarms()
{
    for (int i = 0; i < ALARM_COUNT; i++)
    {
        if (alarms[i].enabled)
            switch (alarms[i].type)
            {
            case 0:
            case 3:
                continue;
            case 1:
                if (checkTime(alarms[i].atTime.hours, alarms[i].atTime.minutes))
                    return true;
                else
                    continue;
            case 2:
                if (checkTime(alarms[i].atTimeDay.hours, alarms[i].atTimeDay.minutes) &&
                    alarms[i].atTimeDay.dayMask & (0x1 << currentTime.day))
                    return true;
                else
                    continue;
            }
    }
    return false;
}

bool testWifiAlarms(uint8_t event)
{
    for (int i = 0; i < ALARM_COUNT; i++)
        if (alarms[i].type == 3 &&
            alarms[i].enabled &&
            alarms[i].atWifiEvent.eventID == event)
            return true;
}

void saveAlarms()
{
    for (int i = 0; i < ALARM_COUNT; i++)
        writeToClock(ALARM_SAVE_OFFSET + i, (uint8_t *)&alarms[i], sizeof(Alarm));
}

void saveAlarm(int alarm)
{
    writeToClock(ALARM_SAVE_OFFSET + alarm, (uint8_t *)&alarms[alarm], sizeof(Alarm));
}

int sprintWeekday(char *str, unsigned int day)
{
    switch (day % 7)
    {
    case 0:
        WRITE2STR('M', 'o', 'n');
        break;
    case 1:
        WRITE2STR('T', 'u', 'e');
        break;
    case 2:
        WRITE2STR('W', 'e', 'd');
        break;
    case 3:
        WRITE2STR('T', 'h', 'u');
        break;
    case 4:
        WRITE2STR('F', 'r', 'i');
        break;
    case 5:
        WRITE2STR('S', 'a', 't');
        break;
    case 6:
        WRITE2STR('S', 'u', 'n');
        break;
    }
    return 3;
}

int sprintTime(char *str, Time *time)
{
    str += sprintHex(str, time->hours);
    WRITE2STR(':')
    str += sprintHex(str, time->minutes);
    WRITE2STR(':')
    str += sprintHex(str, time->seconds);
    WRITE2STR(' ')
    str += sprintWeekday(str, time->day);
    WRITE2STR(' ')
    str += sprintHex(str, time->date);
    WRITE2STR('/')
    str += sprintHex(str, time->month);
    WRITE2STR('/')
    str += sprintHex(str, time->year);
    return 21;
}

int sprintAlarm(char *str, Alarm *alarm)
{
    switch (alarm->type)
    {
    case 0:
        return sprintString(str, "No-Alarm", 8);
    case 1:
        WRITE2STR('7', 'F', '-')
        str += sprintHex(str, alarm->atTime.hours);
        WRITE2STR(':')
        str += sprintHex(str, alarm->atTime.minutes);
        return 8;
    case 2:
        str += sprintHex(str, alarm->atTimeDay.dayMask);
        WRITE2STR('-')
        str += sprintHex(str, alarm->atTimeDay.hours);
        WRITE2STR(':')
        str += sprintHex(str, alarm->atTimeDay.minutes);
        return 8;
    case 3:
        WRITE2STR('W', 'i', 'F', 'i', '0', 'x')
        str += sprintHex(str, alarm->atWifiEvent.eventID);
        return 8;
    }
    return 0;
}

//---------------------------------

bool checkTime(uint8_t hours, uint8_t minutes)
{
    return currentTime.hours & 0x3F == hours & 0x3F &&
           currentTime.minutes & 0x7F == minutes & 0x7F;
}