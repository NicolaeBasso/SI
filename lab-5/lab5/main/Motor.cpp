#include "Motor.h"

Motor::Motor()
{

}

void Motor::init(byte pin1, byte pin2, byte pin3)
{
    MotorPin1 = pin1;
    MotorPin2 = pin2;
    ControlPin = pin3;

    pinMode(MotorPin1, OUTPUT);
    pinMode(MotorPin2, OUTPUT);
    pinMode(ControlPin, OUTPUT);
}

void Motor::changeState(bool direction)
{
    if (direction)
    {
        digitalWrite(MotorPin1, HIGH);
        digitalWrite(MotorPin1, LOW);
    }
    else
    {
        digitalWrite(MotorPin1, LOW);
        digitalWrite(MotorPin1, HIGH);
    }
}

void Motor::changeStateWithSpeed(bool direction, int speed)
{
    if (direction)
    {
        digitalWrite(MotorPin1, HIGH);
        digitalWrite(MotorPin2, LOW);
        analogWrite(ControlPin, speed);
    }
    else
    {
        digitalWrite(MotorPin1, LOW);
        digitalWrite(MotorPin2, HIGH);
        analogWrite(ControlPin, speed);
    }
}
