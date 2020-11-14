#include "dustSensor.h"

#define DustLed_pin 4
#define DustOut_pin A7
dustSensor dust(DustLed_pin, DustOut_pin);

void setup()
{
  Serial.begin(115200);
  dust.begin();
}

void loop()
{
  Serial.println(dust.dustLvl());
  Serial.println(dust.airHealth());
}
