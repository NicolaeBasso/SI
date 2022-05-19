#ifndef Button_h
#define Button_h

#include <Arduino.h>

class Button
{
  public:
    Button(int pin);
    void initB();
    bool readButton();
  private:
    int ButtonPin;
};

#endif
