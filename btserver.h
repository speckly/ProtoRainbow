/*
Author: Andrew Higgins
https://github.com/speckly

Warning: This is very insecure and is 100% susceptible to MITM or spoofing
*/

#include "RainbowSettings.h"
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

std::pair<String, int> bt_loop() {
    if (SerialBT.available()) {
        String message = SerialBT.readStringUntil(';');

        int equalIndex = message.indexOf('=');

        if (equalIndex == -1) {
            // This is the face
            return std::make_pair(message, -1);
        }

        String variableName = message.substring(0, message.indexOf('='));
        String valueString = message.substring(message.indexOf('=') + 1);

        // Assume all values are int
        int value = valueString.toInt();

        if (variableName == "matrix_brightness") {
            matrix_brightness = value;
        } else if (variableName == "led_brightness") {
            led_brightness = value;
        } else if (variableName == "wavelength") {
            wavelength = value;
        } else if (variableName == "frame_delay") {
            frame_delay = value;
        } else if (variableName == "loop_event") {
            loop_event = value;
        } else if (variableName == "xsine_amp") {
            xsine_amp = value;
        } else if (variableName == "ysine_amp") {
            ysine_amp = value;
        } else {
            // Handle unknown variableName case
            return std::make_pair("unknown", -1);
        }

        return std::make_pair(variableName, value);
    }
    return std::make_pair("", -1);
}
