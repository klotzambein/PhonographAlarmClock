#import "TimerOne.h"
#import "servo.c"

#define TIMER_INTERVAL 20000 // aka 50 hz
#define PIN_SERVO1 9
#define PIN_SERVO2 10

SERVO_CREATE(1, SERVO_DEFAULT_DUTY)
SERVO_CREATE(2, SERVO_DEFAULT_DUTY)

void setup()
{
    Timer1.initialize(TIMER_INTERVAL);
    Timer1.attachInterrupt(tick);
    SERVO_INIT(1)
    SERVO_INIT(2)
}

void loop()
{
    SERVO_SET(1, SERVO_MAX_DUTY)
    delay(1000);
    SERVO_SET(2, SERVO_MAX_DUTY)
    delay(1000);
    SERVO_SET(1, SERVO_MIN_DUTY)
    delay(1000);
    SERVO_SET(2, SERVO_MIN_DUTY)
    delay(1000);
}

void tick()
{
    SERVO_UPDATE(1)
    SERVO_UPDATE(2)
}