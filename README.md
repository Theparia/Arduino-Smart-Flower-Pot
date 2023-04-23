# Arduino-Smart-Flower-Pot
***

The smart flower pot is an automated system that makes it easy for plant owners to maintain the ideal environment for their plants to grow. The system is made up of three Arduino boards - the sensor board, actuator board, and main board. Each board has a specific function in the system.

## Sensor Board
The sensor board measures the humidity and temperature conditions of the pot using a humidity sensor and a temperature sensor. The data collected by the sensors is then sent to the main board for processing.

## Main Board
The main board receives the data from the sensor board and determines whether the pot needs to be watered or not. This decision is made based on the humidity and temperature levels in the pot. If the humidity is too low and the temperature is too high, the main board will send a command to the actuator board to water the pot.

## Actuator Board
The actuator board receives the command from the main board and controls the water pump to water the plant. The actuator board uses a relay to switch on and off the water pump based on the command received from the main board.
