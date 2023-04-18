#include <Arduino.h>
#include <Wire.h>

#define SHT25_I2C_ADDRESS 0x40
#define CMD_TMP_NOHLD 0xF3
#define CMD_HUM_NOHLD 0xF5

float getHumidity();
float getTemperature();
void sendData(float, float);

void setup() {
  // Initialise I2C communication as MASTER
	Wire.begin();
	// Initialise UART serial communication, set baud rate = 9600
	Serial.begin(9600);
}

void loop() {
  static float lastHumidity = -1;

  float currentHumidity = getHumidity();
  float currentTemperature = getTemperature();

  if ((currentHumidity > 1.05 * lastHumidity) || (currentHumidity < 0.95 * lastHumidity)){
    sendData(currentHumidity, currentTemperature);
    lastHumidity = currentHumidity;
  }
}

float getHumidity(){
  unsigned int data[2];  
	// Start I2C transmission  
	Wire.beginTransmission(SHT25_I2C_ADDRESS);  
	// Send humidity measurement command, NO HOLD master  
	Wire.write(CMD_HUM_NOHLD);  
	// Stop I2C transmission  
	Wire.endTransmission();  
	delay(500);
	// Request 2 bytes of data  
	Wire.requestFrom(SHT25_I2C_ADDRESS, 2);
	// Read 2 bytes of data  
	// humidity msb, humidity lsb
	if(Wire.available() == 2)
	{
		data[0] = Wire.read();  
		data[1] = Wire.read();
		// Convert the data    
		float humidity = (((data[0] * 256.0 + data[1]) * 125.0) / 65536.0) - 6;
		// Output data to Serial Monitor
		return humidity;
	}
}

float getTemperature(){
  unsigned int data[2];
	// Start I2C transmission  
	Wire.beginTransmission(SHT25_I2C_ADDRESS);  
	// Send temperature measurement command, NO HOLD master  
	Wire.write(CMD_TMP_NOHLD);  
	// Stop I2C transmission  
	Wire.endTransmission();  
	delay(500);
	// Request 2 bytes of data  
	Wire.requestFrom(SHT25_I2C_ADDRESS, 2);
	// Read 2 bytes of data  
	// temp msb, temp lsb  
	if(Wire.available() == 2)  
	{    
		data[0] = Wire.read();    
		data[1] = Wire.read();
		// Convert the data    
		float cTemp = (((data[0] * 256.0 + data[1]) * 175.72) / 65536.0) - 46.85;    
		// Output data to Serial Monitor
		return cTemp;
	}  
}

void sendData(float humidity, float temperature){
  Serial.print('H');
	Serial.println(humidity);
	Serial.print('T');
	Serial.println(temperature);
}