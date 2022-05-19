#ifndef MotorDriver298_h
#define MotorDriver298_h

#include <Arduino.h>
#include "Motor.h"

class MotorDriver298
{
    private:
        Motor motorA;
        Motor motorB;
        bool motorQuantity = false; //true = 2 motors, false - 1 motor

    public:
        MotorDriver298(byte pin1, byte pin2, byte pin3); //only motor A
        MotorDriver298(byte pin1, byte pin2, byte pin3, byte pin4, byte pin5, byte pin6); //motorA and motorB
        void drive(bool side, int speed);
        // motor "A" -> side = true
        // motor "B" -> side = false 
};

#endif