#pragma once
#include <unordered_map>

extern std::unordered_map<String, int*> settingsMap;
const int ledcount = 150; // LED count for WS2812B
const int imageHeight = 32; //Your matrix height
const int imageWidth = 64; //Your matrix width
const int PIXEL_COUNT = imageHeight * imageWidth;
const char BT_NAME[] = "speckles little slave";
extern int matrix_brightness = 255;
extern int led_brightness = 60;
extern int wavelength = 2; // Default value is 1, is how many waves are shown?
extern int frame_delay = 10;
extern int loop_event = 2;
extern int xsine_amp = 3; // mulitiplier
extern int ysine_amp = 4; // to also be adjusted
int hueOffset = 0; // Not needed to be modified
int animation_delay = 4; // Idk why it needs to be separate: 2024
int xsine_period = 4; // (360/b) todo implement extern
int xsine_phase = 0;
int xsine_offset = 0;
int ysine_offset = 0;
int ysine_period = 3; // to be adjusted extern todo

