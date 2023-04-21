#include <Arduino.h>

#define MAX_MOTOR_SPEED 256
#define BLUETOOTH_DATA_DELIMITER '#'
#define BLUETOOTH_BAUD_RATE 9600
#define MOTOR_PIN1 9
#define MOTOR_PIN2 10


String readBluetoothData();
float parseDutyCycleData(String dutyCycleData);
float getWateringRate(float dutyCycle);
void clearBuffer();

String buffer = "";

void setup(){
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  Serial.begin(BLUETOOTH_BAUD_RATE);
}

void loop(){
  float pwm, dutyCycle;
  String recievedData = readBluetoothData();
  if (recievedData != ""){
    buffer += recievedData;
    if(recievedData.indexOf(BLUETOOTH_DATA_DELIMITER) != -1){
      dutyCycle = parseDutyCycleData(buffer);
      pwm = getWateringRate(dutyCycle);
      Serial.println(pwm);
      digitalWrite(MOTOR_PIN1, LOW);
      analogWrite(MOTOR_PIN2, pwm);
      clearBuffer();
    }
  }
}

float getWateringRate(float dutyCycle){
  float pwm = (dutyCycle / 100) * MAX_MOTOR_SPEED;
  return pwm;
}

float parseDutyCycleData(String dutyCycleData){
  dutyCycleData = dutyCycleData.substring(0, dutyCycleData.length() - 1);
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
