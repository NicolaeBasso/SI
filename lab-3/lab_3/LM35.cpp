#include "LM35.h"

LM35::LM35(byte pin)
{
    SensorPin = pin;
}

int LM35::readData()
{
    return analogRead(LDRPin);
}

float LM35::convertMillivotsToCelsius(int mv)
{
    return mv/10;
}