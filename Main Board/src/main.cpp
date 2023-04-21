#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define BLUETOOTH_DATA_SEPERATOR '/'
#define BLUETOOTH_DATA_DELIMITER '#'
#define BLUETOOTH_BAUD_RATE 9600
#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2

String readBluetoothData();
void showOnLcd(float temperature, float humidity, float dutyCycle);
void splitSensorData(String HTData);
float getDutyCycle();
float getWateringRate(float dutyCycle);
void sendData(float dutyCycle);
void clearBuffer();

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
float temperature, humidity;
String buffer = "";

void setup(){
  Serial.begin(BLUETOOTH_BAUD_RATE);
  lcd.begin(20, 4);
}

void loop(){
  String recievedData = readBluetoothData();
  if (recievedData != ""){
    buffer += recievedData;
    if(recievedData.indexOf(BLUETOOTH_DATA_SEPERATOR) != -1){
      splitSensorData(buffer);
      float dutyCycle = getDutyCycle();
      showOnLcd(humidity, temperature, dutyCycle);
      sendData(dutyCycle);
      clearBuffer();
    }
  }
}

void showOnLcd(float humidity, float temperature, float dutyCycle){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("H: " + String(humidity) + " %");
  lcd.setCursor(0, 1);
  lcd.print("T: " + String(temperature) + " C");
  lcd.setCursor(-4, 2);
  lcd.print("R: " + String(getWateringRate(dutyCycle)) + " CC/min");
}

float getWateringRate(float dutyCycle){
  if (dutyCycle == 10)
    return 10;
  else if (dutyCycle == 20)
    return 15;
  else if (dutyCycle == 25)
    return 20;
  else
    return 0; 
}

void splitSensorData(String humidityTemperatureData){
  int seperatorIdx = humidityTemperatureData.indexOf(BLUETOOTH_DATA_SEPERATOR);
  String humidityStr = humidityTemperatureData.substring(0, seperatorIdx);
  String temperatureStr = humidityTemperatureData.substring(seperatorIdx + 1, humidityTemperatureData.length() - 1);
  humidity = atof(&humidityStr[0]);
  temperature = atof(&temperatureStr[0]);
}

String readBluetoothData(){
  return Serial.readString();
}

float getDutyCycle(){
  if (humidity > 30)
    return 0;
  else if (humidity > 20){
    if (temperature < 25)
      return 0;
    else
      return 10;
  }
  else if (humidity > 10)
    return 20;
  else
    return 25;
}

void clearBuffer(){
  buffer = "";
}

void sendData(float dutyCycle){
	String message = String(dutyCycle) + BLUETOOTH_DATA_DELIMITER;
  Serial.println(message);
}