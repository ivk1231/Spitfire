#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

// LCD Configuration
const int LCD_COLS = 16;
const int LCD_ROWS = 4;
const int LCD_ADDRESS = 0x27;
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

// Keypad Configuration
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},  // A: Add
  {'4','5','6','B'},  // B: Subtract
  {'7','8','9','C'},  // C: Multiply
  {'*','0','#','D'}   // D: Divide, *: Clear, #: Enter
};
byte rowPins[ROWS] = {32, 33, 25, 26};
byte colPins[COLS] = {27, 14, 12, 13};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Calculator states
enum CalcState {
  INPUT_FIRST,
  INPUT_SECOND,
  SHOW_RESULT,
  MENU
};

// Menu items
enum MenuItem {
  CALCULATOR,
  TRANSACTION_LOG,
  INVENTORY,
  SETTINGS
};

// Global variables
CalcState currentState = INPUT_FIRST;
MenuItem currentMenu = CALCULATOR;
String firstNumber = "";
String secondNumber = "";
char operation = 0;
float result = 0;
String lastTransaction = "";

// Custom characters
byte arrowRight[8] = {
  0b00000,
  0b00100,
  0b00110,
  0b11111,
  0b00110,
  0b00100,
  0b00000,
  0b00000
};

// Function prototypes
void handleNumber(char key);
void handleOperation(char key);
void calculateResult();
void updateDisplay();
void handleMenu();
void saveTransaction();
void clearCalculator();

void setup() {
  Serial.begin(115200);
  
  // Initialize LCD
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, arrowRight);
  
  // Initialize SPIFFS for storage
  if(!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  
  // Show welcome message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smart Calculator");
  lcd.setCursor(0, 1);
  lcd.print("Version 1.0");
  delay(2000);
  
  updateDisplay();
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    Serial.print("Key pressed: ");
    Serial.println(key);
    
    switch(currentState) {
      case MENU:
        handleMenu();
        break;
        
      case INPUT_FIRST:
      case INPUT_SECOND:
        if (isdigit(key)) {
          handleNumber(key);
        } else if (key == '*') {
          clearCalculator();
        } else if (key == '#') {
          if (currentState == INPUT_SECOND) {
            calculateResult();
          }
        } else {
          handleOperation(key);
        }
        break;
        
      case SHOW_RESULT:
        if (key == '*') {
          clearCalculator();
        } else if (isdigit(key)) {
          clearCalculator();
          handleNumber(key);
        }
        break;
    }
    
    updateDisplay();
  }
}

void handleNumber(char key) {
  if (currentState == INPUT_FIRST) {
    if (firstNumber.length() < 10) {
      firstNumber += key;
    }
  } else if (currentState == INPUT_SECOND) {
    if (secondNumber.length() < 10) {
      secondNumber += key;
    }
  }
}

void handleOperation(char key) {
  if (firstNumber.length() > 0) {
    operation = key;
    currentState = INPUT_SECOND;
  }
}

void calculateResult() {
  float num1 = firstNumber.toFloat();
  float num2 = secondNumber.toFloat();
  
  switch(operation) {
    case 'A': // Add
      result = num1 + num2;
      break;
    case 'B': // Subtract
      result = num1 - num2;
      break;
    case 'C': // Multiply
      result = num1 * num2;
      break;
    case 'D': // Divide
      if (num2 != 0) {
        result = num1 / num2;
      } else {
        lcd.clear();
        lcd.print("Error: Div by 0");
        delay(2000);
        clearCalculator();
        return;
      }
      break;
  }
  
  currentState = SHOW_RESULT;
  saveTransaction();
}

void updateDisplay() {
  lcd.clear();
  
  switch(currentState) {
    case MENU:
      lcd.setCursor(0, 0);
      lcd.print("MENU");
      // Add menu display code
      break;
      
    case INPUT_FIRST:
      lcd.setCursor(0, 0);
      lcd.print("Enter Number:");
      lcd.setCursor(0, 1);
      lcd.print(firstNumber);
      break;
      
    case INPUT_SECOND:
      lcd.setCursor(0, 0);
      lcd.print(firstNumber);
      lcd.print(" ");
      switch(operation) {
        case 'A': lcd.print("+"); break;
        case 'B': lcd.print("-"); break;
        case 'C': lcd.print("*"); break;
        case 'D': lcd.print("/"); break;
      }
      lcd.setCursor(0, 1);
      lcd.print(secondNumber);
      break;
      
    case SHOW_RESULT:
      lcd.setCursor(0, 0);
      lcd.print(firstNumber);
      lcd.print(" ");
      switch(operation) {
        case 'A': lcd.print("+"); break;
        case 'B': lcd.print("-"); break;
        case 'C': lcd.print("*"); break;
        case 'D': lcd.print("/"); break;
      }
      lcd.print(" ");
      lcd.print(secondNumber);
      lcd.setCursor(0, 1);
      lcd.print("= ");
      lcd.print(result);
      break;
  }
  
  // Show help on bottom line
  lcd.setCursor(0, 3);
  lcd.print("*:CLR #:ENTER");
}

void saveTransaction() {
  lastTransaction = firstNumber + operation + secondNumber + "=" + String(result);
  // TODO: Implement SPIFFS saving
}

void clearCalculator() {
  firstNumber = "";
  secondNumber = "";
  operation = 0;
  result = 0;
  currentState = INPUT_FIRST;
}

void handleMenu() {
  // TODO: Implement menu handling
} 