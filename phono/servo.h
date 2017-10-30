#ifndef SERVO_H
#define SERVO_H

#define SERVO_MIN_DUTY 30     // the shortest duty cycle of a 50hz servo
#define SERVO_MAX_DUTY 130    // the longest duty cycle of a 50hz servo
#define SERVO_DEFAULT_DUTY 80 // the default duty cycle of a 50hz servo

#define SERVO_SET(num, duty) SetServoTarget(&servo##num, duty);                        // Set servo duty cycle
#define SERVO_CREATE(num, startDuty) Servo servo##num = SERVO(startDuty);              //Define servo var
#define SERVO_INIT(num) Timer1.pwm(PIN_SERVO##num, 0);                                 // init servo with timer1 (PIN_SERVOx has to exist)
#define SERVO_UPDATE(num) Timer1.setPwmDuty(PIN_SERVO##num, UpdateServo(&servo##num)); //Update servo in timer tick (PIN_SERVOx has to exist)

typedef struct
{
    unsigned int currentPos;
    volatile unsigned int targetPos;
    volatile unsigned int speed;         // how fast should currentPos change
    volatile unsigned int controlRepeat; // how often should control func be invoked
    unsigned int counter;                //counts up to controlRepeat;
} Servo;
#define SERVO(startDuty)              \
    {                                 \
        startDuty, startDuty, 1, 1, 0 \
    }

int UpdateServo(Servo *servo);
void SetServoTarget(Servo *servo, int duty);

#endif