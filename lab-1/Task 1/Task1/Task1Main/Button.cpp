#include "Button.h"

Button::Button(int pin)
{
  ButtonPin = pin;
}


void Button::init()
{
  pinMode(ButtonPin, INPUT);
}

bool Button::readButton(){
    if (digitalRead(ButtonPin) == HIGH) return true;
        else return false;
}
