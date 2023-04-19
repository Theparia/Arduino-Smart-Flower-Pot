#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(20, 4);
}

void loop()
{
  // Serial.println("hiiiii");
  // lcd.println("jjjjjj");

  float rate = 10;
  Serial.println(rate);
  delay(1000);

  // put your main code here, to run repeatedly:
}