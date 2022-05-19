#include <Arduino.h>
#include "Relay.h"
#include "MotorDriver298.h"
#include "MessageIO.h"


#define relayPin 10
#define motorPin1 7
#define motorPin2 6
#define motorPin3 5

const char delimiter = ' ';

Relay relay(relayPin);
MessageIO messageIO;
MotorDriver298 MotorDriver(motorPin1, motorPin2, motorPin3);

String strs[2];

String messages[10] = {
  //"motor -10"
  "lamp ON", "motor -10", "motor 100", "lamp OFF", "motor 0", "motor 100", "lamp fuf", "motor ajdf", "lamp ON", "lamp OFF"
  };
int i = 0;


void setup() 
{
    Serial.begin(9600);
    relay.init();
    Serial.println("write lamp ON or lamp OFF to turn on(or off) the lamp");
    Serial.println("write motor *number from -100 to 100* to turn on the engine");
}

void loop() 
{
    String message = messages[i]; //messageIO.readIn();

    messageSpliter(message);
    messageHandler();

    i++;
    delay(3000);
}

void messageSpliter(String str)
{
    byte StringCount = 0;
    while (str.length() > 0)
    {
        int index = str.indexOf(delimiter);
        if (index == -1) // No space found
        {
            strs[StringCount++] = str;
            break;
        }
        else
        {
            strs[StringCount++] = str.substring(0, index);
            str = str.substring(index + 1);
        }
    }

  //return strs;
}

void messageHandler()
{
    if (messageIO.check(strs[0],"lamp"))
    {
        if (messageIO.check(strs[1],"ON"))
        {
            relay.relayOn();
            Serial.println("Lamp turned ON");
        }   
        else if (strs[1] == "OFF")
        {
            relay.relayOff();
            Serial.println("Lamp turned OFF");
        } 
    }
    else if (strs[0] == "motor")
    {
        int number = strs[1].toInt();
        /*if (number > 100 || number < -100)
        {
            number =   
        }*/
        MotorDriver.drive(true, number);
        Serial.print("Motor turned on ");
        Serial.print(number);
        Serial.println("%");
    }
}
