#include "display_utils.h"

// Custom character definitions
const uint8_t charArrow[8] = {
    0b00000,
    0b00100,
    0b00110,
    0b11111,
    0b00110,
    0b00100,
    0b00000,
    0b00000
};

const uint8_t charBack[8] = {
    0b00000,
    0b00100,
    0b01100,
    0b11111,
    0b01100,
    0b00100,
    0b00000,
    0b00000
};

const uint8_t charEnter[8] = {
    0b00000,
    0b00001,
    0b00001,
    0b00101,
    0b01101,
    0b11111,
    0b01100,
    0b00100
};

const uint8_t charUp[8] = {
    0b00000,
    0b00100,
    0b01110,
    0b10101,
    0b00100,
    0b00100,
    0b00000,
    0b00000
};

const uint8_t charDown[8] = {
    0b00000,
    0b00100,
    0b00100,
    0b10101,
    0b01110,
    0b00100,
    0b00000,
    0b00000
};

const uint8_t charProgress[8] = {
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111
};

const uint8_t charScroll[8] = {
    0b11111,
    0b11111,
    0b11111,
    0b00000,
    0b00000,
    0b11111,
    0b11111,
    0b11111
};

const uint8_t charAlert[8] = {
    0b00100,
    0b01110,
    0b01110,
    0b01110,
    0b01110,
    0b00000,
    0b00100,
    0b00000
};

DisplayUtils::DisplayUtils(LiquidCrystal_I2C& lcd) : _lcd(lcd) {
    _lastUpdate = 0;
    _animationFrame = 0;
    createCustomChars();
}

void DisplayUtils::createCustomChars() {
    _lcd.createChar(CHAR_ARROW, charArrow);
    _lcd.createChar(CHAR_BACK, charBack);
    _lcd.createChar(CHAR_ENTER, charEnter);
    _lcd.createChar(CHAR_UP, charUp);
    _lcd.createChar(CHAR_DOWN, charDown);
    _lcd.createChar(CHAR_PROGRESS, charProgress);
    _lcd.createChar(CHAR_SCROLL, charScroll);
    _lcd.createChar(CHAR_ALERT, charAlert);
}

void DisplayUtils::clearLine(uint8_t line) {
    _lcd.setCursor(0, line);
    for(uint8_t i = 0; i < LCD_COLS; i++) {
        _lcd.print(" ");
    }
}

void DisplayUtils::printCentered(const char* text, uint8_t line) {
    uint8_t len = strlen(text);
    uint8_t pos = (LCD_COLS - len) / 2;
    if(pos < 0) pos = 0;
    
    clearLine(line);
    _lcd.setCursor(pos, line);
    _lcd.print(text);
}

void DisplayUtils::printRight(const char* text, uint8_t line) {
    uint8_t len = strlen(text);
    uint8_t pos = LCD_COLS - len;
    if(pos < 0) pos = 0;
    
    _lcd.setCursor(pos, line);
    _lcd.print(text);
}

void DisplayUtils::printScrollable(const char* text, uint8_t line, uint8_t maxChars) {
    uint8_t len = strlen(text);
    if(len <= maxChars) {
        _lcd.setCursor(0, line);
        _lcd.print(text);
        return;
    }
    
    unsigned long currentTime = millis();
    if(currentTime - _lastUpdate > ANIMATION_DELAY) {
        _animationFrame = (_animationFrame + 1) % (len - maxChars + 1);
        _lastUpdate = currentTime;
        
        clearLine(line);
        _lcd.setCursor(0, line);
        for(uint8_t i = 0; i < maxChars; i++) {
            if(i + _animationFrame < len) {
                _lcd.print(text[i + _animationFrame]);
            }
        }
    }
}

void DisplayUtils::showProgress(uint8_t progress, uint8_t line) {
    clearLine(line);
    _lcd.setCursor(0, line);
    
    uint8_t bars = (progress * LCD_COLS) / 100;
    for(uint8_t i = 0; i < bars; i++) {
        _lcd.write(CHAR_PROGRESS);
    }
}

void DisplayUtils::showLoadingAnimation(uint8_t position, uint8_t line) {
    static const char animation[] = {'|', '/', '-', '\\'};
    
    unsigned long currentTime = millis();
    if(currentTime - _lastUpdate > ANIMATION_DELAY) {
        _animationFrame = (_animationFrame + 1) % LOADING_FRAMES;
        _lastUpdate = currentTime;
        
        _lcd.setCursor(position, line);
        _lcd.print(animation[_animationFrame]);
    }
}

void DisplayUtils::showSuccess(const char* message, uint16_t duration) {
    printCentered(message, 1);
    delay(duration);
    restoreDisplay();
}

void DisplayUtils::showError(const char* message, uint16_t duration) {
    _lcd.clear();
    _lcd.write(CHAR_ALERT);
    _lcd.print(" Error");
    printCentered(message, 1);
    delay(duration);
    restoreDisplay();
}

void DisplayUtils::showAlert(const char* message, uint16_t duration) {
    _lcd.clear();
    _lcd.write(CHAR_ALERT);
    _lcd.print(" Alert");
    printCentered(message, 1);
    delay(duration);
    restoreDisplay();
}

void DisplayUtils::showMenuItem(const char* text, uint8_t line, bool selected) {
    clearLine(line);
    _lcd.setCursor(0, line);
    if(selected) {
        _lcd.write(CHAR_ARROW);
        _lcd.print(" ");
    } else {
        _lcd.print("  ");
    }
    _lcd.print(text);
}

void DisplayUtils::showScrollBar(uint8_t currentItem, uint8_t totalItems, uint8_t displayLines) {
    if(totalItems <= displayLines) return;
    
    uint8_t pos = calculateScrollBarPosition(currentItem, totalItems, displayLines);
    for(uint8_t i = 0; i < displayLines; i++) {
        _lcd.setCursor(LCD_COLS - 1, i);
        _lcd.write(i == pos ? CHAR_SCROLL : ' ');
    }
}

void DisplayUtils::restoreDisplay() {
    // This should be implemented based on the current menu state
    // For now, just clear the display
    _lcd.clear();
}

uint8_t DisplayUtils::calculateScrollBarPosition(uint8_t current, uint8_t total, uint8_t height) {
    if(total <= height) return 0;
    return (current * (height - 1)) / (total - 1);
}