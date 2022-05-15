#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int echo, int ping)
{
    echoPin = echo;
    pingPin = ping;
}

void Ultrasonic::initSensor()
{
    pinMode(pingPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

int Ultrasonic::microsecondsToCentimeters(long microseconds) 
{
    //float centimeters = microseconds / 58.2;
    int i = 100 * microseconds / 58.2;
    return i/100;
}

long Ultrasonic::readData()
{
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(pingPin, LOW);
    int i = 100 * microsecondsToCentimeters(pulseIn(echoPin, HIGH));
    return i/100;
}
