#include "MotorDriver298.h"

MotorDriver298::MotorDriver298(byte pin1, byte pin2, byte pin3)
{
    motorA.init(pin1, pin2, pin3);
}

MotorDriver298::MotorDriver298(byte pin1, byte pin2, byte pin3, byte pin4, byte pin5, byte pin6)
{
    motorA.init(pin1, pin2, pin3);
    motorB.init(pin4, pin5, pin6);
    motorQuantity = true;
}

void MotorDriver298::drive(bool side, int speed)
{
    if(!side && motorQuantity)
    {
        motorB.changeStateWithSpeed((speed >= 0), (abs(speed) * 2.55 + 0.5));
    }
    else
    {
        motorA.changeStateWithSpeed((speed >= 0), (abs(speed) * 2.55 + 0.5));
    }
}