#ifndef LED_h
#define LED_h

#include <Arduino.h>
#include <Keypad.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <stdio.h>
#include "LED.h"

class SecuritySystem
{
  public:
    SecuritySystem();
    void initSetup();
    void initLoop();
    
  private:
    void clearDisplay();
    void correct();
    void invalide();
    void getInput();
    bool checkFeature();
    void changePassword();
    void inputPassword();
    bool checkPassword();
    void clearInput();
    void setPassword();
};

#endif
