#include "LM35.h"

LM35::LM35(byte pin)
{
    SensorPin = pin;
}

float LM35::readData()
{
    return analogRead(SensorPin)/2;
}

