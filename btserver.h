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
std::unordered_map<String, int*> settingsMap = {
    {"matrix_brightness", &matrix_brightness},
    {"led_brightness", &led_brightness},
    {"wavelength", &wavelength},
    {"frame_delay", &frame_delay},
    {"loop_event", &loop_event},
    {"xsine_amp", &xsine_amp},
    {"ysine_amp", &ysine_amp}
};

std::pair<String, int> bt_loop() {
    if (SerialBT.available()) {
        String message = SerialBT.readStringUntil(';');
        String variableName = message.substring(0, message.indexOf('='));
        String valueString = message.substring(message.indexOf('=') + 1);

        // Assume all values are int
        int value = valueString.toInt();

        if (settingsMap.find(variableName) != settingsMap.end()) {
            *(settingsMap[variableName]) = value;
        }

        return std::make_pair(variableName, value);
    }
    return std::make_pair("", -1);
}