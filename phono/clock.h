#ifndef CLOCK_H
#define CLOCK_H

#import <Arduino.h>

#define CLOCK_ADDRESS 0x68
#define ALARM_COUNT 10
#define ALARM_SAVE_OFFSET 8

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
extern Time currentTime;

typedef struct
{
    unsigned type : 2;
    unsigned enabled : 1;
    union {
        struct
        { //Type = 0x1; Alarm at time
            uint8_t hours;
            uint8_t minutes;
        } atTime;
        struct
        { //Type = 0x2; Alarm at time and Weekday
            uint8_t dayMask;
            uint8_t hours;
            uint8_t minutes;
        } atTimeDay;
        struct
        { //Type = 0x3; Alarm at wifi event
            uint8_t eventID;
        } atWifiEvent;
    };
} Alarm;
extern Alarm alarms[ALARM_COUNT];

bool updateClock(); //returns if alarm should ring

void writeToClock(uint8_t addr, const uint8_t *data, uint16_t size);

void settupClock(bool enable, Time *time, bool sqwDefault, bool sqwEnable, uint8_t sqwMode);
void readClock(Time *time);

void readAlarms();

int addAlarm(Alarm *alarm);
void updateAlarm(int alarm, Alarm *newAlarm);
void removeAlarm(int alarm);

void enableAlarm(int alarm);
void disableAlarm(int alarm);

bool testAlarms();
bool testWifiAlarms(uint8_t event);

void saveAlarms();
void saveAlarm(int alarm);

int sprintTime(char *str, Time *time);
int sprintAlarm(char *str, Alarm *alarm);
#endif