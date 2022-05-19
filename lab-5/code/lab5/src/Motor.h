#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

class Motor
{
    private:
        byte MotorPin1;
        byte MotorPin2;
        byte ControlPin;

    public:
        Motor();
        void init(byte pin1, byte pin2, byte pin3);
        void changeStateWithSpeed(bool direction, int speed); 
        // direction = true -> clockwise
        // direction = false -> anti-clockwise
        void changeState(bool direction);
};

#endif