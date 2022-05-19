#include "Relay.h"

Relay::Relay(byte pin)
{
    relayPin = pin;
}

void Relay::init()
{
    pinMode(relayPin, OUTPUT);  
    digitalWrite(relayPin, LOW);  
}

void Relay::relayOn()
{
    digitalWrite(relayPin, HIGH); 
}

void Relay::relayOff()
{
    digitalWrite(relayPin, LOW); 
}
