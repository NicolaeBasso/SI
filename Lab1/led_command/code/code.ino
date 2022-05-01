#include "global.h"
#include <stdio.h>

static FILE *f;

static int putChar(char c, FILE *stream)
{
    Serial.write(c) ;
    return 0 ;
}

static char getChar(FILE *stream)
{
    char c;
    while(!Serial.available()) {  
       c = Serial.read();
    }
    return c;
}

void setup() {
  Serial.begin(9600) ;
  
  f = fdevopen(putChar, getChar);
  stdout = f;
  stdin = f;

  char c;
  scanf("%c", &c);
  printf("%c %d", c, 20);
}

void loop() {
  
}
