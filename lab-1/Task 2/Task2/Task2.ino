#include "LED.h"
#include "SerialIO.h"


const int ledPin = 13;      //pin for LED 
const String patternON = "led on";
const String patternOFF = "led off";

LED led(ledPin);
SerialIO serial;
String input = "";

void setup() {
  Serial.begin(9600);
  led.initL();
}

void loop() {
    input = serial.readIn();

    if (serial.check(input, patternOFF)) {
      Serial.println("Setting LED to OFF");
      led.turnOff();
    }else if (serial.check(input, patternON)) {
      Serial.println("Setting LED to ON");
      led.turnOn();
    }
}
