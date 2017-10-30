#import "servo.h"

int UpdateServo(Servo *servo)
{
    if (++servo->counter >= servo->controlRepeat)
    {
        servo->counter = 0;
        if (servo->currentPos < servo->targetPos)
        {
            servo->currentPos += servo->speed;
            if (servo->currentPos > servo->targetPos)
                servo->currentPos = servo->targetPos;
        }
        else if (servo->currentPos > servo->targetPos)
        {
            servo->currentPos -= servo->speed;
            if (servo->currentPos < servo->targetPos)
                servo->currentPos = servo->targetPos;
        }
        return servo->currentPos;
    }
    return -1;
}

void SetServoTarget(Servo* servo, int duty)
{
    servo->targetPos = (duty < SERVO_MIN_DUTY) ? SERVO_MIN_DUTY : ((duty > SERVO_MAX_DUTY) ? SERVO_MAX_DUTY : duty);
}