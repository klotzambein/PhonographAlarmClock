#import "clock.h"

#import <Wire.h>
#import "text.h"

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
    Wire.write((time->seconds & 0x7F) | (enable ? 0x80 : 0x00));
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