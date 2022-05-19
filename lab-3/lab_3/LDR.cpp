#include "LDR.h"

LDR::LDR(int pin)
{
    LDRPin = pin;
}

void LDR::initSensor()
{
    pinMode(LDRPin, INPUT); //actually this will work and without it
}

int LDR::readData()
{
    return analogRead(LDRPin);
}

float LDR::ldrToLux(int data)
{
    float resistorVoltage = (float)data / MAX_ADC_READING * ADC_REF_VOLTAGE;
    float ldrVoltage = ADC_REF_VOLTAGE - resistorVoltage;
    float ldrResistance = ldrVoltage/resistorVoltage * REF_RESISTANCE;
    return LUX_CALC_SCALAR * pow(ldrResistance, LUX_CALC_EXPONENT);

    /*Serial.print("ldr data: ");
    Serial.print(ldrLux);
    Serial.print(" lux");
    Serial.println();*/
}