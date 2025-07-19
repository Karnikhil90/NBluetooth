#include <Bluetooth.h>

/**
 * @file Talking.ino
 * @version v1.0
 * @brief This sketch connects to your Bluetooth device and shows the output.
 */

Bluetooth BT;

void setup() {
    Serial.begin(9600);
    BT.start();  // Does init and begin
    Serial.println("Bluetooth Ready. Waiting for input...");
}

void loop() {
    if (BT.available()) {
        String cmd = BT.readLine();
        Serial.print("Received from Bluetooth: ");
        Serial.println(cmd);

        // Optional: parse and echo back
        BT.write("OK: " + cmd);
    }
}
