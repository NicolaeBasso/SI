#include "Button.h"

Button::Button(int pin)
{
  ButtonPin = pin;
}


void Button::initB()
{
  pinMode(ButtonPin, INPUT_PULLUP);
}

bool Button::readButton(){
    if (digitalRead(ButtonPin) == LOW) return true;
        else return false;
}
