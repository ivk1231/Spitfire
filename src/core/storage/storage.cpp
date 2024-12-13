#include "storage.h"

Storage::Storage() {
}

bool Storage::begin() {
    return initializeFS();
}

bool Storage::initializeFS() {
    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS Mount Failed");
        return false;
    }
    
    // Check if our files exist, if not create them
    if (!SPIFFS.exists(TRANSACTIONS_FILE)) {
        writeFile(TRANSACTIONS_FILE, "[]");
    }
    if (!SPIFFS.exists(SETTINGS_FILE)) {
        writeFile(SETTINGS_FILE, "{}");
    }
    
    return true;
}

bool Storage::saveTransaction(const char* transaction) {
    String content = readFile(TRANSACTIONS_FILE);
    _doc.clear();
    
    DeserializationError error = deserializeJson(_doc, content);
    if (error) {
        Serial.println("Failed to parse transactions file");
        return false;
    }
    
    JsonArray transactions = _doc.as<JsonArray>();
    
    // Add new transaction at the beginning
    JsonArray newTransactions = _doc.to<JsonArray>();
    newTransactions.add(transaction);
    
    // Copy existing transactions, maintaining size limit
    int count = 1;
    for (JsonVariant v : transactions) {
        if (count >= MAX_TRANSACTIONS) break;
        newTransactions.add(v.as<const char*>());
        count++;
    }
    
    String output;
    serializeJson(newTransactions, output);
    return writeFile(TRANSACTIONS_FILE, output.c_str());
}

bool Storage::getTransactions(JsonArray& transactions) {
    String content = readFile(TRANSACTIONS_FILE);
    _doc.clear();
    
    DeserializationError error = deserializeJson(_doc, content);
    if (error) {
        Serial.println("Failed to parse transactions file");
        return false;
    }
    
    transactions = _doc.as<JsonArray>();
    return true;
}

bool Storage::clearTransactions() {
    return writeFile(TRANSACTIONS_FILE, "[]");
}

bool Storage::saveSetting(const char* key, const char* value) {
    String content = readFile(SETTINGS_FILE);
    _doc.clear();
    
    DeserializationError error = deserializeJson(_doc, content);
    if (error) {
        Serial.println("Failed to parse settings file");
        return false;
    }
    
    _doc[key] = value;
    
    String output;
    serializeJson(_doc, output);
    return writeFile(SETTINGS_FILE, output.c_str());
}

String Storage::getSetting(const char* key) {
    String content = readFile(SETTINGS_FILE);
    _doc.clear();
    
    DeserializationError error = deserializeJson(_doc, content);
    if (error) {
        Serial.println("Failed to parse settings file");
        return "";
    }
    
    if (_doc.containsKey(key)) {
        return _doc[key].as<String>();
    }
    
    return "";
}

bool Storage::clearSettings() {
    return writeFile(SETTINGS_FILE, "{}");
}

bool Storage::writeFile(const char* path, const char* message) {
    File file = SPIFFS.open(path, "w");
    if (!file) {
        Serial.println("Failed to open file for writing");
        return false;
    }
    
    if (file.print(message)) {
        file.close();
        return true;
    } else {
        file.close();
        return false;
    }
}

String Storage::readFile(const char* path) {
    File file = SPIFFS.open(path, "r");
    if (!file) {
        Serial.println("Failed to open file for reading");
        return "";
    }
    
    String content = file.readString();
    file.close();
    return content;
} 