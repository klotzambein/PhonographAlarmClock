//#import "TimerOne.h"
//#import "servo.h"
#import "clock.h"
#import "text.h"

#define TIMER_INTERVAL 20000 // aka 50 hz
#define PIN_SERVO1 9
#define PIN_SERVO2 10

//SERVO_CREATE(1, SERVO_DEFAULT_DUTY)
//SERVO_CREATE(2, SERVO_DEFAULT_DUTY)

void setup()
{
    Serial.begin(9600);

    //Timer1.initialize(TIMER_INTERVAL);
    //Timer1.attachInterrupt(tick);
    //SERVO_INIT(1)
    //SERVO_INIT(2)
}

void loop()
{
    char s[22];
    s[21] = 0;

    Time t = {0x30, 0x15, 0x16, 0x02, 0x30, 0x10, 0x17};
    Serial.println("Test1");
    //readClock(&t);
    Serial.println("Test2");

    sprintTime(&s[0], &t);
    Serial.println("Test3");
    Serial.println(s);
    delay(1000);
}

//void tick()
//{
//    SERVO_UPDATE(1)
//    SERVO_UPDATE(2)
//}