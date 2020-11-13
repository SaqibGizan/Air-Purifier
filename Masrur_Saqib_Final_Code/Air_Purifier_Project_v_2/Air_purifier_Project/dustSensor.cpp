#include<Arduino.h>
#include "dustSensor.h"

dustSensor :: dustSensor(uint8_t ledPin, uint8_t voPin)
{
  LEDPin = ledPin;
  VoPin = voPin;
}

void dustSensor :: begin()
{
  pinMode(LEDPin, OUTPUT);
  pinMode(VoPin, OUTPUT);
}

int dustSensor :: dustRead()
{
  digitalWrite(LEDPin, LOW);
  delayMicroseconds(280);
  int VoRaw = analogRead(VoPin);
  digitalWrite(LEDPin, HIGH);
  delayMicroseconds(9620);
  return VoRaw;
}

float dustSensor :: dustLvl()
{
  float Vo = dustRead();
  for(int i = 0 ; i < sampleRate ; i++)
  {
    VoRawTotal += dustRead();
    VoRawCount++;
  }
  Vo = 1.0 * VoRawTotal / sampleRate;
  VoRawCount = 0;
  VoRawTotal = 0;
  Vo = Vo / 1024.0 * 5.0;
  float dV = Vo - Voc;
  if ( dV < 0 ) {
    dV = 0;
    Voc = Vo;
  }
  dustDensity = dV / K * 100.0;
  return dustDensity;
}

float dustSensor :: avgDensity()
{
  avgDensityTotal += dustLvl();
  averageDensity = avgDensityTotal / 2.0;
  return averageDensity;
}

String dustSensor :: airHealth()
{
  String health;
  if(averageDensity < 10){
   health = "Healthy :)";
  }
  else if(averageDensity < 30){
    health = "Modarate :|";
  }
  else if(averageDensity < 50){
    health = "Sensitive :(";
  }
  else if(averageDensity < 145){
    health = "Unhealthy :'(";
  }
  else if(averageDensity < 245){
    health = "Very Unhealthy"; 
  }
  else{
    health = "Hazardous x_x";
  }
  return health;
}
