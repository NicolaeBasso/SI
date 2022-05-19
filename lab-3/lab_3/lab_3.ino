#include <Arduino.h>
#include "Ultrasonic.h"
#include "LDR.h"
#include "LM35.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 4); //for proteus
//LiquidCrystal_I2C lcd(0x27, 16, 2); //for real arduino

#define LDRpin A1         //Pin for LDR
#define TempAnalogPin A2  //Pin for LM35
#define pingPin 7         // Trigger Pin of Ultrasonic Sensor
#define echoPin 6         // Echo Pin of Ultrasonic Sensor
#define DHTTYPE DHT11

int ldrData[5];
float ldrFilteredValue;

int lmData[5];
float lmFilteredValue;

float ultrasonicData[5];
float ultrasonicFiltredValue;
 
byte counter = 0;
bool filter = true; //true - MWA, false - Salt and pepper( if I'll finish it)
float SMAldr = 0.0;
float SMAulson = 0.0;
float SMAlm = 0.0;

Ultrasonic ultrasonic(echoPin, pingPin);
LDR ldr(LDRpin);
LM35 lm(TempAnalogPin);


void setup() {
    Serial.begin(9600); // Starting Serial Terminal
    ultrasonic.initSensor();
    ldr.initSensor();
}

void loop() {
        
    for(counter = 0; counter < 5; counter++)
    {    
        ldrData[counter] = ldr.readData();
        ultrasonicData[counter] = ultrasonic.readData();
        lmData[counter] = lm.readData();
    }

    if (filter)
    {
        ldrFilteredValue = WMA(ldrData);
        ultrasonicFiltredValue = WMA(ultrasonicData);
        lmFilteredValue = WMA(lmData);
    }
    else
    {
        ldrFilteredValue = EMA(ldrData, SMAldr);
        ultrasonicFiltredValue = EMA(ultrasonicData, SMAulson);
        lmFilteredValue = EMA(lmData, SMAlm);


        SMAldr = SMA(ldrData);
        SMAulson = SMA(ultrasonicData);
        SMAlm = SMA(lmData);
    }

        printToDisplay();
    }

    //printToDisplay();
    


void moveDatas()
{
    for(int i = 0; i < 5; i++)
    {
        ldrData[i] = ldrData[i+1];
        ultrasonicData[i] = ultrasonicData[i+1];
    }
}

void ultrasonicToSerial()
{
    long distance = ultrasonic.readData();

    Serial.print(distance);
    Serial.print("cm");
    Serial.println();
}

void LDRToSerial()
{
    int data = abs(ldr.readData()-1023); //my own sensor send 0 when light is max, and 1023 when is totaly dark, so I need this string to correct translation from ADC to lux
    Serial.print("ldr voltage: ");
    Serial.print(data);
    Serial.println();
    float smt = ldr.ldrToLux(data);
}

void printToDisplay()
{
  //LDR filtered value
    lcd.setCursor(0,0); 
    lcd.print("LDR: ");
    lcd.setCursor(6,0); 
    lcd.print(ldrFilteredValue);

  //LM filtered value
    lcd.setCursor(0,1); 
    lcd.print("LM: ");
    lcd.setCursor(6,0); 
    lcd.print(lmFilteredValue);

    //LM filtered value
    lcd.setCursor(0,2); 
    lcd.print("Ultra: ");
    lcd.setCursor(6,0); 
    lcd.print(ultrasonicFiltredValue);

  
}

float WMA(float someData[5])
{
  int n = 5;
  /*return  (someData[0] * timePeriod + someData[1] * (timePeriod - timeSplit) + someData[2] * (timePeriod - 2 * timeSplit) + 
                    someData[3] * (timePeriod - 3 * timeSplit) + someData[4] * (timePeriod - 4 *timeSplit)) / 
                                  (timePeriod * (timePeriod - timeSplit) / (2 * timeSplit) );*/

    return (someData[0] * n + someData[1] * (n - 1) + someData[2] * (n - 2) + someData[3] * (n - 3) + someData[4])/( n * (n + 1) / 2);                              
}

float EMA(float someData[5], float smaOfData)
{
    return ((smaOfData * 2/3) + (SMA(someData) * 1 / 3));
}


float SMA(float someData[5])
{
  float sum = 0.0;
  for(int i = 0; i < 5; i++)
  {
    sum += someData[i];
  }

  return sum / 5;
}


