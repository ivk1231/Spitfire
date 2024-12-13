#ifndef STORAGE_H
#define STORAGE_H

#include <SPIFFS.h>
#include <ArduinoJson.h>
#include "config.h"

class Storage {
public:
    Storage();
    bool begin();
    
    // Transaction methods
    bool saveTransaction(const char* transaction);
    bool getTransactions(JsonArray& transactions);
    bool clearTransactions();
    
    // Settings methods
    bool saveSetting(const char* key, const char* value);
    String getSetting(const char* key);
    bool clearSettings();
    
private:
    bool initializeFS();
    bool writeFile(const char* path, const char* message);
    String readFile(const char* path);
    
    StaticJsonDocument<1024> _doc; // JSON document for parsing
};

#endif // STORAGE_H 