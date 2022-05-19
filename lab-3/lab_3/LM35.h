#ifndef LM35_h
#define LM35_h

#include <Arduino.h>

class LM35
{
    public:
        LM35(byte pin);
        void initSensor();
        int readData();
        float convertMillivotsToCelsius(int value);
    protected:
        byte SensorPin;

};

#endif