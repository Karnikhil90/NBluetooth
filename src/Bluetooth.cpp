#include "Bluetooth.h"

// Constructor does not initialize SoftwareSerial
Bluetooth::Bluetooth() {}

void Bluetooth::init(int RX, int TX) {
    rxPin = RX;
    txPin = TX;

    // Delete old instance if it exists
    if (btSerial != nullptr) {
        delete btSerial;
        btSerial = nullptr;
    }

    // Create new instance with updated pins
    btSerial = new SoftwareSerial(rxPin, txPin);
}

void Bluetooth::begin(long baud) {
    if (btSerial == nullptr) {
        btSerial = new SoftwareSerial(rxPin, txPin);
    }
    btSerial->begin(baud);
}

bool Bluetooth::setPinState(int pin_number, bool pin_state) {
    pinMode(pin_number, OUTPUT);
    digitalWrite(pin_number, pin_state);
    return true;
}

void Bluetooth::write(const String& data) {
    if (btSerial) {
        btSerial->println(data);
    }
}

bool Bluetooth::available() {
    while (btSerial && btSerial->available()) {
        char c = btSerial->read();

        if (c == '\n' || c == '\r') {
            if (buffer.length() > 0) {
                buffer.trim();
                lineReady = true;
                return true;
            }
        } else {
            buffer += c;
        }
    }
    return false;
}

String Bluetooth::readLine() {
    lineReady = false;
    String result = buffer;
    buffer = "";
    return result;
}

// ----------------------
// BTUtil Implementation
// ----------------------

String BTUtil::removeQuotes(const String& str) {
    if (str.length() >= 2 && str[0] == '"' && str[str.length() - 1] == '"') {
        return str.substring(1, str.length() - 1);
    }
    return str;
}

String* BTUtil::split(const String& str, char delimiter) {
    int count = 1;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == delimiter) count++;
    }

    String* parts = new String[count];
    int start = 0;
    int idx = 0;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == delimiter) {
            parts[idx++] = str.substring(start, i);
            start = i + 1;
        }
    }
    parts[idx] = str.substring(start);
    return parts;
}

void BTUtil::free(String* arr) {
    delete[] arr;
}

void BTUtil::print_arr_str(const String* arr, int length) {
    for (int i = 0; i < length; i++) {
        Serial.print("Arg[");
        Serial.print(i);
        Serial.print("] = ");
        Serial.println(arr[i]);
    }
}
