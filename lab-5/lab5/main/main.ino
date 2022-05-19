#include <Arduino.h>
#include "Relay.h"
#include "MotorDriver298.h"
#include "LM35.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <FreeRTOS.h>

LiquidCrystal_I2C lcd(0x20, 16, 4); //for proteus

//Setup data
#define startTemperature 10
#define bounds 3

int Kp = 50; 
int Ki = 30; 
int Kd = 1200;

int setTemperature = startTemperature;
int currentTemperature = startTemperature;

//Pins
#define lm35Pin A2  //Pin for LM35
#define relayPin 10
#define motorPin1 7
#define motorPin2 6
#define motorPin3 5

Relay relay(relayPin);
MotorDriver298 MotorDriver(motorPin1, motorPin2, motorPin3);
LM35 lm(lm35Pin);

void setup() {
  relay.init();
}

void loop() {
    int Temperature = lm.readData();

}