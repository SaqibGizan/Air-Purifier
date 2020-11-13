#include<Arduino.h>
#include "fanControll.h"

Controll :: Controll(uint8_t Pin, uint8_t Volt)
{
  fanPin = Pin;
  volt = Volt;
}

Controll :: Controll(uint8_t Pin)
{
  fanPin = Pin;
  volt = 12;
}

void Controll :: begin()
{
  pinMode(fanPin, OUTPUT);
}

void Controll :: on()
{
  if(volt > 5)
    digitalWrite(fanPin, HIGH);
  else
    analogWrite(fanPin, 205);
}

void Controll :: highSpd()
{
  if(volt > 5)
    digitalWrite(fanPin, HIGH);
  else
    analogWrite(fanPin, 205);
}

void Controll :: midSpd()
{
  if(volt > 5)
    analogWrite(fanPin, 220);
  else
    analogWrite(fanPin, 180);
}


void Controll :: lowSpd()
{
  if(volt > 5)
    analogWrite(fanPin, 100);
  else
    analogWrite(fanPin, 80);
}

void Controll :: off()
{
  digitalWrite(fanPin, LOW);
}
