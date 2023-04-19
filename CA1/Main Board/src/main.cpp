#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void handleRequest();
void runLogic();
void updateLCD();
void sendData();

float temperature, humidity, dutyCycle = 0;
String buffer = "";

void setup()
{
  Serial.begin(9600);
  lcd.begin(20, 4);
}

void loop()
{
  // if (Serial.available() == 5)
  // {
  //   handleRequest();
  //   runLogic();
  //   updateLCD();
  //   sendData();
  // }

  // Serial.println("hiiiii");
  // lcd.println("jjjjjj");

  float rate = 0;
  Serial.println(rate);
  delay(1000);

  // put your main code here, to run repeatedly:
}

void handleRequest()
{
  char request = Serial.read();
  if (request == 'T')
  {
    temperature = Serial.parseFloat();
    request = Serial.read();
    humidity = Serial.parseFloat();
  }
}

void runLogic()
{
  if (humidity > 30)
    dutyCycle = 0;
  else if (humidity > 20)
  {
    if (temperature < 25)
      dutyCycle = 0;
    else
      dutyCycle = 10;
  }
  else if (humidity > 10)
    dutyCycle = 20;
  else
    dutyCycle = 25;
}

void updateLCD()
{
  lcd.clear();
  lcd.setCursor(0, 0);

  if (dutyCycle == 10)
    lcd.println("Water: 10 cc/min");
  else if (dutyCycle == 20)
    lcd.println("Water: 15 cc/min");
  else if (dutyCycle == 25)
    lcd.println("Water: 20 cc/min");
  else
    lcd.println("Water: 0 cc/min");

  lcd.setCursor(0, 1);
  lcd.print("Duty Cycle: ");
  lcd.println(dutyCycle);
}

void sendData()
{
  Serial.println(dutyCycle);
}