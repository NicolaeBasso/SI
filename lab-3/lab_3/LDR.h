#ifndef LDR_h
#define LDR_h

#include <Arduino.h>

//for LDR (ADC to Lux transformation) 
#define MAX_ADC_READING           1023
#define ADC_REF_VOLTAGE           5.0
#define REF_RESISTANCE            4500 //объясни откуда это число;) 
#define LUX_CALC_SCALAR           12518931
#define LUX_CALC_EXPONENT         -1.405

class LDR
{
    public:
        LDR(int pin);
        void initSensor();
        int readData();
        float ldrToLux(int data);

    private:
        int LDRPin; // Trigger Pin of LDR Sensor
};

#endif