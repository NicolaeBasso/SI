#ifndef SerialIO_h
#define SerialIO_h
#include <stdio.h>
#include <Arduino.h>

class SerialIO
{
    public:
        SerialIO();
        String readIn();
        bool check(String input, String pattern);
};

#endif
