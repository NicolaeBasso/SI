#ifndef Message_h
#define Message_h

#include <Arduino.h>
#include <Wire.h>

#define LIGHT "LIGHT"
#define LIGHT_OK "LIGHT_OK"
#define GET "GET"
#define DATA "DATA"
#define EMPTY "empty"

class Message
{
private:
    const String messageStart = "MessageStart";
    const String messageEnd = "MessageEnd";

    int id;
    String from;
    String to;
    String mesType;
    String payload;
    int sum;

public:
    ~Message()
    {
        free(this);
    };

    Message(){};

    Message(int idCounter, int Mfrom, int Mto, String MmesType, String Mpayload = EMPTY)
    {

        int slaveId;

        if (Mfrom == -1)
        {
            slaveId = Mto;
            to = String(Mto);
            from = "Master";
        }
        else
        {
            slaveId = Mfrom;
            to = "Master";
            from = String(Mfrom);
        }

        id = idCounter;
        mesType = MmesType;
        payload = Mpayload;

        sum = id + slaveId;
    };

    String getMessageStart()
    {
        return messageStart;
    };

    String getId()
    {
        return "id:" + String(id);
    };

    String getFrom()
    {
        return "from:" + from;
    };

    String getTo()
    {
        return "to:" + to;
    };

    String getType()
    {
        return "type:" + mesType;
    };

    String getPayload()
    {
        return "payload:" + payload;
    };

    String getSum()
    {
        return "sum:" + String(sum);
    };

    String getMessageEnd()
    {
        return messageEnd;
    };

    void setId(int idCounter)
    {
        id = idCounter;
        sum = id + from.toInt() + to.toInt();
    };

    void setFrom(String MFrom)
    {

        if (MFrom == "-1")
            from = "Master";
        else
            from = MFrom;

        sum = id + from.toInt() + to.toInt();
    };

    void setTo(String MTo)
    {
        if (MTo == "-1")
            to = "Master";
        else
            to = MTo;

        sum = id + from.toInt() + to.toInt();
    };

    void setType(String type)
    {
        mesType = type;
    };

    void setPayload(String MPayload)
    {
        payload = MPayload;
    };
};

void (*resetFunc)(void) = 0;

#endif