#include "Button.h"
#include "LED.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x20, 16, 2); //for proteus
LiquidCrystal_I2C lcd(0x27, 16, 2); //for real arduino


const int buttonPin1 = 3;        //pin for first button
const int buttonPin2 = 2;        //pin for second button
const int RedledPin = 13;        //pin for first LED 
const int GreenledPin = 12;      //pin for secondLED 


LED RedLed(RedledPin);
LED GreenLed(GreenledPin);

Button button1(buttonPin1);
Button button2(buttonPin2);

bool LedState = true;
bool btn1State2 = false;
bool btn2State2 = false;

int counter = 0;

void setup() {

//1st task setup
    RedLed.initL();
    button1.initB();

//2nd task void setup
    GreenLed.initL();

//3rd task setup
    button2.initB();
    
//4th task void setup
    lcd.init();
    lcd.backlight();

}

void loop() {
  // 1st task
    firstTask();

  //2nd task
    secondTask();

  //3rd task
    thirdTask();

  //4th task
    fourthTask();
}

void firstTask(){
  //1st task
bool btn1State1 = button1.readButton();

    if (btn1State1 && !btn1State2) {
        if(LedState)
        {
            RedLed.turnOn();
            LedState = false;
        }
        else
        {
            RedLed.turnOff();
            LedState = true;
        }
  }

  btn1State2 = btn1State1;
}

void secondTask(){
  //2nd task
    if(LedState)
    {
        GreenLed.turnOn();    
    }
    else
    {
      GreenLed.turnOff();
    }

}

void thirdTask(){
  //3rd task
  bool btn2State1 = button2.readButton();
  //Counter increments only if green led is on (or red is off)
    if(LedState && btn2State1 && !btn2State2)
    {
        counter++;
    }

  btn2State2 = btn2State1;
}

void fourthTask(){
  //Led states
    lcd.setCursor(0,0); 
    lcd.print("Red:");
    lcd.setCursor(5,0); 
  //if u see 1 on display => led is on
  //if u see 0 on display => led is off
    lcd.print(!LedState); 
    lcd.setCursor(8,0);
    lcd.print("Green:");
    lcd.setCursor(15,0);
    lcd.print(LedState);
  
  //counter value
    lcd.setCursor(0,1); 
    lcd.print("Сounter:");
    lcd.setCursor(11,1); 
    lcd.print(counter);
}
