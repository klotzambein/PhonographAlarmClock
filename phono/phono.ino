#import "TimerOne.h"
#import "Wire.h"
#import "servo.h"
#import "clock.h"
#import "text.h"

#define TIMER_INTERVAL 20000 // aka 50 hz
#define PIN_SERVO1 9
#define PIN_SERVO2 10

SERVO_CREATE(1, SERVO_DEFAULT_DUTY)
SERVO_CREATE(2, SERVO_DEFAULT_DUTY)

void setup()
{
  Wire.begin(100);
  Serial.begin(9600);

  pinMode(13, OUTPUT);

  Timer1.initialize(TIMER_INTERVAL);
  Timer1.attachInterrupt(tick);
  SERVO_INIT(1)
  SERVO_INIT(2)
}

void loop()
{
  /*SERVO_SET(1, SERVO_MAX_DUTY);
  delay(1000);
  SERVO_SET(2, SERVO_MAX_DUTY);
  delay(1000);
  SERVO_SET(1, SERVO_MIN_DUTY);
  delay(1000);
  SERVO_SET(2, SERVO_MIN_DUTY);
  delay(1000);*/
  /*char s[22];
    s[21] = 0;

    Time t;
    readClock(&t);

    sprintTime(&s[0], &t);
    Serial.println(s);
    delay(100);*/
}

void tick()
{
  SERVO_UPDATE(1)
  SERVO_UPDATE(2)
}