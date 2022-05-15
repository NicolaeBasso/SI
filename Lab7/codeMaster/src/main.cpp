#include <Arduino.h>
#include <Wire.h>
#include <Connection.h>
#include <Message.h>

#define LIGHT "LIGHT"
#define LIGHT_OK "LIGHT_OK"
#define GET "GET"
#define DATA "DATA"

#define EMPTY "empty"


Connection connection(true, -1, 2);


void setup()
{
    Serial.begin(9600);

    Serial.println("Input command \"dist\" to receive distance or \"light\" to turn on the LED light");
}

void loop()
{

    if (Serial.available())
    {
        String command = Serial.readStringUntil('\n');
        command.trim();
        if (command.equalsIgnoreCase("dist"))
        {
            connection.sendMessage(GET);
        }
        else if (command.equalsIgnoreCase("light"))
        {
            connection.sendMessage(LIGHT);
        }
        else
        {
            Serial.println("No such command!");
        }
    }
}

