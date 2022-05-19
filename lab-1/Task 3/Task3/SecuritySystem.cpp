#include "SecuritySystem.h"
//#include "LED.cpp"

LiquidCrystal_I2C lcd(0x27,20,4);

const byte ROWS = 4; 
const byte COLS = 4; 
const byte RedLED = 13;
const byte GreenLED = 12;

char hexaKeys[ROWS][COLS] =
{
  {'1','2','3','a'},
  {'4','5','6','b'},
  {'7','8','9','c'},
  {'*','0','#','d'}
};
byte rowPins[ROWS] = {4,5,6,7}; 
byte colPins[COLS] = {/*0,1,2,3*/3,2,1,0}; 
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

char input[4] = {' ', ' ', ' ', ' '};
char password[4] = {'1', '3', '3', '7'};

/*LED RedLed(RedLED);
LED GreenLed(GreenLED);*/

SecuritySystem::SecuritySystem(){
}

void SecuritySystem::initSetup(){
    pinMode(RedLED, OUTPUT);
    pinMode(GreenLED, OUTPUT);
    lcd.init();
    lcd.backlight();
    
}

void SecuritySystem::initLoop(){
    clearDisplay();
    lcd.setCursor(0,0);  
    lcd.print("Input password    ");
    
    
    getInput();

    if(checkFeature())
    {                           //if true -> change password 
        changePassword();
    } 
    else                        //if false -> check password
    {                     
        if (checkPassword())
        {
            correct();
        }
        else
        {
            invalide();
        }
    }
}



void SecuritySystem::getInput(){
    byte q = 0;

    while(q < 4){
        
        input[q] = customKeypad.getKey();
        if (input[q] != NULL)
        {
            lcd.setCursor(q,1);  
            lcd.print(input[q]);
            q++;
        }
    }
}

bool SecuritySystem::checkFeature(){

    if (input[0] == '#' && input[1] == '#' && input[2] == '#' && input[3] == '#'){ //#### - special code for password changing
        return true;
        //changePassword();
    }
    else return false;
    
}

void SecuritySystem::changePassword(){
    clearDisplay();                 
    lcd.setCursor(0,0);  
    lcd.print("Old Password:");
    //To setup new password we need to introduce old one
    getInput();

    if(checkPassword())
    {
        setPassword();
    }
    else 
    {
        invalide();
    }
}

bool SecuritySystem::checkPassword(){
    lcd.setCursor(0,0);  
    lcd.print("Checking our ");
    lcd.setCursor(0,1);  
    lcd.print("     password");
    delay(300);
    if (input[0] == password[0] && input[1] == password[1] && input[2] == password[2] && input[3] == password[3])
        return true;
    else
        return false;
    
}

void SecuritySystem::setPassword(){
    clearDisplay();
    lcd.setCursor(0,0);  
    lcd.print("New Password:    ");
    getInput();
    password[0] = input[0];
    password[1] = input[1];
    password[2] = input[2];
    password[3] = input[3];
    lcd.setCursor(0,0);  
    lcd.print("New password      ");
    lcd.setCursor(0,1); 
    lcd.print("   setuped   ");
    delay(1000);
}

void SecuritySystem::correct(){
    lcd.setCursor(0,0);  
    lcd.print("Password          ");
    lcd.setCursor(0,1);  
    lcd.print("accepted           ");
    digitalWrite(GreenLED, HIGH);
    delay(5000);
    digitalWrite(GreenLED, LOW);
    //opening();    
}

void SecuritySystem::invalide()
{
    lcd.setCursor(0,0);  
    lcd.print("Password       ");
    lcd.setCursor(0,1);  
    lcd.print("     invalide");
    digitalWrite(RedLED, HIGH);
    delay(5000);
    digitalWrite(RedLED, LOW);
}

void SecuritySystem::clearDisplay(){
    //clear display
    lcd.setCursor(0,0);  
    lcd.print("                      ");
    lcd.setCursor(0,1);  
    lcd.print("                      ");
    //clear input
    input[0] = ' ';
    input[1] = ' ';
    input[2] = ' ';
    input[3] = ' ';
}
