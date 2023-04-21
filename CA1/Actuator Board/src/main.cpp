#include <Arduino.h>

#define MAX_MOTOR_SPEED 256
#define BLUETOOTH_DATA_DELIMITER '#'

String readBluetoothData();
float parseDutyCycleData(String dutyCycleData);
float getWateringRate(float dutyCycle);
void clearBuffer();

String buffer = "";
float wateringRate = 0;

void setup(){
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  float wateringRate, dutyCycle;
  String recievedData = readBluetoothData();
  if (recievedData != ""){
    buffer += recievedData;
    if(recievedData.indexOf(BLUETOOTH_DATA_DELIMITER) != -1){
      dutyCycle = parseDutyCycleData(buffer);
      wateringRate = getWateringRate(dutyCycle);
      Serial.println(wateringRate);
      analogWrite(11, wateringRate);
      clearBuffer();
    }
  }
}

float getWateringRate(float dutyCycle){
  float wateringRate = (dutyCycle * 0.01) * MAX_MOTOR_SPEED;
  return wateringRate;
}

float parseDutyCycleData(String dutyCycleData){
  dutyCycleData = dutyCycleData.substring(0, dutyCycleData.length() - 2);
  float dutyCycle = atof(&dutyCycleData[0]);
  return dutyCycle;
}

String readBluetoothData(){
  String data = Serial.readString();
  return data;
}

void clearBuffer(){
  buffer = "";
}
