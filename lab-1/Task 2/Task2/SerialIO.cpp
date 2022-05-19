#include "SerialIO.h"

SerialIO::SerialIO(){
}

String SerialIO::readIn(){
    String input = "";
    if (Serial.available() > 0) {
        input = Serial.readStringUntil('\n');

        Serial.print("Received: ");
        Serial.println(input);
   }
   return input;
}

bool SerialIO::check(String input, String pattern){
    if(input == pattern) return true;
        else return false;
}
