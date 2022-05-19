#ifndef MessageIO_h
#define MessageIO_h
#include <stdio.h>
//#include <cstring>
#include <Arduino.h>

class MessageIO
{
    private:
        char charMotor[5];
    public:
        MessageIO();
        String readIn();
        bool check(String input, String pattern);
        bool motor(String motor);

};

#endif
