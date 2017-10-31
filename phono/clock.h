#ifndef CLOCK_H
#define CLOCK_H

#import <Arduino.h>

#define CLOCK_ADDRESS 0x68

typedef struct
{
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} Time;

void writeToClock(uint8_t addr, const uint8_t *data, uint16_t size);
void settupClock(bool enable, Time *time, bool sqwDefault, bool sqwEnable, uint8_t sqwMode);
void readClock(Time *time);
int sprintTime(char *str, Time *time);

#endif