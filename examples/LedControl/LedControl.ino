/**
 * @file LedControl.ino
 * @version 1.0
 * @brief This sketch allows you to control an LED using Bluetooth by sending "on" or "off" commands.
 * 
 * @details
 * - Default LED pin: 3
 * - Command format: Just send `on` or `off` (case insensitive)
 * - Uses NBluetooth library for buffered Bluetooth communication
 */

#include <Bluetooth.h>

Bluetooth BT;

const int LED_PIN = 3;

void setup() {
    Serial.begin(9600);
    pinMode(LED_PIN, OUTPUT);
    
    BT.start();  // internally calls init() and begin()
    Serial.println("Send 'on' or 'off' via Bluetooth to control LED.");
    BT.write("ardunio is started");
}

void loop() {
    if (BT.available()) {
        String cmd = BT.readLine();
        cmd.trim();
        cmd.toLowerCase();

        if (cmd == "on") {
            digitalWrite(LED_PIN, HIGH);
            Serial.println("LED ON");
            BT.write("LED ON");
        } else if (cmd == "off") {
            digitalWrite(LED_PIN, LOW);
            Serial.println("LED OFF");
            BT.write("LED OFF");
        } else {
            Serial.println("Unknown command");
            BT.write("Unknown command. Use 'on' or 'off'");
        }
    }
}
