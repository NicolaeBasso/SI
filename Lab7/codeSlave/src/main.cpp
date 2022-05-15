#include <Arduino.h>
#include <Wire.h>
#include <Ultrasonic.h>
#include <Message.h>
#include <LED.h>

#define LIGHT "LIGHT"
#define LIGHT_OK "LIGHT_OK"
#define GET "GET"
#define DATA "DATA"

#define EMPTY "empty"

int idCounter = 0;

void receiveEvent(int howMany);

void repsonseEvent();


class Connection
{
private:
    boolean isMaster;
    int from;
    int to;

public:
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

///////////////////////////////////////////////////////////////

#define echoPin 4
#define trigPin 5

#define ledPin 8

long distance = 0;

const float dDelta = 0.034;

const float dCoef = 2;

int ledState = LOW;

void setLedState()
{
    ledState = !ledState;
}

////////////////////////////////////////////////////////////////////////////

Connection connection(false, 2, -1);
Ultrasonic ultrasonic(echoPin, trigPin);
LED Led(ledPin);

void receiveEvent(int howMany)
{

    // Serial.println("MESSAGE GOT");

    String response;

    String field;

    while (0 < Wire.available())
    {
        response += (char)Wire.read();
    }

    Serial.println(response + '\n');

    if (response != "MessageStart" && response != "MessageEnd")
    {

        field = response.substring(0, response.indexOf(':'));

        response = response.substring(response.indexOf(':') + 1);

        if (field == "id")
        {
            connection.lastMessage[0] = response;
        }

        if (field == "from")
        {
            connection.lastMessage[1] = response;
        }

        if (field == "to")
        {
            connection.lastMessage[2] = response;
        }

        if (field == "type")
        {
            connection.lastMessage[3] = response;
        }

        if (field == "payload")
        {
            connection.lastMessage[4] = response;
        }

        if (field == "sum")
        {
            connection.lastMessage[5] = response;
        }
    }
};

void repsonseEvent()
{

    if (connection.messageI == 0)
    {

        // for (int j = 0; j < 6; j++) {
        //    Serial.println(connection.lastMessage[j]);
        // }

        if (connection.lastMessage[3] == LIGHT)
        {
            setLedState();
            Serial.println("LIGHT TOGGLED");

            connection.message.setId(idCounter);


            connection.message.setType(LIGHT_OK);

            connection.message.setPayload(EMPTY);

            connection.lastMessage[0] = connection.message.getId();

            connection.lastMessage[1] = connection.message.getFrom();

            connection.lastMessage[2] = connection.message.getTo();

            connection.lastMessage[3] = connection.message.getType();

            connection.lastMessage[4] = connection.message.getPayload();

            connection.lastMessage[5] = connection.message.getSum();
        }

        if (connection.lastMessage[3] == GET)
        {
            distance = ultrasonic.readData();
            Serial.println("DISTANCE GOT");

            connection.message.setId(idCounter);
            idCounter += 2;

            connection.message.setType(DATA);

            connection.message.setPayload(String(distance));

            connection.lastMessage[0] = connection.message.getId();

            connection.lastMessage[1] = connection.message.getFrom();

            connection.lastMessage[2] = connection.message.getTo();

            connection.lastMessage[3] = connection.message.getType();

            connection.lastMessage[4] = connection.message.getPayload();

            connection.lastMessage[5] = connection.message.getSum();
        }

        Wire.write("MessageStart\n");
    }

    if (connection.messageI == 1)
        Wire.write(((connection.lastMessage[0] + '\n').c_str()));

    if (connection.messageI == 2)
        Wire.write(((connection.lastMessage[1] + '\n').c_str()));

    if (connection.messageI == 3)
        Wire.write(((connection.lastMessage[2] + '\n').c_str()));

    if (connection.messageI == 4)
        Wire.write(((connection.lastMessage[3] + '\n').c_str()));

    if (connection.messageI == 5)
        Wire.write(((connection.lastMessage[4] + '\n').c_str()));

    if (connection.messageI == 6)
        Wire.write(((connection.lastMessage[5] + '\n').c_str()));

    if (connection.messageI == 7)
    {
        Wire.write("MessageEnd\n");
        connection.messageI = -1;
    }

    connection.messageI++;
};




void setup()
{

    Serial.begin(9600);

    ultrasonic.initSensor();

    Led.init();
}

void loop()
{
    if(ledState){
        Led.turnOn();
    } 
    else
    {
        Led.turnOff();
    }
    delay(100);
}