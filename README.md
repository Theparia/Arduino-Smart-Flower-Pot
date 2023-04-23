# Arduino-Smart-Flower-Pot

The smart flower pot is an automated system that makes it easy for plant owners to maintain the ideal environment for their plants to grow. The system is made up of three Arduino boards - the sensor board, actuator board, and main board. Each board has a specific function in the system.


[![image](https://www.linkpicture.com/q/Screenshot-4200.png)](https://www.linkpicture.com/view.php?img=LPic64452339929ce2003829647)

## Sensor Board
The sensor board measures the humidity and temperature conditions of the pot using a humidity sensor and a temperature sensor. The data collected by the sensors is then sent to the main board for processing.

[![image](https://www.linkpicture.com/q/Screenshot-4196.png)](https://www.linkpicture.com/view.php?img=LPic6445259d6cd0e1384690519)

## Main Board
The main board receives the data from the sensor board and determines whether the pot needs to be watered or not. This decision is made based on the humidity and temperature levels in the pot. If the humidity is too low and the temperature is too high, the main board will send a command to the actuator board to water the pot.

[![image](https://www.linkpicture.com/q/Screenshot-4197.png)](https://www.linkpicture.com/view.php?img=LPic6445255db94f51184939708)

## Actuator Board
The actuator board receives the command from the main board and controls the water pump to water the plant. The actuator board uses a relay to switch on and off the water pump based on the command received from the main board.

[![image](https://www.linkpicture.com/q/Screenshot-4198.png)](https://www.linkpicture.com/view.php?img=LPic644525d5583821029674507)


Contributors: [Parnian Fazel](https://github.com/parnianf), [Ali Akhgari](https://github.com/AliAkhgari), [Mona Mojtahedi](https://github.com/Monamjh)

