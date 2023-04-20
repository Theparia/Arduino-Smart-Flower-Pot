#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define BLUETOOTH_DELIMETER_CHARACTER '-'
#define BLUETOOTH_END_CHARACTER '/'

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String readBluetoothData();
void showOnLcd(float temperature, float humidity, float dutyCycle);
void splitSensorData(String humidity_temp_data);
float getDutyCycle();
void sendData(float dutyCycle);
void clearBuffer();



float temperature, humidity;
String buffer = "";


void setup(){
  Serial.begin(9600);
  lcd.begin(20, 4);
}

void loop(){
  // put your main code here, to run repeatedly:
  String data = readBluetoothData();
  if (data != ""){
    buffer += data;
    if(data.indexOf(BLUETOOTH_END_CHARACTER) != -1){
      splitSensorData(buffer);
      float dutyCycle = getDutyCycle();
      showOnLcd(humidity, temperature, dutyCycle);
      sendData(dutyCycle);
      clearBuffer();
    }
  }
}

void showOnLcd(float humidity, float temperature, float dutyCycle){ //TODO: LCD <4 x 20> on Proteus
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("H:  " + String(humidity));
  lcd.setCursor(0, 1);
  lcd.print("T:  " + String(temperature));
  lcd.setCursor(-4, 2);
  lcd.print("DC: " + String(dutyCycle));
}

void splitSensorData(String humidityTemperatureData){
  int delimeter_index = humidityTemperatureData.indexOf(BLUETOOTH_DELIMETER_CHARACTER);
  String humidityStr = humidityTemperatureData.substring(0, delimeter_index);
  String temperatureStr = humidityTemperatureData.substring(delimeter_index + 1, humidityTemperatureData.length() - 1);
  humidity = atof(&humidityStr[0]);
  temperature = atof(&temperatureStr[0]);
}

String readBluetoothData(){
  String data = Serial.readString();
  return data;
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
	String message = String(dutyCycle) + BLUETOOTH_END_CHARACTER;
  Serial.println(&message[0]);
}
