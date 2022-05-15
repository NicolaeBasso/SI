#ifndef Connection_h
#define Connection_h

#include <Arduino.h>
#include <Wire.h>
#include <Message.h>

#define LIGHT "LIGHT"
#define LIGHT_OK "LIGHT_OK"
#define GET "GET"
#define DATA "DATA"

#define EMPTY "empty"

class Connection
{
private:
    boolean isMaster;
    int from;
    int to;
    int idCounter = 0;

    

public:

    void receiveEvent(int howMany){};
    void repsonseEvent(){};
    
    int messageI = 0;

    String lastMessage[6];
    Message message;

    Connection(boolean CisMaster, int CFrom = -1, int CTo = -1)
    {

        if (CisMaster && CTo == -1)
        {
            Serial.println("Unable to create master without slave address");
            this->~Connection();
            return;
        }

        if (!CisMaster && CFrom == -1)
        {
            Serial.println("Unable to create slave without slave address");
            this->~Connection();
            return;
        }

        isMaster = CisMaster;
        from = CFrom;
        to = CTo;

        message.setTo(String(to));

        message.setFrom(String(from));

        if (isMaster)
        {
            Wire.begin();
        }
        else
        {
            idCounter = 1;
            Wire.begin(from);
            Wire.onReceive(receiveEvent);
            Wire.onRequest(repsonseEvent);
        }
    };

    void sendMessage(String MType, String Mpayload = EMPTY)
    {
        if (!isMaster)
        {
            Serial.println("Cannot send message from slave directrly");
            return;
        }

        message.setId(idCounter);
        idCounter += 2;

        message.setType(MType);

        message.setPayload(Mpayload);

        transmit("MessageStart");
        transmit(message.getId());
        transmit(message.getFrom());
        transmit(message.getTo());
        transmit(message.getType());
        transmit(message.getPayload());
        transmit(message.getSum());
        transmit("MessageEnd");

        delay(100);

        messageI = 0;

        String Mrequest = "";

        while (Mrequest != "MessageEnd")
        {

            Mrequest = request();

            if (Mrequest != "MessageStart" && Mrequest != "MessageEnd")
            {
                lastMessage[messageI] = Mrequest.substring(Mrequest.indexOf(':') + 1);
                messageI++;
            }

            Serial.println(Mrequest + '\n');
        }

        if (lastMessage[3] == DATA)
        {
            Serial.println("Distance: " + lastMessage[4] + "cm");
        }

        if (lastMessage[3] == LIGHT_OK)
        {
            Serial.println("LED was triggered!");
        }

        // Serial.println("RESPONSE RECEIVED");
    };

    String request()
    {
        Wire.requestFrom(to, 32);

        String response;

        while (Wire.available())
        {
            response += (char)Wire.read();
        }

        response = response.substring(0, response.indexOf('\n'));

        // Serial.println(response+'\n');

        return response;
    };

    void transmit(String part)
    {

        // Serial.println(part);

        Wire.beginTransmission(to);
        Wire.write(part.c_str());
        Wire.endTransmission();
    };

    int getFromId()
    {
        return from;
    };

    int getToId()
    {
        return to;
    };
};


#endif