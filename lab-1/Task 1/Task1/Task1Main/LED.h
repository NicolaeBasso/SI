#ifndef LED_h
#define LED_h

#include <Arduino.h>

class LED
{
  public:
    LED(int pin);
    void initL();
    void turnOn();
    void turnOff();
  private:
    int LEDpin;
};

#endif
