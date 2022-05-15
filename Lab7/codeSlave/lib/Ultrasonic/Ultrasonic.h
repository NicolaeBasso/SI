#ifndef Ultrasonic_h
#define Ultrasonic_h

#include <Arduino.h>

class Ultrasonic
{
    public:
        Ultrasonic(int echo, int ping);
        void initSensor();
        long readData();
        

    private:
        int pingPin; // Trigger Pin of Ultrasonic Sensor
        int echoPin; // Echo Pin of Ultrasonic Sensor
        int microsecondsToCentimeters(long microseconds);
};

#endif