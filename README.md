# Smart Business Calculator

A smart calculator designed for small business owners, featuring inventory management, transaction tracking, and business analytics.

## Features

- Basic calculator functionality
- Inventory management system
- Transaction history tracking
- Low stock alerts
- Menu-based interface
- Data persistence using SPIFFS
- Custom character sets for improved UI

## Hardware Requirements

- ESP32 Development Board
- 16x4 I2C LCD Display (LCD2004 with PCF8574 I2C adapter)
- 4x4 Matrix Keypad
- Jumper wires
- Optional: 10kΩ pull-up resistors (if not using internal pull-ups)

## Software Requirements

### Required Libraries
- LiquidCrystal_I2C
- Keypad
- ArduinoJson
- SPIFFS (built into ESP32)

### Development Environment
- Arduino IDE
- ESP32 Board Support Package

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/smart-calculator.git
   ```

2. Install required libraries in Arduino IDE:
   - Sketch -> Include Library -> Manage Libraries
   - Search and install all required libraries

3. Configure ESP32 in Arduino IDE:
   - File -> Preferences -> Additional Board Manager URLs
   - Add: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Tools -> Board -> Boards Manager
   - Search for ESP32 and install

4. Connect hardware according to wiring diagram in `docs/wiring_diagram.md`

5. Upload SPIFFS data:
   - Tools -> ESP32 Sketch Data Upload
   - This will upload the contents of the data folder

6. Compile and upload the main program:
   - Select correct board and port
   - Upload sketch

## Project Structure

```
SmartCalculator/
│
├── src/                    # Source files
│   ├── main/              # Main application files
│   ├── core/              # Core functionality
│   └── utils/             # Utility functions
│
├── test/                  # Test files
├── docs/                  # Documentation
├── data/                  # SPIFFS data
└── README.md             # This file
```

## Usage

1. **Calculator Mode**
   - Use numeric keypad (0-9) for numbers
   - A: Add, B: Subtract, C: Multiply, D: Divide
   - *: Clear, #: Enter/Execute

2. **Inventory Management**
   - Navigate menu using 2(Up) and 8(Down)
   - Enter selections with #
   - Go back with *
   - Follow on-screen prompts

3. **Transaction History**
   - View past calculations
   - Scroll through history
   - Export data (if implemented)

## Development

- Follow the folder structure for new features
- Use display utilities for consistent UI
- Document changes in development_tracker.md
- Test new features using test_sequence.ino

## Contributing

1. Fork the repository
2. Create your feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- ESP32 Community
- Arduino Community
- Contributors and testers

## Support

For support, please open an issue in the GitHub repository or contact the maintainers. 