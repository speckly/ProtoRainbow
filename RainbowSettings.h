#pragma once
int ledcount = 80; // LED count for WS2812B
int imageHeight = 32; //Your matrix height
int imageWidth = 64; //Your matrix width
int pixelCount = imageHeight * imageWidth;
int wavelength = 2; //Value of rgb waves shown in one frame, idk how to explain lol, default value is 1
int frame_delay = 10;
int animation_delay = 4;
int loopEvent = 2;
int xsine_period = 4; //(360/b)
int xsine_amp = 3; //mulitiplier
int xsine_phase = 0;
int xsine_offset = 0;
int ysine_offset = 0;
int ysine_period = 3; 
int ysine_amp = 4;
