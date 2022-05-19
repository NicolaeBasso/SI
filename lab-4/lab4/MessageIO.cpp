#include "MessageIO.h"

MessageIO::MessageIO()
{
}

//String SerialIO::readIn()

String MessageIO::readIn()
{
    String input = "";
    if (Serial.available() > 0) {
        input = Serial.readStringUntil('\n');

        Serial.print("Received: ");
        Serial.println(input);
   }
   return input;
}

bool MessageIO::check(String input, String pattern)
{
    if(input == pattern) return true;
        else return false;
}



