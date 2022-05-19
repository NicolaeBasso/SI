#ifndef Relay_h
#define Relay_h

#include <Arduino.h>

class Relay
{
    private:
        byte relayPin;

    public:
        Relay(byte pin);
        void init();
        void relayOn();
        void relayOff();

};

#endif
