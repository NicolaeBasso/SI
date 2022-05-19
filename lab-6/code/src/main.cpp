#include <Arduino.h>

// BUTTON/LED

#define LED_PIN 13
#define BUTTON_PIN 12

#define LED_OFF_STATE 0
#define LED_ON_STATE 1

// SEMAFOR

#define NORTH_PIN 11
#define EAST_PIN 10
#define EAST_RED_PIN 4
#define EAST_YELLOW_PIN 3
#define EAST_GREEN_PIN 2
#define NORTH_RED_PIN 8
#define NORTH_YELLOW_PIN 7
#define NORTH_GREEN_PIN 6
#define goN 0
#define waitN 1
#define goE 2
#define waitE 3

// BUTTON/LED

struct State_Button
{
  unsigned long Out;
  unsigned long Time;
  unsigned long Next[2];
};
typedef const struct State_Button STyp_Button;

STyp_Button FSM_Button[2] = {
    {0, 10, {LED_OFF_STATE, LED_ON_STATE}},
    {1, 10, {LED_ON_STATE, LED_OFF_STATE}}};

int FSM_State_Button = LED_OFF_STATE;

int Old_State_Button = FSM_State_Button;

// SEMAFOR

struct State_Sem
{
  unsigned long Out;
  unsigned long Time;
  unsigned long Next[4];
};
typedef const struct State_Sem STyp_Sem;

STyp_Sem FSM_Sem[4] = {
    {0b100001, 3000, {goN, waitN, goN, waitN}},
    {0b100010, 500, {goE, goE, goE, goE}},
    {0b001100, 3000, {goE, goE, waitE, waitE}},
    {0b010100, 500, {goN, goN, goN, goN}}};

int FSM_State_Sem = goN;

int Old_State_Sem = FSM_State_Sem;

int GetInput()
{
  int northButton = digitalRead(NORTH_PIN);
  int eastButton = digitalRead(EAST_PIN);
  if (northButton && eastButton)
    return 0b11;
  else if (northButton)
    return 0b10;
  else if (eastButton)
    return 0b01;
  else
    return 0b00;
}

void SetOutput(int out)
{
  int ledState;
  ledState = (out & (1 << 5)) ? HIGH : LOW;
  digitalWrite(EAST_RED_PIN, ledState);
  ledState = (out & (1 << 4)) ? HIGH : LOW;
  digitalWrite(EAST_YELLOW_PIN, ledState);
  ledState = (out & (1 << 3)) ? HIGH : LOW;
  digitalWrite(EAST_GREEN_PIN, ledState);
  ledState = (out & (1 << 2)) ? HIGH : LOW;
  digitalWrite(NORTH_RED_PIN, ledState);
  ledState = (out & (1 << 1)) ? HIGH : LOW;
  digitalWrite(NORTH_YELLOW_PIN, ledState);
  ledState = (out & (1 << 0)) ? HIGH : LOW;
  digitalWrite(NORTH_GREEN_PIN, ledState);
}

void setup()
{

  Serial.begin(9600);

  pinMode(BUTTON_PIN, INPUT);

  pinMode(LED_PIN, OUTPUT);


  pinMode(NORTH_PIN, INPUT);
  pinMode(EAST_PIN, INPUT);

  pinMode(EAST_RED_PIN, OUTPUT);
  pinMode(EAST_YELLOW_PIN, OUTPUT);
  pinMode(EAST_GREEN_PIN, OUTPUT);
  pinMode(NORTH_RED_PIN, OUTPUT);
  pinMode(NORTH_YELLOW_PIN, OUTPUT);
  pinMode(NORTH_GREEN_PIN, OUTPUT);
}

void loop()
{

  //BUTTON/LED

  int output = FSM_Button[FSM_State_Button].Out;
  digitalWrite(LED_PIN, output);

  delay(FSM_Button[FSM_State_Button].Time * 10);

  int input = digitalRead(BUTTON_PIN);

  Old_State_Button = FSM_State_Button;

  FSM_State_Button = FSM_Button[FSM_State_Button].Next[input];

  String stringState_Button;

  if (FSM_State_Button)
    stringState_Button = "ON";
  else
    stringState_Button = "OFF";

  if (Old_State_Button != FSM_State_Button)
    Serial.println("Button state was changed to " + stringState_Button);

  //SEMAFOR

  output = FSM_Sem[FSM_State_Sem].Out;

  SetOutput(output);

  if (Old_State_Sem != FSM_State_Sem)
    delay(FSM_Sem[FSM_State_Sem].Time);

  input = GetInput();

  Old_State_Sem = FSM_State_Sem;

  FSM_State_Sem = FSM_Sem[FSM_State_Sem].Next[input];

  String stringState_Sem;

  if (FSM_State_Sem == goN)
    stringState_Sem = "GoNorth";
  else if (FSM_State_Sem == waitN)
    stringState_Sem = "WaitNorth";
  else if (FSM_State_Sem == goE)
    stringState_Sem = "GoEast";
  else if (FSM_State_Sem == waitE)
    stringState_Sem = "WaitEast";    

  if (Old_State_Sem != FSM_State_Sem)
    Serial.println("Semafor state was changed to " + stringState_Sem);
}