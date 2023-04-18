#include <Arduino.h>

void setup()
{
  // put your setup code here, to run once:
}

void loop()
{
  // put your main code here, to run repeatedly:
}

void handleRequest()
{
  static float wateringRate = -1;
  char request = Serial.read();
  if (request == 'Y')
    wateringRate = Serial.parseFloat();
  else if (request == 'N')
    wateringRate = -1;
}