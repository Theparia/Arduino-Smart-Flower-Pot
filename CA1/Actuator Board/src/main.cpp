#include <Arduino.h>

#define MAX_MOTOR_SPEED 256

float wateringRate = 0;

void setup()
{
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  wateringRate = (Serial.parseFloat() / 100) * MAX_MOTOR_SPEED;
  Serial.println(wateringRate);
  digitalWrite(9, wateringRate);
  digitalWrite(8, LOW);
}
