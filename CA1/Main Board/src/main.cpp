#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define BLUETOOTH_DELIMETER_CHARACTER '-'
#define BLUETOOTH_END_CHARACTER '/'

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

String readBluetoothData();
void showOnLcd();
void splitData(String humidity_temp_data);


float temperature, humidity, dutyCycle = 0;
String buffer = "";


void setup()
{
  Serial.begin(9600);
  lcd.begin(20, 4);
}

void loop()
{
  // put your main code here, to run repeatedly:
  String data = readBluetoothData();
  if (data != ""){
    buffer += data;
    if(data.indexOf(BLUETOOTH_END_CHARACTER) != -1){
      splitData(buffer);
      showOnLcd();
      buffer = "";
    }
  }
}

void showOnLcd(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T: " + String(temperature));
  lcd.setCursor(0, 1);
  lcd.print("H: " + String(humidity));
}

void splitData(String humidityTemperatureData){
  int delimeter_index = humidityTemperatureData.indexOf(BLUETOOTH_DELIMETER_CHARACTER);
  String humidityStr = humidityTemperatureData.substring(0, delimeter_index);
  String temperatureStr = humidityTemperatureData.substring(delimeter_index + 1, humidityTemperatureData.length() - 1);
  humidity = atoi(&humidityStr[0]);
  temperature = atoi(&temperatureStr[0]);
}

String readBluetoothData(){
  String data = Serial.readString();
  return data;
}
