/**
 * @file Bluetooth.h
 * @author Nikhil Karmakar
 * @version 1.0
 * @brief Arduino Bluetooth class with built-in line buffering.
 */
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#define ON true
#define off false
#define HIGH true
#define LOW false

class Bluetooth {
public:
    Bluetooth();

    void init(int RX = 10, int TX = 11);
    void begin(long baud = 9600);

    void write(const String& data);
    bool available();
    String readLine();
    bool setPinState(int pin_number, bool pin_state);

private:
    int rxPin = 10;
    int txPin = 11;
    SoftwareSerial* btSerial = nullptr;
    String buffer = "";
    bool lineReady = false;
};

class BTUtil {
public:
    static String removeQuotes(const String& str);
    static String* split(const String& str, char delimiter);
    static void free(String* arr);
    static void print_arr_str(const String* arr, int length);
};

#endif
