#ifndef DISPLAY_UTILS_H
#define DISPLAY_UTILS_H

#include <LiquidCrystal_I2C.h>
#include "../main/config.h"

class DisplayUtils {
public:
    DisplayUtils(LiquidCrystal_I2C& lcd);
    
    // Text display functions
    void clearLine(uint8_t line);
    void printCentered(const char* text, uint8_t line);
    void printRight(const char* text, uint8_t line);
    void printScrollable(const char* text, uint8_t line, uint8_t maxChars);
    
    // Progress indicators
    void showProgress(uint8_t progress, uint8_t line);
    void showLoadingAnimation(uint8_t position, uint8_t line);
    
    // Status indicators
    void showSuccess(const char* message, uint16_t duration = 2000);
    void showError(const char* message, uint16_t duration = 2000);
    void showAlert(const char* message, uint16_t duration = 2000);
    
    // Menu helpers
    void showMenuItem(const char* text, uint8_t line, bool selected);
    void showScrollBar(uint8_t currentItem, uint8_t totalItems, uint8_t displayLines);
    
    // Custom characters
    void createCustomChars();
    
private:
    LiquidCrystal_I2C& _lcd;
    unsigned long _lastUpdate;
    uint8_t _animationFrame;
    
    // Custom character definitions
    static const uint8_t CHAR_ARROW = 0;
    static const uint8_t CHAR_BACK = 1;
    static const uint8_t CHAR_ENTER = 2;
    static const uint8_t CHAR_UP = 3;
    static const uint8_t CHAR_DOWN = 4;
    static const uint8_t CHAR_PROGRESS = 5;
    static const uint8_t CHAR_SCROLL = 6;
    static const uint8_t CHAR_ALERT = 7;
    
    // Animation frames
    static const uint8_t LOADING_FRAMES = 4;
    static const uint8_t ANIMATION_DELAY = 250; // ms
    
    // Utility functions
    void restoreDisplay();
    uint8_t calculateScrollBarPosition(uint8_t current, uint8_t total, uint8_t height);
};

#endif // DISPLAY_UTILS_H 