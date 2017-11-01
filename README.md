# Phonograph Alarm Clock
An Arduino build into a phonograph to wake me up


# Circuit
The circuit consist of an Arduino Uno which is connected to two servos controlling the Arm of the phonograph. It is an old Dual phonograph. 

## Arduino Pins
| Pin | Description         |
|-----|---------------------|
| 9   | Up/Down Servo       |
| 10  | Left/Right Servo    |
| A4  | I2C SDA Clock+Flash |
| A5  | I2C SCL Clock+Flash |

# TODO
- Connect time Module
- Connect ESP8266 and create WIFI control

# Notes
- CPU on Phonograph: [Datasheet](http://datasheetz.com/data/Integrated%20Circuits%20(ICs)/Microcontrollers/D13008F25V-datasheetz.html)
- [AT Commands](https://room-15.github.io/blog/2015/03/26/esp8266-at-command-reference/)