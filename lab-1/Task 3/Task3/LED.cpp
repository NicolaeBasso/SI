#include "LED.h"

LED::LED(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void LED::turnOn(){
    digitalWrite(_pin, HIGH);
}

void LED::turnOff(){
    digitalWrite(_pin, LOW);
}