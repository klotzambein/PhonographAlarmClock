#import "TimerOne.h"
#import "Wire.h"
#import "servo.h"
#import "clock.h"
#import "text.h"
#import "files.h"

#define TIMER_INTERVAL 20000 // aka 50 hz
#define PIN_SERVO_UD 9
#define PIN_SERVO_LR 10

Servo servo_upDown = SERVO(SERVO_DEFAULT_DUTY);
Servo servo_leftRight = SERVO(SERVO_DEFAULT_DUTY);

void setup()
{
    Wire.begin(100);
    Serial.begin(9600);

    pinMode(13, OUTPUT);
    
    Timer1.initialize(TIMER_INTERVAL);
    Timer1.attachInterrupt(tick);
    Timer1.pwm(PIN_SERVO_UD, 0);
    Timer1.pwm(PIN_SERVO_LR, 0);

    filePages[7] = {0x1883,
                    0x0000,
                    0x0000,
                    0x0008};

    char test[30] = "                             ";
    sprintFileAddress(&test[0], 7, 30);
    Serial.println(test);
    findFile("home");

    Time tim = {0x30, 0x25, 0x17, 0x1, 0x20, 0x02, 0x17};
    settupClock(true, &tim, false, false, 0);
}

void loop()
{
    /*char s[22];
    s[21] = 0;

    Time t;
    readClock(&t);

    sprintTime(&s[0], &t);
    //Serial.println(s);
    delay(5000);*/

    /*SetServoTarget(&servo_upDown, SERVO_MIN_DUTY);
    delay(1000);
    SetServoTarget(&servo_leftRight, SERVO_MIN_DUTY);
    delay(1000);
    SetServoTarget(&servo_upDown, SERVO_MAX_DUTY);
    delay(1000);
    SetServoTarget(&servo_leftRight, SERVO_MAX_DUTY);
    delay(1000);*/
}

void tick()
{
    Timer1.setPwmDuty(PIN_SERVO_UD, UpdateServo(&servo_upDown));
    Timer1.setPwmDuty(PIN_SERVO_LR, UpdateServo(&servo_leftRight));
}