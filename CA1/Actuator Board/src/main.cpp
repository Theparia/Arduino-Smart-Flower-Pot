#include <Arduino.h>

float wateringRate = 0;

void handleRequest();

void setup()
{
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  // if (Serial.available() == 5)
  // {
  //   handleRequest();
  //   Serial.println(wateringRate);
  // }

  analogWrite(9, HIGH);
  analogWrite(8, LOW);
}

void handleRequest()
{
  char request = Serial.read();
  if (request == 'Y')
    wateringRate = Serial.parseFloat();
  else if (request == 'N')
    wateringRate = 0;
}