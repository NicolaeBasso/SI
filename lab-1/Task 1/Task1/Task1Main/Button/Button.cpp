#include "Button.h"

Button::Button(int pin)
{
  ButtonPin = pin;
}


void Button::initL()
{
  pinMode(ButtonPinpin, OUTPUT);
}

bool Button::readButton(){
    if (digitalRead(ButtonPin) == HIGH) return true;
        else return false;
}
