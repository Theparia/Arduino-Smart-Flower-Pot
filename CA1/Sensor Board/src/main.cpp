#include <Arduino.h>
#include <Wire.h>

#define SHT25_I2C_ADDRESS 0x40
#define CMD_TMP_NOHLD 0xF3
#define CMD_HUM_NOHLD 0xF5
#define BLUETOOTH_DATA_SEPERATOR '/'
#define BLUETOOTH_DATA_DELIMITER '#'
#define INITIAL_HUMIDITY -1
#define BLUETOOTH_BAUD_RATE 9600
#define MINIMUM_HUMIDITY_DIFFERENCE 5


float getHumidity();
float getTemperature();
void sendData(float, float);
bool needToSendSensorData(float lastHumidity, float currentHumidity);


void setup(){
	Wire.begin();
	Serial.begin(BLUETOOTH_BAUD_RATE);
}

void loop(){
	static float lastHumidity = INITIAL_HUMIDITY;
	float currentHumidity = getHumidity();
	float currentTemperature = getTemperature();
	if (needToSendSensorData(lastHumidity, currentHumidity)){
		lastHumidity = currentHumidity;
		sendData(currentHumidity, currentTemperature);
	}
}

bool needToSendSensorData(float lastHumidity, float currentHumidity){
	return fabs(currentHumidity - lastHumidity) > MINIMUM_HUMIDITY_DIFFERENCE || (lastHumidity == INITIAL_HUMIDITY);
}

float getHumidity(){
	unsigned int data[2];
	Wire.beginTransmission(SHT25_I2C_ADDRESS);
	Wire.write(CMD_HUM_NOHLD);
	Wire.endTransmission();
	delay(500);
	Wire.requestFrom(SHT25_I2C_ADDRESS, 2);
	if (Wire.available() == 2){
		data[0] = Wire.read();
		data[1] = Wire.read();
		float humidity = (((data[0] * 256.0 + data[1]) * 125.0) / 65536.0) - 6;
		return humidity;
	}
}

float getTemperature(){
	unsigned int data[2];
	Wire.beginTransmission(SHT25_I2C_ADDRESS);
	Wire.write(CMD_TMP_NOHLD);
	Wire.endTransmission();
	delay(500);
	Wire.requestFrom(SHT25_I2C_ADDRESS, 2);
	if (Wire.available() == 2){
		data[0] = Wire.read();
		data[1] = Wire.read();
		float cTemp = (((data[0] * 256.0 + data[1]) * 175.72) / 65536.0) - 46.85;
		return cTemp;
	}
}

void sendData(float humidity, float temperature){
	String message = String(humidity) + BLUETOOTH_DATA_SEPERATOR + String(temperature) + BLUETOOTH_DATA_DELIMITER;
  	Serial.println(message);
}