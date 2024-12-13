#ifndef CONFIG_H
#define CONFIG_H

// Version
#define VERSION "1.0.0"

// Hardware Configuration
#define LCD_COLS 16
#define LCD_ROWS 4
#define LCD_ADDRESS 0x27
#define LCD_SDA 21
#define LCD_SCL 22

// Keypad Configuration
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4
#define ROW_PIN_1 32
#define ROW_PIN_2 33
#define ROW_PIN_3 25
#define ROW_PIN_4 26
#define COL_PIN_1 27
#define COL_PIN_2 14
#define COL_PIN_3 12
#define COL_PIN_4 13

// Special Keys
#define KEY_CLEAR '*'
#define KEY_ENTER '#'
#define KEY_ADD 'A'
#define KEY_SUBTRACT 'B'
#define KEY_MULTIPLY 'C'
#define KEY_DIVIDE 'D'

// File System
#define TRANSACTIONS_FILE "/transactions.json"
#define SETTINGS_FILE "/settings.json"
#define MAX_TRANSACTIONS 100
#define MAX_TRANSACTION_SIZE 256

// Display Settings
#define DISPLAY_TIMEOUT 30000  // 30 seconds
#define SCROLL_DELAY 300       // 300ms between scroll steps

// Menu Settings
#define MENU_ITEMS 4
#define MENU_TIMEOUT 10000     // 10 seconds

// Error Messages
#define ERR_DIV_ZERO "Error: Div by 0"
#define ERR_OVERFLOW "Error: Overflow"
#define ERR_STORAGE "Error: Storage"

// Success Messages
#define MSG_SAVED "Saved"
#define MSG_DELETED "Deleted"

// Number Formatting
#define MAX_DIGITS 10
#define DECIMAL_PLACES 2

// Custom Characters
const byte ARROW_RIGHT[8] = {
    0b00000,
    0b00100,
    0b00110,
    0b11111,
    0b00110,
    0b00100,
    0b00000,
    0b00000
};

const byte ARROW_LEFT[8] = {
    0b00000,
    0b00100,
    0b01100,
    0b11111,
    0b01100,
    0b00100,
    0b00000,
    0b00000
};

// Menu Items
enum MenuItem {
    CALCULATOR,
    TRANSACTION_LOG,
    INVENTORY,
    SETTINGS
};

const char* const MENU_LABELS[] = {
    "Calculator",
    "Transactions",
    "Inventory",
    "Settings"
};

// Calculator States
enum CalcState {
    INPUT_FIRST,
    INPUT_SECOND,
    SHOW_RESULT,
    MENU
};

#endif // CONFIG_H 