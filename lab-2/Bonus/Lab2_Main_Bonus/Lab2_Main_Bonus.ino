#include "Button.h"
#include "LED.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x20, 16, 2); //for proteus
LiquidCrystal_I2C lcd(0x27, 16, 2); //for real arduino


const int buttonPin1 = 2;        //pin for first button
const int buttonPin2 = 3;        //pin for second button
const int RedledPin = 13;        //pin for first LED 
const int GreenledPin = 12;      //pin for secondLED 


LED RedLed(RedledPin);
LED GreenLed(GreenledPin);

Button button1(buttonPin1);
Button button2(buttonPin2);

bool LedState = true;
/*bool btn1State = true;
bool btn2State = true;*/

int counter = 0;

long Timer = 0;

String text = "Red  ";

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
    

  attachInterrupt(digitalPinToInterrupt(buttonPin1), firstTask, /*CHANGE*/ LOW);
  attachInterrupt(digitalPinToInterrupt(buttonPin2), thirdTask, CHANGE);

  
  RedLed.turnOn();
  ledIndicator(text); 
  counterIndicator();
}

void loop() {

  if (millis() - Timer >= 1000) {
    Timer = millis();
    int i = Timer/1000;
    timeCounterIndicator(i);
  }

  ledIndicator(text);
  counterIndicator();
}

void firstTask(){
  //1st task
  //if(btn1State){
        if(LedState)
        {
            GreenLed.turnOff();
            RedLed.turnOn();
            LedState = false;
            text = "Red  "; 
        }
        else
        {
            RedLed.turnOff();
            GreenLed.turnOn();
            LedState = true;
            text = "Green";
        }
//        btn1State = !btn1State;
//}
}


void thirdTask(){
  //3rd task
  //Counter increments only if green led is on (or red is off)
  //if(btn2State){
      if(LedState)
        counter++;
  //    btn2State = !btn2State;
  //}    
}

void timeCounterIndicator(int number){
  //time indicator
    lcd.setCursor(0,0); 
    lcd.print("Time(s):");
    lcd.setCursor(9,0); 
    lcd.print(number);
}

void ledIndicator(String text){
  //Led states
    lcd.setCursor(0,1); 
    lcd.print(text);
}

void counterIndicator(){ 
  //counter value
    lcd.setCursor(11,1); 
    lcd.print(counter);
}
