#include <Arduino.h>
#include <Wire.h>
#include "Button.h"

//#define master 0    //master ordinal
//#define slave  1    //slave ordinal

//#define buttonPin 10    // button pin

// uint8_t Buffer[20];
// int buff_it;

// bool buttonWasPressed = false;  //Variable to see if the buton was pressed
// Button button(buttonPin);
// uint8_t time;

// void receiveReponce();

// void setup() {
//     Wire.begin(master);
//     Wire.onReceive(receiveReponce); 
//     Serial.begin(9600);
//     button.init();
// }

// void loop() {

// //Send Request to slave
//     if (button.readButton() && !buttonWasPressed)  
//     {
//         time = millis();
//         Serial.print("Request sent | time: ");
//         Serial.println(time);
//         Wire.beginTransmission(slave);     
//         Wire.write(0x25);              
//         Wire.endTransmission();  
//     }
// //Receive reponce

// }

// void receiveReponce(int howMany)
// {
//     buff_it = 0;

//     while (Wire.available())
//     {
//         Buffer[buff_it++] = Wire.read();
//     }

//     int distance = Buffer[0];
//     distance += (int)Buffer[1] << 8;

//     time = millis();
//     Serial.print("Answer received and read | time: ");
//     Serial.println(time);
//     float distanceFloat = distance/10;
//     Serial.print("\n\nDistance is "); 
//     Serial.print(distanceFloat);
//     Serial.println(" cm"); 
// }



const int buttonPin = 9;    //pin for button
const int ledPin = 13;      //pin for LED 


LED led(ledPin);
Button button(buttonPin);

void setup() {
  led.initL();
  button.initL();
  }

void loop(){
  //led.turnOn();

    if (button.readButton()) { //if button is pressed, than LED turns on
        led.turnOn();
    }
    else {                     //else turns off
        led.turnOff();
    }

}
