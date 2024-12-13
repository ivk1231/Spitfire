# Wiring Diagram for Smart Business Calculator

## Components
1. ESP32 Development Board
2. 16x4 I2C LCD Display (LCD2004 with PCF8574 I2C adapter)
3. 4x4 Matrix Keypad
4. Jumper wires
5. Optional: 10kΩ pull-up resistors (if not using internal pull-ups)

## Connections

### LCD Display (I2C)
```
LCD I2C Module -> ESP32
GND  -----------> GND
VCC  -----------> 5V
SDA  -----------> GPIO21
SCL  -----------> GPIO22
```

### 4x4 Matrix Keypad
```
Keypad Pin -> ESP32
ROW1 -------> GPIO32
ROW2 -------> GPIO33
ROW3 -------> GPIO25
ROW4 -------> GPIO26
COL1 -------> GPIO27
COL2 -------> GPIO14
COL3 -------> GPIO12
COL4 -------> GPIO13
```

## Pin Layout Diagram
```
+----------------+     +-------------------+
|    ESP32       |     |  LCD I2C Module  |
|                |     |                  |
| 5V    ---------|---->| VCC             |
| GND   ---------|---->| GND             |
| GPIO21---------|---->| SDA             |
| GPIO22---------|---->| SCL             |
|                |     |                  |
+----------------+     +-------------------+

+----------------+     +-------------------+
|    ESP32       |     |  4x4 Keypad      |
|                |     |                  |
| GPIO32---------|---->| ROW1            |
| GPIO33---------|---->| ROW2            |
| GPIO25---------|---->| ROW3            |
| GPIO26---------|---->| ROW4            |
| GPIO27---------|---->| COL1            |
| GPIO14---------|---->| COL2            |
| GPIO12---------|---->| COL3            |
| GPIO13---------|---->| COL4            |
+----------------+     +-------------------+
```

## Notes
1. The I2C LCD module has built-in pull-up resistors, no external resistors needed
2. ESP32's internal pull-up resistors are used for the keypad
3. Default I2C address is 0x27 (can be changed with module jumpers if needed)
4. Make sure all GND connections are common

## Power Considerations
- LCD with I2C module requires 5V power
- ESP32 I/O pins operate at 3.3V but are 5V tolerant on input
- Total power consumption:
  - LCD: ~20mA
  - ESP32: ~100mA
  - Keypad: negligible (using pull-ups)
``` 