#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop()
{
  Serial.print('Y');
  Serial.println(0.25);
  delay(10000);

  // put your main code here, to run repeatedly:
}