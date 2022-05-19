#include <Arduino.h>
#include "Relay.h"
#include "MotorDriver298.h"
#include "LM35.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x20, 16, 4); //for proteus

//Setup data
#define startTemperature 10
#define bounds 3
#define PID_DUTY_CYCLE_MIN 0
#define PID_DUTY_CYCLE_MAX 100

float pwmDutyCycle = 500;

float Kp = 300;
float Ki = 10;
float Kd = 900;

float previousError = 0;
float currentError = 0;
float integralError = 0;
float differentialError = 0;

uint32_t timeCounterMs = 0;

float targetTemperature = startTemperature;
int currentTemperature = startTemperature;



//Pins
#define lm35Pin A0      //Pin for LM35
#define varistorPin A2  //Pin for temperature setting
#define relayPin 10     //Pin for Relay-heater
#define motorPin1 7
#define motorPin2 6
#define motorPin3 5

Relay relay(relayPin);
MotorDriver298 MotorDriver(motorPin1, motorPin2, motorPin3);
LM35 lm(lm35Pin);

bool heaterState = false;

void dataOnLCD();

void setup() {
  lcd.init();
  lcd.backlight();

  relay.init();
}

void loop() {

    currentTemperature = lm.readData();
    targetTemperature = analogRead(varistorPin) / 20;

    //a)
    if ((currentTemperature > targetTemperature + bounds) && heaterState)
    {
        relay.relayOff();
        heaterState = false;
    }

    if ((currentTemperature < targetTemperature - bounds) && !heaterState)
    {
        relay.relayOn();
        heaterState = true;
    }

    //b)
    timeCounterMs = millis() - timeCounterMs;

    float timeCounterSec = (float)timeCounterMs / 1000;
    currentError = currentTemperature - targetTemperature;

    if (((((Ki * integralError) <= PID_DUTY_CYCLE_MAX) && currentError >= 0)) || 
        (((Ki * integralError) >= PID_DUTY_CYCLE_MIN) && currentError < 0))
    {
      integralError += currentError * timeCounterSec;
    }

    differentialError = (currentError - previousError) / timeCounterSec;
    pwmDutyCycle = Kp * currentError + Ki * integralError + Kd * differentialError;

    if (pwmDutyCycle < PID_DUTY_CYCLE_MIN)
    {
      pwmDutyCycle = PID_DUTY_CYCLE_MIN;
    }

    if (pwmDutyCycle > PID_DUTY_CYCLE_MAX)
    {
      pwmDutyCycle = PID_DUTY_CYCLE_MAX;
    }
    MotorDriver.drive(true, pwmDutyCycle);

    previousError = currentError;

    
    dataOnLCD();
    
}

void dataOnLCD()
{
    lcd.setCursor(0,0); 
    lcd.print("Target:");
    lcd.setCursor(10,0); 
    lcd.print(targetTemperature);
    lcd.setCursor(14,0); 
    lcd.print("C");

    lcd.setCursor(0,1); 
    lcd.print("Сurrent:");
    lcd.setCursor(10,1); 
    lcd.print(currentTemperature);
    lcd.setCursor(14,1); 
    lcd.print("C");
}
