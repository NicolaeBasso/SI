#include "LED.h"

LED::LED(int pin)
{
  LEDpin = pin;
}

void LED::initL()
{
  pinMode(LEDpin, OUTPUT);
}

void LED::turnOn(){
    digitalWrite(LEDpin, HIGH);
}

void LED::turnOff(){
    digitalWrite(LEDpin, LOW);
}
