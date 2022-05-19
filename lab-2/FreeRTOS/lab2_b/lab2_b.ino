#include <Arduino_FreeRTOS.h>
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
  // put your setup code here, to run once:
Serial.begin(9600);

xTaskCreate(firstTask,"Task1",128,NULL,1,NULL);
xTaskCreate(secondTask,"Task2 ",128,NULL,1,NULL);
xTaskCreate(thirdTask,"Task3",128,NULL,1,NULL);
xTaskCreate(fourthTask,"Task4",128,NULL,1,NULL);   
vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void firstTask(void *pvParameters ){
  //1st task
while(1){  
  Serial.println("First Task");
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
}

void secondTask(void *pvParameters ){
  //2nd task
while(1){   
  Serial.println("Second Task");
    if(LedState)
    {
        GreenLed.turnOn();    
    }
    else
    {
      GreenLed.turnOff();
    }
}
}

void thirdTask(void *pvParameters ){
  //3rd task
while(1){ 
  Serial.println("Third Task");
  bool btn2State1 = button2.readButton();
  //Counter increments only if green led is on (or red is off)
    if(LedState && btn2State1 && !btn2State2)
    {
        counter++;
    }

  btn2State2 = btn2State1;
}
}

void fourthTask(void *pvParameters ){
while(1){ 
  Serial.println("Fourth Task");
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
    lcd.print(" Counter:");
    lcd.setCursor(11,1); 
    lcd.print(counter);
}
}
