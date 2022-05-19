#include <Arduino.h>
#include <Wire.h>

#define LIGHT "LIGHT"
#define LIGHT_OK "LIGHT_OK"
#define GET "GET"
#define DATA "DATA"

#define EMPTY "empty"

int idCount = 0;

void receiveEvent(int howMany);

void repsonseEvent();

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

    Message(int Mfrom, int Mto, String MmesType, String Mpayload = EMPTY)
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

        id = idCount;
        idCount += 2;
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

    void setId()
    {
        id = idCount;

        idCount += 2;

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

///////////////////////////////////////////////////////////////

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
            idCount = 1;
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

        message.setId();

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

Connection connection(true, -1, 2);

void receiveEvent(int howMany){

};

void repsonseEvent(){

};

void setup()
{
    Serial.begin(9600);

    Serial.println("Input command \"dist\" to receive distance or \"light\" to turn on the LED light");
}

void loop()
{

    if (Serial.available())
    {
        String command = Serial.readStringUntil('\n');
        command.trim();
        if (command.equalsIgnoreCase("dist"))
        {
            connection.sendMessage(GET);
        }
        else if (command.equalsIgnoreCase("light"))
        {
            connection.sendMessage(LIGHT);
        }
        else
        {
            Serial.println("No such command!");
        }
    }
}